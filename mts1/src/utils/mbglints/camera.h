#pragma once
#if !defined(__CAMERA_H_)
#define __CAMERA_H_

#include "path.h"
#include "util.h"
#include "shape.h"
#include "localEigen/Dense"
using namespace Eigen;

typedef Eigen::Vector3f Vec3;
typedef Eigen::Vector2f Vec2;
typedef Eigen::Vector4f Vec4;
typedef Eigen::Vector2i Vec2i;

float deg2rad(float degree)
{
	return degree * M_PI / 180.0f;
}

Vec3 getNormal(const Vec3 &vert1, const Vec3 &vert2, const Vec3 &vert3)
{
	Vec3 v2v3 = vert3 - vert2;
	Vec3 v1v2 = vert2 - vert1;
	Vec3 N = v2v3.cross(v1v2);
	N.normalize();

	return N;
}

Vec4 plane(const Vec3 &P, const Vec3 &v1, const Vec3 &v2, const Vec3 &v3, const Vec3 &ng)
{
	Vec3 v3_to_2 = (v2 - v3).normalized();
	Vec3 p1 = v3 + (P - v3).dot(v3_to_2) * v3_to_2;
	Vec3 nA = getNormal(v2, v3, v3 + ng);

	float w = nA.dot(v2);
	Vec4 L = Vec4(nA[0], nA[1], nA[2], -w);

	float length = L.dot(Vec4(v1[0], v1[1], v1[2], 1));
	L /= length;
	return L;
}
Vec3 reflect(const Vec3 &wi, const Vec3 &n)
{
	return 2 * wi.dot(n) * n - wi;
}

enum EPostOption
{
	NoProcess = 0, // Default no post-processing
	BloomTwoPass,
	BloomUpDown,
};

class Camera
{
public:
	Camera(const Vec3 &_pos, const Vec3 &_dir, const Vec3 &_up, const Vec3 &_left, const Vec2i &_res, float _fov,
		   const mitsuba::Transform &_cameraToSample) : m_pos(_pos), m_dir(_dir), m_resolution(_res), m_fov(_fov)
	{
		m_cameraToSample = _cameraToSample;
		m_sampleToCamera = m_cameraToSample.inverse();
		m_s = _left;
		m_t = _up;

		// if (global_log_flag) cout << "m_s:" << m_s[0] << ", " << m_s[1] << "," << m_s[2] << endl;
		// if (global_log_flag) cout << "m_t:" << m_t[0] << ", " << m_t[1] << "," << m_t[2] << endl;

		m_image.resize(m_resolution[0] * m_resolution[1] * 3, 0.0f);
		m_image2.resize(m_resolution[0] * m_resolution[1] * 3, 0.0f);

		m_scale = tan(deg2rad(m_fov * 0.5));
		m_imageAspectRatio = (float)m_resolution[1] / (float)m_resolution[0];

		m_A = 4 * m_imageAspectRatio * m_scale * m_scale;
		// if (global_log_flag) cout << "M_A1: " << m_resolution[0] * m_resolution[1] / m_A << endl;

		const int threadCount = omp_get_max_threads();
		m_imageThreads.resize(threadCount);
		for (int i = 0; i < threadCount; i++)
			m_imageThreads[i].resize(m_resolution[0] * m_resolution[1] * 3, 0.0f);

		// postprocessing
		postProcessOption = EPostOption::NoProcess;
	};

	void setCam(const Vec3 &_pos, const Vec3 &_dir, const Vec3 &_up, const Vec3 &_left, const Vec2i &_res, float _fov,
				const mitsuba::Transform &_cameraToSample)
	{
		m_pos = _pos;
		m_dir = _dir;
		m_resolution = _res;
		m_fov = _fov;
		m_cameraToSample = _cameraToSample;
		m_sampleToCamera = m_cameraToSample.inverse();
		m_s = _left;
		m_t = _up;
	}

	~Camera()
	{
		std::vector<float>().swap(m_image);
		std::vector<float>().swap(m_image2);
		const int threadCount = omp_get_max_threads();
		for (int i = 0; i < threadCount; i++)
			std::vector<float>().swap(m_imageThreads[i]);
		std::vector<std::vector<float>>().swap(m_imageThreads);
	}

	void reflectionAutoDiff(const PathVert &vert, const DVec4 &P, DVec4 &D)
	{
		DVec3 n = vert.Lalpha.dot(P) * vert.Nalpha + vert.Lbeta.dot(P) * vert.Nbeta + vert.Lgamma.dot(P) * vert.Ngamma;
		DVec3 N = n / sqrt(n.dot(n));

		DVec4 N4 = DVec4(N[0], N[1], N[2], 0);
		D = D - 2.0f * (D.dot(N4)) * N4;
	}

	bool refractionAutoDiff(const PathVert &vert, const DVec4 &P, DVec4 &D)
	{
		DVec3 n = vert.Lalpha.dot(P) * vert.Nalpha + vert.Lbeta.dot(P) * vert.Nbeta + vert.Lgamma.dot(P) * vert.Ngamma;
		DVec3 N = n / sqrt(n.dot(n));
		DVec4 N4 = DVec4(N[0], N[1], N[2], 0);
		DFloat DdotN = D.dot(N4);

		float eta;
		if (true)
		{
			eta = 1.5041833;
		}
		else
		{
			N4 = -N4;
			DdotN = D.dot(N4);
			eta = vert.m_bsdf->m_eta;
		}

		DFloat term2 = -sqrt(1 - eta * eta * (1 - DdotN * DdotN));
		DFloat mu = eta * DdotN - term2;

		D = eta * D - mu * N4;
		return true;
	}

	void propagationAutoDiff(const PathVert &next_vert, DVec4 &P, const DVec4 &D)
	{
		Vec3 N = next_vert.m_N_G;
		float w = N.dot(next_vert.m_pos);
		Vec4 N4 = Vec4(N[0], N[1], N[2], -w);
		DFloat temp = D.dot(Vec4(N[0], N[1], N[2], 0));
		DFloat t = -(P.dot(N4)) / temp;
		P = P + t * D;
	}

	DVec4 pathAutoDiff(const Path &path, DFloat x, DFloat y, DVec4 &outPxy, bool &valid)
	{
		const int pathLength = path.getLength() - 2;

		DVec4 P_xy = DVec4(m_pos[0], m_pos[1], m_pos[2], 1);
		DVec3 D3 = (m_dir + x * m_s + y * m_t).normalized();

		DVec4 D_xy = DVec4(D3[0], D3[1], D3[2], 0);

		valid = true;
		for (int i = 0; i < pathLength; i++)
		{
			// vert start from the light side, but we have to move to the camera side
			const PathVert &vert = path.getVert(pathLength - i);

			// the first operator is propagation
			propagationAutoDiff(vert, P_xy, D_xy);

			if (vert.m_bsdf->getType() == MyBSDF::ERefelction)
				reflectionAutoDiff(vert, P_xy, D_xy);
			else
				valid = refractionAutoDiff(vert, P_xy, D_xy);
		}

		propagationAutoDiff(path.getVert(0), P_xy, D_xy);

		outPxy = P_xy;
		return D_xy;
	}

	bool computeDifferentialAutoDiff(const Path &path, Vec3 &out_dDdx, Vec3 &out_dDdy, Vec3 &out_dPdx, Vec3 &out_dPdy, float &fac)
	{
		const int pathLength = path.getLength() - 2;
		Vec3 dworld = (path.getVert(pathLength).m_pos - path.getVert(pathLength + 1).m_pos).normalized();
		Vec3 dLocal = toLocal(dworld);
		dLocal /= dLocal[2]; // the z unit is 1
		fac = 1 / std::pow(dLocal[0] * dLocal[0] + dLocal[1] * dLocal[1] + 1, 1.5);
		// fac = 1.0;
		DFloat x = DFloat(dLocal[0], 2, 0);
		DFloat y = DFloat(dLocal[1], 2, 1);
		DVec4 P;
		bool valid = true;
		DVec4 D = pathAutoDiff(path, x, y, P, valid);

		out_dDdx = Vec3(D[0].derivatives()[0], D[1].derivatives()[0], D[2].derivatives()[0]);
		out_dDdy = Vec3(D[0].derivatives()[1], D[1].derivatives()[1], D[2].derivatives()[1]);

		out_dPdx = Vec3(P[0].derivatives()[0], P[1].derivatives()[0], P[2].derivatives()[0]);
		out_dPdy = Vec3(P[0].derivatives()[1], P[1].derivatives()[1], P[2].derivatives()[1]);
		return valid;
	}

	std::pair<Vec3, Vec3> splat(const Path *path)
	{
		Vec3 surfacePos = path->getLastVertPos();
		Vec3 camToSurfaceDir = (surfacePos - m_pos).normalized();
		auto lightPos = path->vertices[0].m_pos;
		// std::cout << "Splat: " << lightPos[0] << ", " <<  lightPos[1] << ", " << lightPos[2] << std::endl;

		// from world space to local Space
		Vec3 localDir = toLocal(camToSurfaceDir);
		Vec2 pixel = dirToPixel(localDir);

		Vec3 value;

		if ((pixel[0] < m_resolution[0] && pixel[0] >= 0 && pixel[1] < m_resolution[1] && pixel[1] >= 0) || global_log_flag == false)
		{
			// compute direction ray differential
			Vec3 dDdx, dDdy, dPdx, dPdy;
			float fac;
			bool valid = computeDifferentialAutoDiff(*path, dDdx, dDdy, dPdx, dPdy, fac);
			if (!valid)
				return {};

			float temp;
			temp = dPdx.norm() * dPdy.norm() * std::max(0.1f, dPdx.normalized().cross(dPdy.normalized()).norm());

			float curvatureFac = 1.0 / temp;
			value = path->computeContribution() * curvatureFac * fac;

			path->ans = value;

			if (global_log_flag == true)
				value *= m_resolution[0] * m_resolution[1] / m_A;

#if 0
			//this is a box filter
			m_image[(round(pixel[1]) * m_resolution[0] + round(pixel[0])) * 3] += value[0];
			m_image[(round(pixel[1]) * m_resolution[0] + round(pixel[0])) * 3 + 1] += value[1];
			m_image[(round(pixel[1]) * m_resolution[0] + round(pixel[0])) * 3 + 2] += value[2];
#else
			// use a tent filter
			// find the four neighbors
			int x0 = floor(pixel[0]);
			int y0 = floor(pixel[1]);
			int x1 = pixel[0] - x0 > 0.5 ? min(m_resolution[0] - 1, x0 + 1) : max(0, x0 - 1);
			int y1 = pixel[1] - y0 > 0.5 ? min(m_resolution[1] - 1, y0 + 1) : max(0, y0 - 1);
			float w1 = abs(pixel[0] - x0 - 0.5);
			float w2 = abs(pixel[1] - y0 - 0.5);
			Vec2i pos[] = {Vec2i(x0, y0), Vec2i(x0, y1), Vec2i(x1, y1), Vec2i(x1, y0)};
			float weight[] = {(1 - w1) * (1 - w2), (1 - w1) * w2, w1 * w2, w1 * (1 - w2)};

			for (int k = 0; k < 4; k++)
			{
				int idx = pos[k][1] * m_resolution[0] + pos[k][0];
				m_image[idx * 3] += value[0] * weight[k];
				m_image[idx * 3 + 1] += value[1] * weight[k];
				m_image[idx * 3 + 2] += value[2] * weight[k];
			}
#endif
		}

		return std::make_pair(camToSurfaceDir, value);
	}

	std::vector<std::pair<Vec3, Vec3>> splat(const std::vector<Path *> &pathList, const Scene *scene)
	{
		const int threadCount = omp_get_max_threads();
		if (global_log_flag)
			cout << "The thread cout for splatting is " << threadCount << endl;

		Vec3 sum(0, 0, 0);
		std::vector<std::pair<Vec3, Vec3>> ans;

		for (int i = 0; i < pathList.size(); i++)
		{
			int tid = omp_get_thread_num();
			const Path *path = pathList[i];
			auto [dir, tmp] = splat(path);
			sum += tmp;
			ans.push_back({dir, tmp});
		}

		return ans;
	}

	// #------------------------#
	// #----post-processing-----#
	// #------------------------#
	using RGBRow = std::vector<Vec3>;
	using RGBMat = std::vector<std::vector<Vec3>>;
	void PostTwoPassBloom(int kSize)
	{
		auto width = m_resolution[0];
		auto height = m_resolution[1];
		// 1.bright fetch(threshold dot product)
		// another standard exists or not
		RGBMat bright_image(width, RGBRow(height, Vec3(0.f, 0.f, 0.f)));

		for (int i = 0; i < m_image.size(); i += 3)
		{
			Vec3 pixel(m_image[i], m_image[i + 1], m_image[i + 2]);
			// from Blog https://github.com/WingerZeng/MyCGLab
			auto alpha = 0.2989, beta = 0.5870, gamma = 0.1240;
			auto brightness = alpha * pixel[0] + beta * pixel[1] + gamma * pixel[2];
			if (brightness >= 1.f)
			{
				auto ppos = i / 3;
				bright_image[ppos / height][ppos % height] = pixel;
			}
		}
		// 2. two-pass filter
		auto depth = 3;
		auto sigma = 1.f;

		// down sample
		std::vector<RGBMat> temp_images(depth + 1, RGBMat(width, RGBRow(height, Vec3(0.f, 0.f, 0.f))));
		temp_images[0] = bright_image;
		// RGBMat temp_image(width, RGBRow(height, Vec3(0.f, 0.f, 0.f)));
		for (int d = 1; d < depth; d++)
		{
			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					Vec3 sum(0.f, 0.f, 0.f);
					float weight_sum = 0.0;
					for (int i = -kSize / 2; i <= kSize / 2; i++)
					{
						int newX = x + i;
						if (newX >= 0 && newX < width)
						{
							auto coeff = 1.f / sqrt(2.0 * M_PI * sigma * sigma);
							auto weight = coeff * exp(-(float)i * i / (2 * sigma * sigma));
							sum += temp_images[d - 1][newX][y] * weight;
							weight_sum += weight;
						}
					}

					temp_images[d][x][y] = sum / weight_sum;
				}
			}
			RGBMat inter_image(width, RGBRow(height, Vec3(0.f, 0.f, 0.f)));
			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					Vec3 sum(0.f, 0.f, 0.f);
					float weight_sum = 0.0;
					for (int j = -kSize / 2; j <= kSize / 2; j++)
					{
						int newY = y + j;
						if (newY >= 0 && newY < height)
						{
							auto coeff = 1.f / sqrt(2.0 * M_PI * sigma * sigma);
							auto weight = coeff * exp(-(float)j * j / (2 * sigma * sigma));
							sum += temp_images[d][x][newY] * weight;
							weight_sum += weight;
						}
					}
					inter_image[x][y] = sum / weight_sum;
				}
			}
			temp_images[d] = inter_image;
		}
		temp_images[depth] = bright_image;
		for (int d = 1; d <= depth; d++)
		{
			// 3. amelorate two pictures
			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					int pos = x * height + y;
					m_image[3 * pos] += temp_images[d][x][y][0];
					m_image[3 * pos + 1] += temp_images[d][x][y][1];
					m_image[3 * pos + 2] += temp_images[d][x][y][2];
				}
			}
		}
		for (int i = 0; i < m_image.size(); i++)
		{
			m_image[i] /= depth;
		}
		return;
	}

	void PostProcessingSelection()
	{
		switch (postProcessOption)
		{
		case EPostOption::BloomTwoPass:
		{
			auto kSize = 16;
			PostTwoPassBloom(kSize);
		}
		break;
		case EPostOption::BloomUpDown:
			// TODO
			break;
		default:
			break;
		}
		return;
	}

	void writeOutput(string output)
	{
		PostProcessingSelection();
		SaveEXRChannel3(m_image, m_resolution[0], m_resolution[1], output.c_str());
		cout << "Rendering to Image done!" << endl;
	}

	void writeOutput2(string output)
	{
		SaveEXRChannel3(m_image2, m_resolution[0], m_resolution[1], output.c_str());
		cout << "Rendering to Image done!" << endl;
	}

	Vec3 getPos() const { return m_pos; }
	Vec3 getDir() const { return m_dir; }
	void setPos(const Vec3 &_pos) { m_pos = _pos; }
	void setPostProcessOption(EPostOption __postProcessOption) { postProcessOption = __postProcessOption; }

	void imageClear()
	{
		for (int i = 0; i < m_resolution[0] * m_resolution[1] * 3; i++)
		{
			m_image[i] = 0.0f;
		}
	}

	Vec2i getResolution()
	{
		return m_resolution;
	}

	Vec2i getResolution() const
	{
		return m_resolution;
	}

	void setImage(const std::vector<std::vector<int>> &count)
	{
		for (int i = 0; i < m_resolution[0]; i++)
		{
			for (int j = 0; j < m_resolution[1]; j++)
			{
				int icount = count[i][j];
				m_image[(j * m_resolution[0] + i) * 3] = icount / 10.0f;
				m_image[(j * m_resolution[0] + i) * 3 + 1] = icount / 10.0f;
				m_image[(j * m_resolution[0] + i) * 3 + 2] = icount / 10.0f;
			}
		}
	}

	void put(int i, const Path *path, const Vec3 &value)
	{
		Vec3 surfacePos = path->getLastVertPos();
		Vec3 camToSurfaceDir = (surfacePos - m_pos).normalized();

		// from world space to local Space
		Vec3 localDir = toLocal(camToSurfaceDir);
		Vec2 pixel = dirToPixel(localDir);

		if (pixel[0] < m_resolution[0] && pixel[0] >= 0 && pixel[1] < m_resolution[1] && pixel[1] >= 0)
		{
			// use a tent filter
			// find the four neighbors
			int x0 = floor(pixel[0]);
			int y0 = floor(pixel[1]);
			int x1 = pixel[0] - x0 > 0.5 ? min(m_resolution[0] - 1, x0 + 1) : max(0, x0 - 1);
			int y1 = pixel[1] - y0 > 0.5 ? min(m_resolution[1] - 1, y0 + 1) : max(0, y0 - 1);
			float w1 = abs(pixel[0] - x0 - 0.5);
			float w2 = abs(pixel[1] - y0 - 0.5);
			Vec2i pos[] = {Vec2i(x0, y0), Vec2i(x0, y1), Vec2i(x1, y1), Vec2i(x1, y0)};
			float weight[] = {(1 - w1) * (1 - w2), (1 - w1) * w2, w1 * w2, w1 * (1 - w2)};

			for (int k = 0; k < 4; k++)
			{
				int idx = pos[k][1] * m_resolution[0] + pos[k][0];
				m_imageThreads[i][idx * 3] += value[0] * weight[k];
				m_imageThreads[i][idx * 3 + 1] += value[1] * weight[k];
				m_imageThreads[i][idx * 3 + 2] += value[2] * weight[k];
			}
		}
	}

	void gathering(int mutateCount, float factor)
	{
		const int count = m_imageThreads.size();
		const int res = m_resolution[0] * m_resolution[1] * 3;
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < res; j++)
				m_image[j] += factor * m_imageThreads[i][j] * m_resolution[0] * m_resolution[1] / (mutateCount * m_A); // the m_A is the resolution factor.
		}
	}

	bool pathOcclusion(const Path *path, const Scene *scene)
	{
		for (int i = 0; i < path->getLength() - 1; i++)
		{
			const PathVert &current = path->getVert(i);
			const PathVert &next = path->getVert(i + 1);

			Vec3 pos = current.m_pos;
			Vec3 pos2 = next.m_pos;
			Vec3 dir = (pos2 - pos).normalized();
			RayDifferential ray;
			ray.time = 0;
			ray.hasDifferentials = false;

			ray = Ray(Point3(pos[0], pos[1], pos[2]), Vector3(dir[0], dir[1], dir[2]), 0);
			ray.maxt = (pos2 - pos).norm() - Epsilon;
			ray.mint = Epsilon;
			Intersection its;
			if (scene->rayIntersect(ray, its))
			{
				return true;
			}
		}
		return false;
	}

private:
	mitsuba::Transform m_cameraToSample;
	mitsuba::Transform m_sampleToCamera;

	Vec2i m_resolution;
	Vec3 m_pos;
	Vec3 m_dir;
	Vec3 m_s, m_t;
	float m_fov;
	float m_scale;
	float m_imageAspectRatio;
	float m_A; // the area of the image plane
	std::vector<float> m_image;
	std::vector<float> m_image2; // used for dPdy vis.
	std::vector<std::vector<float>> m_imageThreads;
	EPostOption postProcessOption;

	/// Convert from world coordinates to local coordinates
	inline Vec3 toLocal(const Vec3 &v) const
	{
		return Vec3(
			v.dot(m_s),
			v.dot(m_t),
			v.dot(m_dir));
	}

	inline Vec3 toWorld(const Vec3 &v) const
	{
		return m_s * v[0] + m_t * v[1] + m_dir * v[2];
	}

	inline Vec2 dirToPixel(const Vec3 &v) const
	{
		Point localV(v[0], v[1], v[2]);

		Point screenSample = m_cameraToSample(localV);
		if (screenSample.x < 0 || screenSample.x > 1 ||
			screenSample.y < 0 || screenSample.y > 1)
			return Vec2(0, 0);

		return Vec2(
			screenSample.x * m_resolution[0],
			screenSample.y * m_resolution[1]);
	}

	inline Vec3 pixelToDir(const Vec2 &pixelSample) const
	{
		Point nearP = m_sampleToCamera(Point(
			pixelSample[0] / m_resolution[0],
			pixelSample[1] / m_resolution[1], 0.0f));
		Vec3 d = Vec3(nearP[0], nearP[1], nearP[2]).normalized();
		return d;
	}
};

#endif /* __CAMERA_H_ */
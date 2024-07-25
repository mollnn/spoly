#pragma once
#if !defined(__PATH_H_)
#define __PATH_H_

#include "localEigen/Dense"
#include <fstream>
#include <iostream>
#include <vector>
#include "BSDF.h"

using namespace Eigen;
using namespace std;

typedef Eigen::Vector3f Vec3;
typedef Eigen::Vector4f Vec4;

using namespace mitsuba;

int pathType_glb = 1;

class PathVert
{

public:
	PathVert() {}
	PathVert(const Vec3 &_pos, const Vec3 &_nor, const Vec3 &_intensity) : m_pos(_pos), m_n(_nor), m_intensity(_intensity)
	{
		m_bsdf = NULL;
		m_N = m_n.normalized();
		m_N_G = m_N;
	}

	Vec4 plane(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3)
	{
		Vec3 v3_to_2 = (v2 - v3).normalized();
		Vec3 p1 = v3 + (m_pos - v3).dot(v3_to_2) * v3_to_2;
		Vec3 nA = getNormal(v2, v3, v3 + m_N_G);

		float w = nA.dot(v2);
		Vec4 L = Vec4(nA[0], nA[1], nA[2], -w);

		float length = L.dot(Vec4(v1[0], v1[1], v1[2], 1));
		L /= length;
		return L;
	}

	PathVert(const Vec3 &_pos, const Vec3 &_nor,
			 const Vec3 &vert1, const Vec3 &vert2, const Vec3 &vert3,
			 const Vec3 &vN1, const Vec3 &vN2, const Vec3 &vN3,
			 int _ishape, int _itriangle,
			 const Vec3 &fN, MyBSDF *_bsdf) : m_pos(_pos), m_n(_nor), Nalpha(vN1), Nbeta(vN2), Ngamma(vN3),
											  m_bsdf(_bsdf), m_ishape(_ishape), m_itriangle(_itriangle)
	{
		m_intensity = Vec3(1, 1, 1);
		m_N = m_n.normalized();

		m_N_G = fN;

		// compute other stuff for differential
		Lalpha = plane(vert1, vert2, vert3);
		Lbeta = plane(vert2, vert3, vert1);
		Lgamma = plane(vert3, vert1, vert2);

		Eigen::Vector4f P(m_pos[0], m_pos[1], m_pos[2], 1);
		m_alpha = Lalpha.dot(P);
		m_beta = Lbeta.dot(P);
	}

	PathVert(const Vec3 &_pos, const Vec3 &_nor,
			 const Vec3 &vert1, const Vec3 &vert2, const Vec3 &vert3,
			 const Vec3 &vN1, const Vec3 &vN2, const Vec3 &vN3,
			 const Vec3 &fN, MyBSDF *_bsdf) : m_pos(_pos), m_n(_nor), Nalpha(vN1), Nbeta(vN2), Ngamma(vN3),
											  m_bsdf(_bsdf)
	{
		m_intensity = Vec3(1, 1, 1);
		m_N = m_n.normalized();

		m_N_G = fN;

		Lalpha = plane(vert1, vert2, vert3);
		Lbeta = plane(vert2, vert3, vert1);
		Lgamma = plane(vert3, vert1, vert2);

		Eigen::Vector4f P(m_pos[0], m_pos[1], m_pos[2], 1);
		m_alpha = Lalpha.dot(P);
		m_beta = Lbeta.dot(P);
	}

	Vec3 m_pos;
	Vec3 m_N;	// this is shading normal Normalized
	Vec3 m_N_G; // this is geometry normal

	Vec3 m_intensity; // light's eta represent intensity.
	MyBSDF *m_bsdf;

	// for differentials
	Vec4 Lalpha, Lbeta, Lgamma; // the three planes
	Vec3 Nalpha, Nbeta, Ngamma; // normals at triangle vertices
	Vec3 m_n;					// unnormalized shading normal

	// for MLT
	float m_alpha, m_beta;
	int m_itriangle;
	int m_ishape;

	float alpha, beta;

private:
	Vec3 getNormal(const Vec3 &vert1, const Vec3 &vert3, const Vec3 &vert2)
	{
		Vec3 v2v3 = vert3 - vert2;
		Vec3 v1v2 = vert2 - vert1;
		Vec3 N = v2v3.cross(v1v2);
		N.normalize();
		return N;
	}
};

class Path
{
public:
	Path(vector<PathVert> &path, float pdf)
	{
		vertices.swap(path);
		m_pdf = pdf;
	}
	Path(vector<PathVert> &path, vector<int> &tid, float pdf)
	{
		vertices.swap(path);
		triangle_indices.swap(tid);
		m_pdf = pdf;
	}
	Path()
	{
	}

	~Path()
	{
		if (!vertices.empty())
			std::vector<PathVert>().swap(vertices);
	}
	void setContent(vector<PathVert> &path)
	{
		vertices.swap(path);
	}
// #define REFLECTION_PATH
// #define REFRACTION_PATH

	Vec3 computeContribution() const
	{

		const int pathLength = vertices.size();
		const PathVert &light = vertices[0];
		const PathVert &cam = vertices[pathLength - 1];
		Vec3 result = Vec3(1.0, 1.0, 1.0);
		auto cosTheta = 1.0;
		// std::cout << vertices[0].m_bsdf->getType() << std::endl;
		// if(pathLength >= 2) // costheta for calibration
		// {
		// 	if(vertices[1].m_bsdf->getType() &(MyBSDF::ERefelction | MyBSDF::EDielectricReflection))
		// 	{
		// 		Vec3 n = Vec3(0, 1.0, 0);
		// 		Vec3 l2p = (vertices[1].m_pos - light.m_pos).normalized();
		// 		cosTheta = l2p.dot(n);
		// 	}
		// 	else if(vertices[1].m_bsdf->getType() & (MyBSDF::ERefracion | MyBSDF::EDielectricRefracion))
		// 	{
		// 		Vec3 n = Vec3(0, 0, -1.0);
		// 		Vec3 l2p = (vertices[1].m_pos - light.m_pos).normalized();
		// 		cosTheta = l2p.dot(n);
		// 	}
		// }
#ifdef REFLECTION_PATH
		if (pathLength >= 2)
		{
			// reflection
			Vec3 n = Vec3(0, -1.0, 0.0);
			Vec3 l2p = (vertices[1].m_pos - light.m_pos).normalized();
			cosTheta = l2p.dot(n);
		}
#endif
#ifdef REFRACTION_PATH
		 if(pathLength >= 2)
		 {
		 	// refraction
		 	Vec3 n = Vec3(0, 0.0, -1.0);
		 	Vec3 l2p = (vertices[1].m_pos - light.m_pos).normalized();
		 	cosTheta = l2p.dot(n);
		 }
#endif
		for (int i = 1; i < pathLength - 1; i++)
		{
			const PathVert &p = vertices[i];

			Vec3 p2c = (vertices[i + 1].m_pos - p.m_pos).normalized();
			Vec3 F = p.m_bsdf->eval(p2c, p.m_N);

			result[0] *= F[0];
			result[1] *= F[1];
			result[2] *= F[2];
		}

		result[0] *= light.m_intensity[0] * cam.m_intensity[0];
		result[1] *= light.m_intensity[1] * cam.m_intensity[1];
		result[2] *= light.m_intensity[2] * cam.m_intensity[2];

		return result / (cosTheta * m_pdf);
	}

	Vec3 getLastVertPos() const { return vertices[vertices.size() - 2].m_pos; }

	int getLength() const { return vertices.size(); }

	const PathVert &getVert(int i) const { return vertices[i]; }

	mutable Vec3 ans = Vec3(0.0, 0.0, 0.0);
	mutable vector<int> triangle_indices;
	float m_pdf = 1.f;

	vector<PathVert> vertices;

private:
	// the first is light source and the last one is camera
};

#endif
#pragma once
#if !defined(__Shape_H_)
#define __Shape_H_

#include "localEigen/Dense"
#include <fstream>
#include <vector>
#include "unsupported/Eigen/AutoDiff"
#include <omp.h>
#define TINYEXR_IMPLEMENTATION
#include "tinyexr.h"
#include "path.h"
#include "interval.h"
#include <queue>
#include <mutex>
// #include "torch/torch.h"

using namespace std;
using namespace Eigen;

typedef Eigen::Vector3f Vec3;
typedef Eigen::Vector3i Vec3i;
typedef Eigen::Vector2i Vec2i;

typedef Eigen::Vector2f Vec2;
typedef Eigen::Vector4f Vec4;
// we only need two derivative (alpha and beta) to track
//-----------------------------------------------------
typedef AutoDiffScalar<Eigen::Vector2f> DFloat;

typedef Eigen::Matrix<DFloat, 4, 1> DVec4;
typedef Eigen::Matrix<DFloat, 3, 1> DVec3;
typedef Eigen::Matrix<DFloat, 2, 1> DVec2;

typedef Eigen::Matrix<DFloat, 2, 1, 0, 2, 1> DMatrix2;

// double
//-----------------------------------------------------
typedef AutoDiffScalar<Eigen::Vector2d> DDouble;

typedef Eigen::Matrix<DDouble, 4, 1> DVec4d;
typedef Eigen::Matrix<DDouble, 3, 1> DVec3d;
typedef Eigen::Matrix<DDouble, 2, 1> DVec2d;

typedef Eigen::Matrix<DDouble, 2, 1, 0, 2, 1> DMatrix2d;

// we only need four derivative (two alpha and beta) to track
//-----------------------------------------------------
typedef AutoDiffScalar<Vec4> DFloat4;
typedef Eigen::Matrix<DFloat4, 4, 1> DVec44;
typedef Eigen::Matrix<DFloat4, 3, 1> DVec43;
typedef Eigen::Matrix<DFloat4, 2, 1> DVec42;

#define M_PI 3.14159265358979323846f
#define UVGrid 100

class MyShape;

class BoundSphere
{
public:
	Vec3 pos;
	float radius;
};
class BoundCone
{
public:
	Vec3 dir;
	float gamma;
};
int sign(float x)
{
	return x < 0 ? -1 : (x == 0) ? 0
								 : 1;
}

int signed_tetra_volume(Vec3 a, Vec3 b, Vec3 c, Vec3 d)
{
	return sign(((b - a).cross(c - a)).dot(d - a) / 6.0f);
}

bool intersect_line_triangle(Vec3 q1, Vec3 q2, Vec3 p1, Vec3 p2, Vec3 p3, Vec3 &its)
{
	int s1 = signed_tetra_volume(q1, p1, p2, p3);
	int s2 = signed_tetra_volume(q2, p1, p2, p3);

	if (s1 != s2)
	{
		int s3 = signed_tetra_volume(q1, q2, p1, p2);
		int s4 = signed_tetra_volume(q1, q2, p2, p3);
		int s5 = signed_tetra_volume(q1, q2, p3, p1);

		if (s3 == s4 && s4 == s5)
		{
			Vec3 n = (p2 - p1).cross(p3 - p1);
			float t = (p1 - q1).dot(n) / (q2 - q1).dot(n);
			its = q1 + t * (q2 - q1);
			return true;
		}
	}
	return false;
}
class TreeNode;

class HFTriangle
{

public:
	HFTriangle() {}
	HFTriangle(const Vec3i &_index, const Vec3 &_normal) : index(_index), normal(_normal)
	{
		mycoordinateSystem(normal, s, t);
	}

	void setCenter(const Vec3 &_center) { center = _center; }

	Vec3i index;
	Vec3 normal;
	Vec3 s;
	Vec3 t;
	Vec3 center;
	TreeNode *node;
};

int node_id_cnt = 0;
class TreeNode
{
public:
	inline bool inside(const Vec3 &_bbmin, const Vec3 &_bbmax)
	{
		Interval3D input(_bbmin, _bbmax);
		Interval3D sub = posBox - input;
		return sub.coverZero();
	}

	inline void process(const Vec3 &_bbmin, const Vec3 &_bbmax, std::vector<int> &output)
	{
		if (inside(_bbmin, _bbmax))
		{
			if (triangleIndex == -1) // mid node
			{
				for (int i = 0; i < 4; i++)
				{
					child[i]->process(_bbmin, _bbmax, output);
				}
			}
			else
			{
				output.push_back(triangleIndex);
				output.push_back(triangleIndex + 1);
			}
		}
	}

	void getNodeLevel(int ilevel, int level, std::vector<TreeNode *> &nodeList)
	{
		if (ilevel == level || triangleIndex != -1)
			nodeList.push_back(this);
		else
		{
			for (int i = 0; i < 4; i++)
			{
				if (child[i] != NULL)
					child[i]->getNodeLevel(ilevel + 1, level, nodeList);
			}
		}
	}

	float computeposArea()
	{
		if (triangleIndex == -1) // node
			return posBox.area();
		else // reach the leaf node
			return -1.0f;
	}

	void computeSelfDirBound()
	{
		Interval3D dataBound(Vec3(1e10, 1e10, 1e10), Vec3(-1e10, -1e10, -1e10));
		if (triangleIndex != -1)
		{
			selfDirBox = dataBound;
		}
		else
		{
			int ichild = 0;
			for (int i = 0; i < 4; i++)
			{
				if (child[i] != NULL)
				{
					child[i]->computeSelfDirBound();
					ichild++;
				}
			}

			for (int i = 0; i < ichild; i++)
			{
				for (int j = 0; j < ichild; j++)
				{
					if (i == j)
					{
						dataBound = minmax(dataBound, child[i]->selfDirBox);
					}
					else
					{
						Interval3D i2j = child[j]->posBox - child[i]->posBox;
						i2j = i2j.normalized();
						dataBound = minmax(dataBound, i2j);
						Interval3D j2i = child[i]->posBox - child[j]->posBox;
						j2i = j2i.normalized();
						dataBound = minmax(dataBound, j2i);
					}
				}
			}
			selfDirBox = dataBound;
		}
	}

	size_t getSize()
	{
		size_t nodeSize = (6 * 2 + 4 + 1) * 4;
		return nodeSize;
	}

	void xlog()
	{
		nodeIndex = node_id_cnt++;

		mu.lock();
		ofs << "treenode begin " << nodeIndex << std::endl;
		mu.unlock();

		if (triangleIndex == -1)
		{

			for (int i = 0; i < 4; i++)
			{
				if (child[i] != NULL)
				{
					child[i]->xlog();
				}
			}
		}
		else
		{
			mu.lock();
			ofs << "treeleaf " << triangleIndex << std::endl;
			mu.unlock();
		}

		mu.lock();
		ofs << "treenode end " << nodeIndex << std::endl;
		;
		mu.unlock();
	}

	Interval3D posBox;
	Interval3D norBox;

	TreeNode *child[4] = {0, 0, 0, 0};
	int triangleIndex = 0;
	int triangleCount = 0;

	Interval3D selfDirBox;
	float posArea = 0;
	Vec3 center;

	int nodeIndex = -1;

	// torch::Tensor latentCode;
};

class MyShape
{

public:
	MyShape()
	{
	}

	MyShape(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;
		m_verts.resize(_height * _width);
	}

	MyShape(MyBSDF *bsdf, std::vector<Vec3> &verts, std::vector<Vec3> &vn, std::vector<HFTriangle> &triangles)
	{
		m_verts.swap(verts);
		m_vertexNormal.swap(vn);
		m_triangles.swap(triangles);

		m_bsdf1 = bsdf;
		m_bsdf2 = NULL;
	}
	~MyShape()
	{

		std::vector<Vec3>().swap(m_verts);
		std::vector<Vec3>().swap(m_vertexNormal);
		if (!m_uv.empty())
			std::vector<Vec2>().swap(m_uv);
		std::vector<HFTriangle>().swap(m_triangles);

		delete m_bsdf1;
		if (m_bsdf2 != NULL)
			delete m_bsdf2;
		// delete the tree
		if (m_root != NULL)
		{
			std::vector<TreeNode *> nodes;
			getNodes(m_root, nodes);
			for (int i = 0; i < nodes.size(); i++)
			{
				delete nodes[i];
			}
			std::vector<TreeNode *>().swap(nodes);
			m_root = NULL;
		}
	}
	void getNodes(TreeNode *node, std::vector<TreeNode *> &nodes)
	{
		if (node != NULL)
		{
			nodes.push_back(node);
			if (node->triangleIndex == -1)
			{
				for (int i = 0; i < 4; i++)
				{
					getNodes(node->child[i], nodes);
				}
			}
		}
		else
			return;
	}

	float dotvv(const Vec3 &v1, const Vec3 &v2)
	{
		return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	}

	// create a shape for the input height field.
	MyShape(const Vec3 &center, string inputHFName, float hfLength,
			const Vec3 &normal, const Shape *shape,
			float maxHeight, MyBSDF *bsdf1, MyBSDF *bsdf2, const Vec3 &camPos, const Scene *scene)
	{
		m_center = center;
		m_length = hfLength;
		m_planeNormal = normal;
		m_heightLength = maxHeight;
		mycoordinateSystem(normal, m_planeS, m_planeT);
		// v4 --- v3
		// v1 --- v2
		m_planeVerts[0] = center + (0 - hfLength * 0.5) * m_planeS + (0 - hfLength * 0.5) * m_planeT;
		m_planeVerts[1] = center + (0 - hfLength * 0.5) * m_planeS + (hfLength - hfLength * 0.5) * m_planeT;
		m_planeVerts[2] = center + (hfLength - hfLength * 0.5) * m_planeS + (hfLength - hfLength * 0.5) * m_planeT;
		m_planeVerts[3] = center + (hfLength - hfLength * 0.5) * m_planeS + (0 - hfLength * 0.5) * m_planeT;

		m_bsdf1 = bsdf1;
		m_bsdf2 = bsdf2;

		Vec3 u, v;
		coordinateSystem(m_planeNormal, u, v);
		cout << "U:" << u[0] << "," << u[1] << "," << u[2] << endl;
		cout << "V:" << v[0] << "," << v[1] << "," << v[2] << endl;

		float *image;
		const char *err = NULL;
		int ret = LoadEXR(&image, &m_width, &m_height, inputHFName.c_str(), &err);
		if (ret != TINYEXR_SUCCESS)
		{
			if (err)
			{
				fprintf(stderr, "Load EXR err: %s(code %d)\n", err, ret);
			}
			else
			{
				fprintf(stderr, "Load EXR err: code = %d\n", ret);
			}
			FreeEXRErrorMessage(err);
		}
		float maxH = 0.0;
		for (int i = 0; i < m_width * m_height; i += 4)
		{
			maxH = max(maxH, image[i]);
		}
		cout << "The maxH is: " << maxH << endl;
		const float heightScale = maxHeight / maxH;
		float pixelScale = m_length / m_width;
		cout << "The hight Scale is: " << heightScale << endl;

		for (int i = 0; i < m_width; i++)
		{
			for (int j = 0; j < m_height; j++)
			{
				int idx = (i * m_height + j) * 4;
				float value = image[idx];
				m_verts.push_back(m_center + (i * pixelScale - m_length * 0.5) * u + (j * pixelScale - m_length * 0.5) * v + value * heightScale * m_planeNormal);
				m_uv.push_back(Vec2((i + 0.5) / m_width, (j + 0.5) / m_height));
			}
		}
		computeVertexNormal();

		cout << "computeVertexNormal Done." << endl;

		for (int i = 0; i < m_width - 1; i++)
		{
			for (int j = 0; j < m_height - 1; j++)
			{
				int idx1 = i * m_height + j;
				int idx2 = i * m_height + j + 1;
				int idx3 = (i + 1) * m_height + j + 1;
				int idx4 = (i + 1) * m_height + j;
				Vec3 vert1 = Vec3(m_verts[idx1]);
				Vec3 vert2 = Vec3(m_verts[idx2]);
				Vec3 vert3 = Vec3(m_verts[idx3]);
				Vec3 vert4 = Vec3(m_verts[idx4]);
				Vec3 vn1 = Vec3(m_vertexNormal[idx1]);
				Vec3 vn2 = Vec3(m_vertexNormal[idx2]);
				Vec3 vn3 = Vec3(m_vertexNormal[idx3]);
				Vec3 vn4 = Vec3(m_vertexNormal[idx4]);

				Vec3 normal1 = getNormal(vert1, vert2, vert3);
				HFTriangle triangle1(Vec3i(idx1, idx2, idx3), normal1);
				triangle1.setCenter((m_verts[idx1] + m_verts[idx2] + m_verts[idx3]) / 3.0);

				Vec3 normal2 = getNormal(vert1, vert3, vert4);
				HFTriangle triangle2(Vec3i(idx1, idx3, idx4), normal2);
				triangle2.setCenter((m_verts[idx1] + m_verts[idx3] + m_verts[idx4]) / 3.0);

				m_triangles.push_back(triangle1);
				m_triangles.push_back(triangle2);
			}
		}

		// build a tree for the shape
		m_root = buildTree(Vec2i(0, 0), Vec2i(m_width - 1, m_width - 1));
		m_root->computeSelfDirBound();

		free(image);
	}

	MyShape(const Shape *shape, MyBSDF *bsdf1, MyBSDF *bsdf2, const Vec3 &camPos, const Scene *scene)
	{
		m_bsdf1 = bsdf1;
		m_bsdf2 = bsdf2;
		m_mesh = static_cast<const TriMesh *>(shape);

		const Point *positions = m_mesh->getVertexPositions();
		const int vertCount = m_mesh->getVertexCount();
		// mesh->getVertexTexcoords();
		const Vector *normalsProxy = m_mesh->getVertexNormals();
		// avoid potential invalid nornals.
		if (normalsProxy == nullptr)
		{
			TriMesh *m_mesh_proxy = const_cast<TriMesh *>(m_mesh);
			m_mesh_proxy->computeNormals(true);
		}
		const Vector *normals = m_mesh->getVertexNormals();
		const Point2 *uvs = m_mesh->getVertexTexcoords();

		for (int i = 0; i < vertCount; i++)
		{
			Point vert = positions[i];
			m_verts.push_back(Vec3(vert.x, vert.y, vert.z));
			Vector vn = normals[i];
			m_vertexNormal.push_back(Vec3(vn.x, vn.y, vn.z));

			if (m_mesh->hasVertexTexcoords())
			{
				Point2 uv = uvs[i];
				m_uv.push_back(Vec2(uv.x, uv.y));
			}
		}
		// cout << "Vertex transition done! \n";
		const int triCount = m_mesh->getTriangleCount();
		const Triangle *triangles = m_mesh->getTriangles();

		for (int i = 0; i < triCount; i++)
		{
			const Triangle &t = triangles[i];
			int idx0 = t.idx[0];
			int idx1 = t.idx[1];
			int idx2 = t.idx[2];

			const Point &p0 = positions[idx0];
			const Point &p1 = positions[idx1];
			const Point &p2 = positions[idx2];
			Vector side1(p1 - p0), side2(p2 - p0);
			Normal faceNormal(cross(side1, side2));

			// for the stained glass
			if (faceNormal.length() != 0)
				faceNormal /= faceNormal.length();
			HFTriangle triangle1(Vec3i(idx0, idx1, idx2), Vec3(faceNormal.x, faceNormal.y, faceNormal.z));
			triangle1.setCenter((m_verts[idx0] + m_verts[idx1] + m_verts[idx2]) / 3.0);

			m_triangles.push_back(triangle1);
		}
		// cout << "Triangle transition done! \n";

		// build a tree for the shape
		AABB posBox, norBox;

		posBox.max = Point(-1e10, -1e10, -1e10);
		posBox.min = Point(1e10, 1e10, 1e10);
		norBox.max = Point(-1e10, -1e10, -1e10);
		norBox.min = Point(1e10, 1e10, 1e10);

		std::vector<int> triangleList(m_triangles.size());
		for (int i = 0; i < m_triangles.size(); i++)
		{
			triangleList[i] = i;

			Vec3 center = m_triangles[i].center;
			Point c(center[0], center[1], center[2]);
			Vec3 centerNor = m_triangles[i].normal;
			Point cN(centerNor[0], centerNor[1], centerNor[2]);
			for (int k = 0; k < 3; k++)
			{
				posBox.min[k] = min(posBox.min[k], c[k]);
				posBox.max[k] = max(posBox.max[k], c[k]);
				norBox.min[k] = min(norBox.min[k], cN[k]);
				norBox.max[k] = max(norBox.max[k], cN[k]);
			}
		}

		const AABB &shapeAABB = shape->getAABB();
		m_root = buildTreeForMeshMedian(posBox, triangleList);

		// m_root->xlog();

		// cout << "Build tree done! \n";
	}

	void getNodeSize(TreeNode *root, long long &count)
	{
		if (!root)
			return;
		count += root->getSize();
		for (int i = 0; i < 4; i++)
		{
			if (root->child[i] != NULL)
				getNodeSize(root->child[i], count);
		}
	}

	long long getHiearchySize()
	{
		long long count = 0;
		if (m_root != NULL)
		{
			getNodeSize(m_root, count);
			return count;
		}
		return 0;
	}

	TreeNode *buildTriangleNode(HFTriangle &triangle1, int triIndex)
	{
		TreeNode *node = new TreeNode;
		node->triangleCount = 1;
		Vec3i index(triangle1.index[0], triangle1.index[1], triangle1.index[2]);

		Interval3D posBound(Vec3(1e10, 1e10, 1e10), Vec3(-1e10, -1e10, -1e10));
		Interval3D normBound(Vec3(1e10, 1e10, 1e10), Vec3(-1e10, -1e10, -1e10));
		for (int i = 0; i < 3; i++)
		{
			Vec3 vert = m_verts[index[i]];
			posBound = minmax(posBound, vert);
			Vec3 norm = m_vertexNormal[index[i]];
			normBound = minmax(normBound, norm);
			node->child[i] = NULL;
		}

		node->child[3] = NULL;
		node->triangleIndex = triIndex;
		node->posBox = posBound;
		node->norBox = normBound.normalized();

		triangle1.node = node;
		node->posArea = node->computeposArea();
		return node;
	}

	TreeNode *buildTree(const Vec2i &bbmin, const Vec2i &bbmax)
	{
		if (bbmax[0] - bbmin[0] == 1 && bbmax[1] - bbmin[1] == 1)
		{
			TreeNode *node = new TreeNode;
			int i = bbmin[0];
			int j = bbmin[1];
			// get the triangleIndex
			int triIndex = (i * (m_height - 1) + j) * 2;

			HFTriangle &triangle1 = m_triangles[triIndex];
			HFTriangle &triangle2 = m_triangles[triIndex + 1];

			node->child[0] = buildTriangleNode(triangle1, triIndex);
			node->child[1] = buildTriangleNode(triangle2, triIndex + 1);

			node->child[2] = NULL;
			node->child[3] = NULL;

			Interval3D dataBound(Vec3(1e10, 1e10, 1e10), Vec3(-1e10, -1e10, -1e10));
			Interval3D normBound(Vec3(1e10, 1e10, 1e10), Vec3(-1e10, -1e10, -1e10));
			Vec3 norm(0.0, 0.0, 0.0);

			bool visCam = false;
			for (int i = 0; i < 2; i++)
			{
				dataBound = minmax(dataBound, node->child[i]->posBox);
				normBound = minmax(normBound, node->child[i]->norBox);
			}

			node->posBox = dataBound;
			node->norBox = normBound;
			node->triangleIndex = -1;
			node->posArea = node->computeposArea();

			return node;
		}
		else
		{
			if (bbmax[0] - bbmin[0] == 1)
			{
				TreeNode *node = new TreeNode;
				node->triangleIndex = -1;

				int center = (int)std::ceil((bbmin[1] + bbmax[1]) * 0.5);

				node->child[0] = buildTree(bbmin, Vec2i(bbmax[0], center));
				node->child[1] = buildTree(Vec2i(bbmin[0], center), bbmax);

				node->child[2] = NULL;
				node->child[3] = NULL;
				Interval3D dataBound(Vec3(1e10, 1e10, 1e10), Vec3(-1e10, -1e10, -1e10));
				Interval3D normBound(Vec3(1e10, 1e10, 1e10), Vec3(-1e10, -1e10, -1e10));
				for (int i = 0; i < 2; i++)
				{
					dataBound = minmax(dataBound, node->child[i]->posBox);
					normBound = minmax(normBound, node->child[i]->norBox);
				}

				node->posBox = dataBound;
				node->norBox = normBound;
				node->posArea = node->computeposArea();

				return node;
			}
			else if (bbmax[1] - bbmin[1] == 1)
			{
				TreeNode *node = new TreeNode;
				node->triangleIndex = -1;

				int center = (int)std::ceil((bbmin[0] + bbmax[0]) * 0.5);

				node->child[0] = buildTree(bbmin, Vec2i(center, bbmax[1]));
				node->child[1] = buildTree(Vec2i(center, bbmin[1]), bbmax);
				node->child[2] = NULL;
				node->child[3] = NULL;
				Interval3D dataBound(Vec3(1e10, 1e10, 1e10), Vec3(-1e10, -1e10, -1e10));
				Interval3D normBound(Vec3(1e10, 1e10, 1e10), Vec3(-1e10, -1e10, -1e10));
				for (int i = 0; i < 2; i++)
				{
					dataBound = minmax(dataBound, node->child[i]->posBox);
					normBound = minmax(normBound, node->child[i]->norBox);
				}
				node->posBox = dataBound;
				node->norBox = normBound;
				node->posArea = node->computeposArea();

				return node;
			}
			else
			{

				TreeNode *node = new TreeNode;
				node->triangleIndex = -1;

				Vec2i center((int)std::ceil((bbmin[0] + bbmax[0]) * 0.5), (int)std::ceil((bbmin[1] + bbmax[1]) * 0.5));

				node->child[0] = buildTree(bbmin, center);
				node->child[1] = buildTree(Vec2i(bbmin[0], center[1]), Vec2i(center[0], bbmax[1]));
				node->child[2] = buildTree(center, bbmax);
				node->child[3] = buildTree(Vec2i(center[0], bbmin[1]), Vec2i(bbmax[0], center[1]));

				Interval3D dataBound(Vec3(1e10, 1e10, 1e10), Vec3(-1e10, -1e10, -1e10));
				Interval3D normBound(Vec3(1e10, 1e10, 1e10), Vec3(-1e10, -1e10, -1e10));
				for (int i = 0; i < 4; i++)
				{
					dataBound = minmax(dataBound, node->child[i]->posBox);
					normBound = minmax(normBound, node->child[i]->norBox);
				}
				node->posBox = dataBound;
				node->norBox = normBound;
				node->posArea = node->computeposArea();
				return node;
			}
		}
	}

	void computeSelfDirBound()
	{
		m_root->computeSelfDirBound();
	}

	struct AxisTriangle
	{
		AxisTriangle() {}
		AxisTriangle(float _value, int _triangle)
		{
			value = _value;
			triangle = _triangle;
		}
		float value;
		int triangle;
	};

	struct Compare_Value
	{

		Compare_Value() {}

		bool operator()(AxisTriangle const &a, AxisTriangle const &b)
		{
			return a.value < b.value;
		}
	};

	void splitMidan(const AABB &aabb, AABB &leftAABB, AABB &rightAABB,
					const std::vector<int> &triangles, bool isPos,
					std::vector<int> &left_points, std::vector<int> &right_points)
	{
		int axis = aabb.getLargestAxis();
		// sort along this axis
		std::vector<AxisTriangle> nodeList(triangles.size());
		for (int i = 0; i < triangles.size(); i++)
		{
			Vec3 center = isPos ? m_triangles[triangles[i]].center : m_triangles[triangles[i]].normal;
			nodeList[i] = AxisTriangle(center[axis], triangles[i]);
		}
		// from small to large
		std::sort(nodeList.begin(), nodeList.end(), Compare_Value());

		int const median_index = int(nodeList.size() * 0.5f);

		left_points.resize(median_index);
		right_points.resize(triangles.size() - median_index);

		for (int i = 0; i < median_index; i++)
			left_points[i] = nodeList[i].triangle;

		for (int i = 0; i < nodeList.size() - median_index; i++)
			right_points[i] = nodeList[i + median_index].triangle;

		std::vector<AxisTriangle>().swap(nodeList);

		leftAABB.max = Point(-1e10, -1e10, -1e10);
		leftAABB.min = Point(1e10, 1e10, 1e10);
		rightAABB.max = Point(-1e10, -1e10, -1e10);
		rightAABB.min = Point(1e10, 1e10, 1e10);

		for (int i = 0; i < left_points.size(); i++)
		{
			Vec3 center = isPos ? m_triangles[left_points[i]].center : m_triangles[left_points[i]].normal;

			Point c(center[0], center[1], center[2]);
			for (int k = 0; k < 3; k++)
			{
				leftAABB.min[k] = min(leftAABB.min[k], c[k]);
				leftAABB.max[k] = max(leftAABB.max[k], c[k]);
			}
		}
		for (int i = 0; i < right_points.size(); i++)
		{
			Vec3 center = isPos ? m_triangles[right_points[i]].center : m_triangles[right_points[i]].normal;
			Point c(center[0], center[1], center[2]);
			for (int k = 0; k < 3; k++)
			{
				rightAABB.min[k] = min(rightAABB.min[k], c[k]);
				rightAABB.max[k] = max(rightAABB.max[k], c[k]);
			}
		}
	}

	TreeNode *buildTreeForMeshMedian(const AABB &aabb, const std::vector<int> &triangles)
	{
		if (triangles.size() <= 4)
		{
			TreeNode *node = new TreeNode;
			node->triangleCount = triangles.size();
			node->child[0] = node->child[1] = node->child[2] = node->child[3] = NULL;

			Vec3 norm(0.0, 0.0, 0.0);
			for (int i = 0; i < triangles.size(); i++)
			{
				int triIndex = triangles[i];
				// construct a node for a triangle
				node->child[i] = buildTriangleNode(m_triangles[triIndex], triIndex);

				const HFTriangle &triangle = m_triangles[triIndex];
				const Vec3i &idx = triangle.index;
				for (int k = 0; k < 3; k++)
				{
					const Vec3 &inor = m_vertexNormal[idx[k]];
					norm += inor;
				}
			}
			norm.normalize();
			Interval3D dataBound(Vec3(1e10, 1e10, 1e10), Vec3(-1e10, -1e10, -1e10));
			Interval3D normBound(Vec3(1e10, 1e10, 1e10), Vec3(-1e10, -1e10, -1e10));
			float norCone = 0.0f;
			for (int i = 0; i < triangles.size(); i++)
			{
				dataBound = minmax(dataBound, node->child[i]->posBox);
				normBound = minmax(normBound, node->child[i]->norBox);

				int triIndex = triangles[i];
				const HFTriangle &triangle = m_triangles[triIndex];
				const Vec3i &idx = triangle.index;
				for (int k = 0; k < 3; k++)
				{
					const Vec3 &inor = m_vertexNormal[idx[k]];
					norCone = max(norCone, acos(inor.dot(norm)));
				}
			}
			node->posBox = dataBound;
			node->norBox = normBound;
			node->triangleIndex = -1;
			node->posArea = node->computeposArea();
			return node;
		}
		else
		{
			AABB temp[2];
			std::vector<int> left, right;
			splitMidan(aabb, temp[0], temp[1], triangles, true, left, right);

			AABB childAABB[4];
			std::vector<int> nodeChild[4];
			splitMidan(temp[0], childAABB[0], childAABB[1], left, true, nodeChild[0], nodeChild[1]);
			splitMidan(temp[1], childAABB[2], childAABB[3], right, true, nodeChild[2], nodeChild[3]);

			TreeNode *node = new TreeNode;
			node->triangleCount = triangles.size();
			node->triangleIndex = -1;

			for (int k = 0; k < 4; k++)
			{
				if (nodeChild[k].empty())
					node->child[k] = NULL;
				else
					node->child[k] = buildTreeForMeshMedian(childAABB[k], nodeChild[k]);
			}

			Interval3D dataBound(Vec3(1e10, 1e10, 1e10), Vec3(-1e10, -1e10, -1e10));
			Interval3D normBound(Vec3(1e10, 1e10, 1e10), Vec3(-1e10, -1e10, -1e10));
			for (int i = 0; i < 4; i++)
			{
				if (node->child[i] != NULL)
				{
					dataBound = minmax(dataBound, node->child[i]->posBox);
					normBound = minmax(normBound, node->child[i]->norBox);
				}
			}
			Vec3 norm(0.0, 0.0, 0.0);
			for (int i = 0; i < triangles.size(); i++)
			{
				int triIndex = triangles[i];
				const HFTriangle &triangle = m_triangles[triIndex];
				const Vec3i &idx = triangle.index;
				for (int k = 0; k < 3; k++)
				{
					const Vec3 &inor = m_vertexNormal[idx[k]];
					norm += inor;
				}
			}
			norm.normalize();
			float norCone = 0.0f;
			for (int i = 0; i < triangles.size(); i++)
			{
				int triIndex = triangles[i];
				const HFTriangle &triangle = m_triangles[triIndex];
				const Vec3i &idx = triangle.index;
				for (int k = 0; k < 3; k++)
				{
					const Vec3 &inor = m_vertexNormal[idx[k]];
					norCone = max(norCone, acos(inor.dot(norm)));
				}
			}

			node->posBox = dataBound;
			node->norBox = normBound;
			node->posArea = node->computeposArea();
			return node;
		}
	}

	void traverseTree(const Vec3 &bbmin, const Vec3 &bbmax, std::vector<int> &triangles)
	{
		m_root->process(bbmin, bbmax, triangles);
	}

	vector<Vec3> m_vertexNormal;
	vector<Vec3> m_verts;
	vector<Vec2> m_uv;
	vector<HFTriangle> m_triangles;
	// for BSDF
	MyBSDF *m_bsdf1;
	MyBSDF *m_bsdf2;
	TreeNode *m_root;

	Vec3 m_center;
	Vec3 m_planeNormal;
	Vec3 m_planeS;
	Vec3 m_planeT;
	Vec3 m_planeVerts[4];
	float m_length;
	float m_heightLength;

private:
	int sign(float x) const
	{
		return x < 0 ? -1 : (x == 0) ? 0
									 : 1;
	}

	int signed_tetra_volume(Vec3 a, Vec3 b, Vec3 c, Vec3 d) const
	{
		return sign(((b - a).cross(c - a)).dot(d - a) / 6.0f);
	}

	bool intersect_line_triangle(Vec3 q1, Vec3 q2, Vec3 p1, Vec3 p2, Vec3 p3, Vec3 &its) const
	{
		int s1 = signed_tetra_volume(q1, p1, p2, p3);
		int s2 = signed_tetra_volume(q2, p1, p2, p3);

		if (s1 != s2)
		{
			int s3 = signed_tetra_volume(q1, q2, p1, p2);
			int s4 = signed_tetra_volume(q1, q2, p2, p3);
			int s5 = signed_tetra_volume(q1, q2, p3, p1);

			if (s3 == s4 && s4 == s5)
			{
				Vec3 n = (p2 - p1).cross(p3 - p1);
				float t = (p1 - q1).dot(n) / (q2 - q1).dot(n);
				its = q1 + t * (q2 - q1);
				return true;
			}
		}
		return false;
	}

	Vec3 getNormal(const Vec3 &vert1, const Vec3 &vert2, const Vec3 &vert3)
	{
		Vec3 v2v3 = vert3 - vert2;
		Vec3 v1v2 = vert2 - vert1;
		Vec3 N = v2v3.cross(v1v2);
		N.normalize();

		return N;
	}

	bool is_valid(const Vec2 &projection)
	{

		return projection[0] * projection[0] + projection[1] * projection[1] < 1.0;
	}

	void computeVertexNormal()
	{
		m_vertexNormal.resize(m_width * m_height);

		for (int i = 0; i < m_width; i++)
		{
			for (int j = 0; j < m_height; j++)
			{

				Vec3 p = Vec3(m_verts[i * m_height + j]);

				Vec3 vv_minus = Vec3(m_verts[i * m_height + max(0, j - 1)]);
				Vec3 vv_plus = Vec3(m_verts[i * m_height + min(m_width - 1, j + 1)]);
				Vec3 vu_minus = Vec3(m_verts[(max(0, i - 1)) * m_height + j]);
				Vec3 vu_plus = Vec3(m_verts[min(i + 1, m_width - 1) * m_height + j]);

				Vec3 N1 = getNormal(p, vv_plus, vu_plus);
				Vec3 N2 = getNormal(p, vu_plus, vv_minus);
				Vec3 N3 = getNormal(p, vv_minus, vu_minus);
				Vec3 N4 = getNormal(p, vu_minus, vv_plus);

				//	cout << "N1:" << N1[0] << "," << N1[1] << "," << N1[2] << endl;
				m_vertexNormal[i * m_height + j] = ((N1 + N2 + N3 + N4) * 0.25f).normalized();
			}
		}
	}

	int m_width;
	int m_height;
	const TriMesh *m_mesh; // for general object only
	int m_maxSubDepth;
};

#endif
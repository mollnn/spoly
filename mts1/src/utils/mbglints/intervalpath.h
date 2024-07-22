#pragma once
#if !defined(__INTERVALPATH_H_)
#define __INTERVALPATH_H_

#include "localEigen/Dense"
#include <vector>
#include "shape.h"

using namespace Eigen;
using namespace std;

typedef Eigen::Vector3f Vec3;
#define MAX_Bounce 10

class IntervalPath
{
public:
	IntervalPath()
	{
		//	m_largestIntersection = -1;
	}
	IntervalPath(int count, TreeNode *path[])
	{
		//	m_largestIntersection = -1;
		m_countBounce = count;
		for (int i = 0; i < m_countBounce; i++)
			m_bounces[i] = path[i];
	}
	~IntervalPath()
	{
	}

	int getLength() const
	{
		return m_countBounce;
	}

	const TreeNode *getPatch(int i) const { return m_bounces[i]; }

	int findThickestArea() const
	{
		int index = -1;
		float area = 0.0f;
		// the first and the last one are light and camera
		for (int i = 1; i < getLength() - 1; i++)
		{
			if (m_bounces[i]->posArea >= area)
			{
				index = i;
				area = m_bounces[i]->posArea;
			}
		}
		return index;
	}

	// subdivide the position bound of a patch
	inline void subdivide(int index, IntervalPath subPaths[]) const
	{
		for (int i = 0; i < 4; i++)
		{
			subPaths[i].m_countBounce = m_countBounce;
			for (int j = 0; j < m_countBounce; j++)
			{
				if (j != index)
					subPaths[i].m_bounces[j] = m_bounces[j];
				else
					subPaths[i].m_bounces[j] = m_bounces[j]->child[i];
				// MAYBE null, if there are only two child nodes
			}
		}
	}

	Interval3D computeHalfV(const Interval3D &in, const Interval3D &out,
							int type, float etaIn, float etaOut) const
	{
		switch (type)
		{
		case -1:
			return (in + out).normalized();
		case -2:
			return -(in + out).normalized();
		case 1:
			return -(in * etaIn + out * etaOut).normalized();
		}
	}

	Interval3D reflect(const Interval3D &v, const Interval3D &n) const
	{
		return -v + n * (v.dot(n) * 2);
	}

	inline float signum(float value) const
	{
#if defined(__WINDOWS__)
		return (Float)_copysign(1.0, value);
#elif defined(SINGLE_PRECISION)
		return copysignf((float)1.0, value);
#elif defined(DOUBLE_PRECISION)
		return copysign((double)1.0, value);
#endif
	}

	Interval3D refract(const Interval3D &wi, const Interval3D &n, float eta) const
	{
		Interval1D cosThetaI = wi.dot(n);
		if (cosThetaI.vMin > 0)
			eta = 1.0f / eta;

		if (cosThetaI.vMax > 0)
		{
			return Interval3D(Vec3(-1e10, -1e10, -1e10), Vec3(1e10, 1e10, 1e10));
		}

		Interval1D cosThetaTSqr = Interval1D(1.0f) - (Interval1D(1.0f) - cosThetaI * cosThetaI) * (eta * eta);
		return n * (cosThetaI * eta - cosThetaTSqr.sqrt() * signum(cosThetaI.vMin)) - wi * eta;
	}

	bool isValid(int *sign, float *etaInside) const
	{

		for (int i = 1; i < getLength() - 1; i++)
		{
			if (m_bounces[i] == NULL)
				return false;
		}
		int outside = 1;
		Interval3D nP2Next2 = Interval3D(Vec3(-1e10, -1e10, -1e10), Vec3(1e10, 1e10, 1e10));
		Interval3D pre = m_bounces[0]->posBox;
		Interval3D current = m_bounces[1]->posBox;
		Interval3D P2Pre = pre - current;
		Interval3D nP2Pre = P2Pre.normalized();

		for (int i = 1; i < getLength() - 1; i++)
		{
			// type  -1 for reflection and 1 for refraction
			const int type = sign[getLength() - 1 - i];
			Interval3D next = m_bounces[i + 1]->posBox;
			Interval3D P2Next = next - current;

			if (m_bounces[i - 1] == m_bounces[i])
			{
				P2Pre = m_bounces[i - 1]->selfDirBox;
			}
			if (m_bounces[i + 1] == m_bounces[i])
			{
				P2Next = m_bounces[i]->selfDirBox;
			}
			Interval1D dotIN = m_bounces[i]->norBox.dot(P2Pre);
			Interval1D dotON = m_bounces[i]->norBox.dot(P2Next);

			float etaIn, etaOut;
			if (type == -1) // conductor reflection: always above the normal
			{
				if (dotIN.vMax <= 0.0 || dotON.vMax <= 0.0)
					return false;
				etaIn = etaOut = 1.0;
			}
			else if (type == -2) // dielectric reflection: on the same side. For TRT
			{
				if ((dotIN.vMax <= 0.0 && dotON.vMin >= 0.0) ||
					(dotIN.vMin >= 0.0 && dotON.vMax <= 0.0))
					return false;

				etaIn = etaOut = 1.0;
			}
			else // refraction
			{
				if (outside == 1) // incoming in the air
				{
					if (dotIN.vMax <= 0.0 || dotON.vMin >= 0.0)
						return false;

					etaIn = 1.0; // assume the outside of the object is air
					etaOut = etaInside[getLength() - 1 - i];
				}
				else // outgoing in the area
				{
					if (dotIN.vMin >= 0.0 || dotON.vMax <= 0.0)
						return false;

					etaIn = etaInside[getLength() - 1 - i];
					etaOut = 1.0; // assume the outside of the object is air
				}
				if (type == 1)
					outside = -outside;
			}

			Interval3D nP2Next = P2Next.normalized();

			Interval3D halfV = computeHalfV(nP2Pre, nP2Next, type, etaIn, etaOut);

			if (!(halfV - m_bounces[i]->norBox).coverZero())
			{
				return false;
			}

			if (type == -1 || type == -2)
				nP2Next2 = -reflect(nP2Pre, m_bounces[i]->norBox);
			else
				nP2Next2 = -refract(nP2Pre, m_bounces[i]->norBox, etaInside[getLength() - 1 - i]);

			nP2Pre = -nP2Next;
			nP2Pre = nP2Pre.intersect(nP2Next2);
			if (nP2Pre.isEmpty())
				return false;

			pre = current;
			current = next;
			P2Pre = -P2Next;
		}

		return true;
	}

	float getTriangleProduct() const
	{
		float ans = 1;
		for (int i = 0; i < m_countBounce; i++)
		{
			ans *= m_bounces[i]->triangleCount;
		}
		return ans;
	}

	TreeNode *m_bounces[MAX_Bounce];
	int m_countBounce;
};
#endif
#pragma once
#if !defined(__INTERVAL_H_)
#define __INTERVAL_H_

#include "localEigen/Dense"

using namespace Eigen;
using namespace std;

typedef Eigen::Vector3f Vec3;
typedef Eigen::Vector2f Vec2;

class Interval1D
{
public:
	Interval1D() : vMin(-1e9), vMax(1e9){};
	Interval1D(float _min, float _max) : vMin(_min), vMax(_max) {}
	Interval1D(float _min) : vMin(_min), vMax(_min) {}
	//[x_1, x_2] + [y_1, y_2] = [x_1+y_1, x_2+y_2]
	/// Add two vectors and return the result

	inline Interval1D operator+(const Interval1D &b) const
	{
		return Interval1D(vMin + b.vMin, vMax + b.vMax);
	}

	//[x_1, x_2] - [y_1, y_2] = [x_1-y_2, x_2-y_1]
	inline Interval1D operator-(const Interval1D &b) const
	{
		return Interval1D(vMin - b.vMax, vMax - b.vMin);
	}
	inline Interval1D operator-(const float &b) const
	{
		return Interval1D(vMin - b, vMax - b);
	}

	//[x_1, x_2] \cdot [y_1, y_2] = [\min(x_1 y_1,x_1 y_2,x_2 y_1,x_2 y_2), \max(x_1 y_1,x_1 y_2,x_2 y_1,x_2 y_2)]
	inline Interval1D operator*(const Interval1D &b) const
	{
		return Interval1D(min(min(vMin * b.vMin, vMin * b.vMax), min(vMax * b.vMin, vMax * b.vMax)),
						  max(max(vMin * b.vMin, vMin * b.vMax), max(vMax * b.vMin, vMax * b.vMax)));
	}

	inline Interval1D operator*(float b) const
	{
		return Interval1D(min(vMin * b, vMax * b), max(vMin * b, vMax * b));
	}

	inline Interval1D inverse(const Interval1D &b) const
	{
		if (b.vMin > 0 || b.vMax < 0) // 0 is not in the range
		{
			return Interval1D(1.0 / b.vMax, 1.0 / b.vMin);
		}
		else
		{
			return Interval1D(-1e10, 1e10);
		}
	}

	inline Interval1D operator/(const Interval1D &b) const
	{
		Interval1D inverseB = inverse(b);
		Interval1D result(vMin, vMax);
		return result * inverseB;
	}

	inline Interval1D sqrt() const
	{
		return Interval1D(std::sqrt(vMin), std::sqrt(vMax));
	}

	inline Interval1D square() const
	{
		float vMin_2 = vMin * vMin;
		float vMax_2 = vMax * vMax;
		float maxSquare = max(vMin_2, vMax_2);

		if (vMin < 0 && vMax > 0)
		{
			return Interval1D(1e-7, maxSquare);
		}
		else
		{
			return Interval1D(min(vMin_2, vMax_2), maxSquare);
		}
	}
	/// Return a negated version of the vector
	inline Interval1D operator-() const
	{
		return Interval1D(-vMax, -vMin);
	}
	inline float length() const
	{
		return vMax - vMin;
	}

	inline Interval1D clampZero()
	{
		return Interval1D(std::max(vMin, 0.0f), std::max(vMax, 0.0f));
	}

	inline Interval1D intersect(const Interval1D &b)
	{
		return Interval1D(std::max(vMin, b.vMin), std::min(vMax, b.vMax));
	}

	inline Interval1D acos()
	{
		return Interval1D(std::acos(vMax), std::acos(vMin));
	}

	inline bool coverZero()
	{
		if (vMin > 0 || vMax < 0)
		{
			return false;
		}
		return true;
	}
	inline bool subset(const Interval1D &b)
	{
		return vMin >= b.vMin && vMax <= b.vMax;
	}

	inline bool empty()
	{
		return vMin > vMax;
	}

	inline float mid()
	{
		return (vMin + vMax) / 2;
	}
	float vMin;
	float vMax;
};

inline Interval1D minmax(const Interval1D &a, const Interval1D &b)
{
	return Interval1D(min(a.vMin, b.vMin), max(a.vMax, b.vMax));
}
inline Interval1D minmax(const Interval1D &a, const float &b)
{
	return Interval1D(min(a.vMin, b), max(a.vMax, b));
}

inline Interval1D minus1D(const float &a, const Interval1D &b)
{
	return Interval1D(a - b.vMax, a - b.vMin);
}

class Interval3D
{
public:
	Interval3D() {}
	Interval3D(const Vec3 &_min, const Vec3 &_max)
	{
		for (int i = 0; i < 3; i++)
		{
			value[i] = Interval1D(_min[i], _max[i]);
		}
	}
	Interval3D(const Vec3 &_value)
	{
		for (int i = 0; i < 3; i++)
		{
			value[i] = Interval1D(_value[i], _value[i]);
		}
	}
	Interval3D(const Interval1D v[])
	{
		for (int i = 0; i < 3; i++)
		{
			value[i] = v[i];
		}
	}

	inline Interval1D dot(const Interval3D &b)
	{
		return value[0] * b.value[0] + value[1] * b.value[1] + value[2] * b.value[2];
	}

	inline Interval1D dot(const Interval3D &b) const
	{
		return value[0] * b.value[0] + value[1] * b.value[1] + value[2] * b.value[2];
	}

	inline Interval3D operator+(const Interval3D &b) const
	{
		Interval1D result[3];
		for (int i = 0; i < 3; i++)
		{
			result[i] = value[i] + b.value[i];
		}
		return Interval3D(result);
	}

	inline Interval3D operator-(const Interval3D &b) const
	{
		Interval1D result[3];
		for (int i = 0; i < 3; i++)
		{
			result[i] = value[i] - b.value[i];
		}
		return Interval3D(result);
	}

	inline Interval3D operator*(float b) const
	{
		Interval1D result[3];
		for (int i = 0; i < 3; i++)
		{
			result[i] = value[i] * b;
		}
		return Interval3D(result);
	}

	inline Interval3D operator*(const Interval1D &b) const
	{

		Interval1D result[3];
		for (int i = 0; i < 3; i++)
		{
			result[i] = value[i] * b;
		}
		return Interval3D(result);
	}

	inline Interval3D operator/(const Interval1D &b) const
	{
		Interval1D temp = b.inverse(b);
		Interval1D result[3];
		for (int i = 0; i < 3; i++)
		{
			result[i] = value[i] * temp;
		}
		return Interval3D(result);
	}

	inline Interval3D operator-(const Vec3 &b) const
	{
		Interval1D result[3];
		for (int i = 0; i < 3; i++)
		{
			result[i] = value[i] - b[i];
		}
		return Interval3D(result);
	}

	inline Interval1D squaredNorm()
	{
		Interval1D result = (value[0].square() + value[1].square() + value[2].square());
		return result;
	}

	inline Interval1D norm()
	{
		Interval1D result = (value[0].square() + value[1].square() + value[2].square());
		result.vMin = sqrt(result.vMin);
		result.vMax = sqrt(result.vMax);
		return result;
	}

	inline Interval1D norm3()
	{
		Interval1D result = (value[0].square() + value[1].square() + value[2].square());
		result.vMin = pow(sqrt(result.vMin), 3.0f);
		result.vMax = pow(sqrt(result.vMax), 3.0f);

		return result;
	}

	inline Interval3D normalized()
	{
		Interval1D lengthSquare = squaredNorm();
		if (lengthSquare.vMin < 0)
			return Interval3D(Vec3(-1, -1, -1), Vec3(1, 1, 1));

		Interval1D length = lengthSquare.sqrt();
		Interval1D invLength = length.inverse(length);
		Interval1D result[3];
		for (int i = 0; i < 3; i++)
		{
			result[i] = value[i] * invLength;
			result[i].vMin = std::max(result[i].vMin, -1.0f);
			result[i].vMax = std::min(result[i].vMax, 1.0f);
		}

		return Interval3D(result);
	}

	inline bool coverZero()
	{
		for (int i = 0; i < 3; i++)
		{
			if (value[i].vMin > 0 || value[i].vMax < 0)
			{
				return false;
			}
		}
		return true;
	}
	inline bool smallerThan(float threshold)
	{
		for (int i = 0; i < 3; i++)
		{
			if (value[i].vMin > threshold || value[i].vMax < -threshold)
			{
				return false;
			}
		}
		return true;
	}
	inline bool valid()
	{
		for (int i = 0; i < 3; i++)
		{
			if (value[i].vMin > value[i].vMax)
			{
				return false;
			}
		}
		return true;
	}

	inline float area()
	{
		// surface area
		float area = value[0].length() * value[1].length() +
					 value[0].length() * value[2].length() +
					 value[1].length() * value[2].length();
		area *= 2;
		return area;
	}

	inline float volumeSphere()
	{
		float maxDist = -1;
		for (int i = 0; i < 3; i++)
		{
			float temp = value[i].vMax - value[i].vMin;
			maxDist = max(maxDist, temp);
		}
		return 4 / 3.0f * M_PI * pow(maxDist * 0.5, 3.0);
	}

	inline Interval3D operator-() const
	{
		Interval1D result[3];
		for (int i = 0; i < 3; i++)
		{
			result[i] = -value[i];
		}

		return Interval3D(result);
	}

	inline Interval3D intersect(const Interval3D &b)
	{
		Interval1D result[3];
		for (int i = 0; i < 3; i++)
		{
			result[i] = value[i].intersect(b.value[i]);
		}
		return Interval3D(result);
	}

	inline bool isEmpty()
	{
		for (int i = 0; i < 3; i++)
		{
			if (value[i].vMin > value[i].vMax)
				return true;
		}
		return false;
	}

	inline Vec3 center(float &radius)
	{
		Vec3 result;
		float r = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			result[i] = (value[i].vMin + value[i].vMax) * 0.5;
			float temp = value[i].vMin - result[i];
			r += temp * temp;
		}
		radius = sqrtf(r);
		return result;
	}

	Interval1D value[3];
};

inline Interval3D minmax(const Interval3D &a, const Interval3D &b)
{
	Interval1D result[3];
	for (int i = 0; i < 3; i++)
	{
		result[i] = minmax(a.value[i], b.value[i]);
	}
	return Interval3D(result);
}

inline Interval3D minmax(const Interval3D &a, const Vec3 &b)
{
	Interval1D result[3];
	for (int i = 0; i < 3; i++)
	{
		result[i] = minmax(a.value[i], b[i]);
	}
	return Interval3D(result);
}

inline Interval3D reflect(const Interval3D &wi, const Interval3D &n)
{
	return n * (wi.dot(n) * 2) - wi;
}

inline Interval3D minus3D(const Vec3 &a, const Interval3D &b)
{
	Interval1D result[3];
	for (int i = 0; i < 3; i++)
	{
		result[i] = minus1D(a[i], b.value[i]);
	}
	return Interval3D(result);
}

inline Interval3D mul(const Interval1D &a, const Vec3 &b)
{
	Interval1D result[3];
	for (int i = 0; i < 3; i++)
	{
		result[i] = a * b[i];
	}
	return Interval3D(result);
}

inline Interval3D minus(const Vec3 &a, const Interval3D &b)
{
	Interval1D result[3];
	for (int i = 0; i < 3; i++)
	{
		result[i] = Interval1D(a[i]) - b.value[i];
	}
	return Interval3D(result);
}

class Interval2D
{
public:
	Interval2D(){};
	Interval2D(const Interval1D v[])
	{
		for (int i = 0; i < 2; i++)
		{
			value[i] = v[i];
		}
	}

	Interval2D(const Vec2 &_min, const Vec2 &_max)
	{
		for (int i = 0; i < 2; i++)
		{
			value[i] = Interval1D(_min[i], _max[i]);
		}
	}

	Interval2D(const Vec2 &_value)
	{
		for (int i = 0; i < 2; i++)
		{
			value[i] = Interval1D(_value[i], _value[i]);
		}
	}

	inline Interval2D operator+(const Interval2D &b) const
	{
		Interval1D result[2];
		for (int i = 0; i < 2; i++)
		{
			result[i] = value[i] + b.value[i];
		}
		return Interval2D(result);
	}

	inline Interval2D operator-(const Interval2D &b) const
	{
		Interval1D result[2];
		for (int i = 0; i < 2; i++)
		{
			result[i] = value[i] - b.value[i];
		}
		return Interval2D(result);
	}

	inline Interval2D operator-(const Vec2 &b) const
	{
		Interval1D result[2];
		for (int i = 0; i < 2; i++)
		{
			result[i] = value[i] - b[i];
		}
		return Interval2D(result);
	}

	inline Interval2D operator*(float b) const
	{
		Interval1D result[2];
		for (int i = 0; i < 2; i++)
		{
			result[i] = value[i] * b;
		}
		return Interval2D(result);
	}

	inline Interval2D operator*(const Interval1D &b) const
	{

		Interval1D result[2];
		for (int i = 0; i < 2; i++)
		{
			result[i] = value[i] * b;
		}
		return Interval2D(result);
	}

	inline Interval2D operator/(const Interval1D &b) const
	{
		Interval1D temp = b.inverse(b);
		Interval1D result[2];
		for (int i = 0; i < 2; i++)
		{
			result[i] = value[i] * temp;
		}
		return Interval2D(result);
	}

	inline Interval1D inverse(const Interval1D &b) const
	{
		if (b.vMin > 0 || b.vMax < 0) // 0 is not in the range
		{
			return Interval1D(1.0 / b.vMax, 1.0 / b.vMin);
		}
		else
		{
			//	cout << "Infinity" << endl;
			return Interval1D(-1e10, 1e10);
		}
	}

	inline Interval1D squaredNorm()
	{
		Interval1D result = (value[0].square() + value[1].square());
		return result;
	}

	inline Interval2D square()
	{
		Interval1D result[2];
		for (int i = 0; i < 2; i++)
		{
			result[i] = value[i].square();
		}
		return Interval2D(result);
	}

	inline Interval2D normalized()
	{
		Interval1D lengthSquare = squaredNorm();
		if (lengthSquare.vMin < 0)
			return Interval2D(Vec2(-1, -1), Vec2(1, 1));

		Interval1D length = lengthSquare.sqrt();
		Interval1D invLength = length.inverse(length);
		Interval1D result[2];
		for (int i = 0; i < 2; i++)
		{
			result[i] = value[i] * invLength;
			result[i].vMin = std::max(result[i].vMin, -1.0f);
			result[i].vMax = std::min(result[i].vMax, 1.0f);
		}

		return Interval2D(result);
	}

	inline Interval2D intersect(const Interval2D &b)
	{
		Interval1D result[2];
		for (int i = 0; i < 2; i++)
		{
			result[i] = value[i].intersect(b.value[i]);
		}
		return Interval2D(result);
	}

	inline bool coverZero()
	{
		for (int i = 0; i < 2; i++)
		{
			if (value[i].vMin > 0 || value[i].vMax < 0)
			{
				return false;
			}
		}
		return true;

		return true;
	}

	inline Vec2 mid()
	{
		return Vec2((value[0].vMin + value[0].vMax) / 2, (value[1].vMin + value[1].vMax) / 2);
	}

	inline bool empty()
	{
		for (int i = 0; i < 2; i++)
		{
			if (value[i].vMin > value[i].vMax)
				return true;
		}
		return false;
	}

	inline bool subset(const Interval2D &b)
	{
		for (int i = 0; i < 2; i++)
		{
			if (!value[i].subset(b.value[i]))
				return false;
		}
		return true;
	}

	Interval1D value[2];
};

class Interval4D
{
public:
	Interval4D(){};

	Interval4D(const Interval1D v[])
	{
		for (int i = 0; i < dimension; i++)
		{
			value[i] = v[i];
		}
	}

	Interval4D(const Vec4 &_min, const Vec4 &_max)
	{
		for (int i = 0; i < dimension; i++)
		{
			value[i] = Interval1D(_min[i], _max[i]);
		}
	}

	Interval4D(const Vec4 &_value)
	{
		for (int i = 0; i < dimension; i++)
		{
			value[i] = Interval1D(_value[i], _value[i]);
		}
	}

	inline Interval4D operator+(const Interval4D &b) const
	{
		Interval1D result[4];
		for (int i = 0; i < dimension; i++)
		{
			result[i] = value[i] + b.value[i];
		}
		return Interval4D(result);
	}

	inline Interval4D operator-(const Interval4D &b) const
	{
		Interval1D result[4];
		for (int i = 0; i < 4; i++)
		{
			result[i] = value[i] - b.value[i];
		}
		return Interval4D(result);
	}

	inline Interval4D operator-(const Vec4 &b) const
	{
		Interval1D result[4];
		for (int i = 0; i < 4; i++)
		{
			result[i] = value[i] - b[i];
		}
		return Interval4D(result);
	}

	inline Interval4D operator*(float b) const
	{
		Interval1D result[4];
		for (int i = 0; i < 4; i++)
		{
			result[i] = value[i] * b;
		}
		return Interval4D(result);
	}

	inline Interval4D operator*(const Interval1D &b) const
	{

		Interval1D result[4];
		for (int i = 0; i < 4; i++)
		{
			result[i] = value[i] * b;
		}
		return Interval4D(result);
	}
	inline Interval4D operator/(const Interval1D &b) const
	{
		Interval1D temp = b.inverse(b);
		Interval1D result[4];
		for (int i = 0; i < 4; i++)
		{
			result[i] = value[i] * temp;
		}
		return Interval4D(result);
	}

	inline Interval1D squaredNorm()
	{
		Interval1D result = (value[0].square() + value[1].square() + value[2].square() + value[3].square());
		return result;
	}

	inline Interval4D square()
	{
		Interval1D result[4];
		for (int i = 0; i < 4; i++)
		{
			result[i] = value[i].square();
		}
		return Interval4D(result);
	}

	inline Interval4D normalized()
	{
		Interval1D lengthSquare = squaredNorm();
		if (lengthSquare.vMin < 0)
			return Interval4D(Vec4(-1, -1, -1, -1), Vec4(1, 1, 1, 1));

		Interval1D length = lengthSquare.sqrt();
		Interval1D invLength = length.inverse(length);
		Interval1D result[4];
		for (int i = 0; i < 4; i++)
		{
			result[i] = value[i] * invLength;
			result[i].vMin = std::max(result[i].vMin, -1.0f);
			result[i].vMax = std::min(result[i].vMax, 1.0f);
		}

		return Interval4D(result);
	}

	inline Interval4D intersect(const Interval4D &b)
	{
		Interval1D result[4];
		for (int i = 0; i < 4; i++)
		{
			result[i] = value[i].intersect(b.value[i]);
		}
		return Interval4D(result);
	}

	inline bool coverZero()
	{
		for (int i = 0; i < 4; i++)
		{
			if (value[i].vMin > 0 || value[i].vMax < 0)
			{
				return false;
			}
		}
		return true;

		return true;
	}

	inline Vec4 mid()
	{
		return Vec4((value[0].vMin + value[0].vMax) / 2, (value[1].vMin + value[1].vMax) / 2, (value[2].vMin + value[2].vMax) / 2, (value[3].vMin + value[3].vMax) / 2);
	}

	inline bool empty()
	{
		for (int i = 0; i < 4; i++)
		{
			if (value[i].vMin > value[i].vMax)
				return true;
		}
		return false;
	}

	inline bool subset(const Interval4D &b)
	{
		for (int i = 0; i < 4; i++)
		{
			if (!value[i].subset(b.value[i]))
				return false;
		}
		return true;
	}

	Interval1D value[4];
	const int dimension = 4;
};

#endif
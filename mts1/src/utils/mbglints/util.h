/*
	This file is part of Mitsuba, a physically based rendering system.

	Copyright (c) 2007-2014 by Wenzel Jakob and others.

	Mitsuba is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License Version 3
	as published by the Free Software Foundation.

	Mitsuba is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#if !defined(__UTIL_H_)
#define __UTIL_H_

#include <Eigen/Dense>
#include <vector>

using namespace Eigen;

Eigen::Vector3f myreflect(const Eigen::Vector3f &wi, const Eigen::Vector3f &n);
Eigen::Vector3f myrefract(const Eigen::Vector3f &wi, const Eigen::Vector3f &n, float eta);
void coordinateSystem(const Eigen::Vector3f &a, Eigen::Vector3f &b, Eigen::Vector3f &c);
void mycoordinateSystem(const Eigen::Vector3f &a, Eigen::Vector3f &b, Eigen::Vector3f &c);
float myfresnelDielectricExt(float cosThetaI,
							 float &cosThetaT, float eta);
float myfresnelDielectric(float cosThetaI,
						  float cosThetaT, float eta);
Eigen::Vector3f myfresnelConductorExact(float cosThetaI,
										const Eigen::Vector3f &eta, const Eigen::Vector3f &k);

inline Vector3f divide(const Vector3f &first, const Vector3f &other)
{
	Vector3f value = first;

	for (int i = 0; i < 3; i++)
		value[i] /= other[i];

	return value;
}
inline Vector3f multiply(const Vector3f &first, const Vector3f &other)
{
	Vector3f value = first;

	for (int i = 0; i < 3; i++)
		value[i] *= other[i];

	return value;
}

inline Vector3f sqrt(const Vector3f &first)
{
	Vector3f value = first;

	for (int i = 0; i < 3; i++)
		value[i] = sqrt(value[i]);

	return value;
}
float myfresnelDielectric(float cosThetaI, float cosThetaT, float eta)
{
	if (eta == 1)
		return 0.0f;

	float Rs = (cosThetaI - eta * cosThetaT) / (cosThetaI + eta * cosThetaT);
	float Rp = (eta * cosThetaI - cosThetaT) / (eta * cosThetaI + cosThetaT);

	/* No polarization -- return the unpolarized reflectance */
	return 0.5f * (Rs * Rs + Rp * Rp);
}

float myfresnelDielectricExt(float cosThetaI_, float &cosThetaT_, float eta)
{
	if (eta == 1)
	{
		cosThetaT_ = -cosThetaI_;
		return 0.0f;
	}

	/* Using Snell's law, calculate the squared sine of the
	angle between the Vector3f  and the transmitted ray */
	float scale = (cosThetaI_ > 0) ? 1 / eta : eta,
		  cosThetaTSqr = 1 - (1 - cosThetaI_ * cosThetaI_) * (scale * scale);

	/* Check for total internal reflection */
	if (cosThetaTSqr <= 0.0f)
	{
		cosThetaT_ = 0.0f;
		return 1.0f;
	}

	/* Find the absolute cosines of the incident/transmitted rays */
	float cosThetaI = std::abs(cosThetaI_);
	float cosThetaT = std::sqrt(cosThetaTSqr);

	float Rs = (cosThetaI - eta * cosThetaT) / (cosThetaI + eta * cosThetaT);
	float Rp = (eta * cosThetaI - cosThetaT) / (eta * cosThetaI + cosThetaT);

	cosThetaT_ = (cosThetaI_ > 0) ? -cosThetaT : cosThetaT;

	/* No polarization -- return the unpolarized reflectance */
	return 0.5f * (Rs * Rs + Rp * Rp);
}

Eigen::Vector3f myfresnelConductorExact(float cosThetaI, const Eigen::Vector3f &eta, const Eigen::Vector3f &k)
{
	/* Modified from "Optics" by K.D. Moeller, University Science Books, 1988 */

	float cosThetaI2 = cosThetaI * cosThetaI,
		  sinThetaI2 = 1 - cosThetaI2,
		  sinThetaI4 = sinThetaI2 * sinThetaI2;

	Eigen::Vector3f temp1 = multiply(eta, eta) - multiply(k, k) - Eigen::Vector3f(sinThetaI2, sinThetaI2, sinThetaI2),
					a2pb2 = sqrt(multiply(temp1, temp1) + multiply(multiply(k, k), multiply(eta, eta)) * 4),
					a = sqrt((a2pb2 + temp1) * 0.5f);

	Eigen::Vector3f term1 = a2pb2 + Eigen::Vector3f(cosThetaI2, cosThetaI2, cosThetaI2),
					term2 = a * (2 * cosThetaI);

	Eigen::Vector3f Rs2 = divide((term1 - term2), (term1 + term2));
	// do not find the same function in eigan

	Eigen::Vector3f term3 = a2pb2 * cosThetaI2 + Eigen::Vector3f(sinThetaI4, sinThetaI4, sinThetaI4),
					term4 = term2 * sinThetaI2;

	Eigen::Vector3f Rp2 = divide(multiply(Rs2, (term3 - term4)), (term3 + term4));

	return 0.5f * (Rp2 + Rs2);
}

Eigen::Vector3f myreflect(const Eigen::Vector3f &wi, const Eigen::Vector3f &n)
{
	return 2 * wi.dot(n) * n - wi;
}

inline float signum(float value)
{
#if defined(__WINDOWS__)
	return (float)_copysign(1.0, value);
#elif defined(SINGLE_PRECISION)
	return copysignf((float)1.0, value);
#elif defined(DOUBLE_PRECISION)
	return copysign((double)1.0, value);
#endif
}

Eigen::Vector3f myrefract(const Eigen::Vector3f &wi, const Eigen::Vector3f &n, float eta)
{
	if (eta == 1)
		return -wi;

	float cosThetaI = wi.dot(n);
	if (cosThetaI > 0)
		eta = 1 / eta;

	/* Using Snell's law, calculate the squared sine of the
	angle between the Vector3f  and the transmitted ray */
	float cosThetaTSqr = 1 - (1 - cosThetaI * cosThetaI) * (eta * eta);

	/* Check for total internal reflection */
	if (cosThetaTSqr <= 0.0f)
		return Eigen::Vector3f(0.0f, 0.0, 0.0);

	return n * (cosThetaI * eta - signum(cosThetaI) * std::sqrt(cosThetaTSqr)) - wi * eta;
}

void coordinateSystem(const Vector3f &a, Vector3f &b, Vector3f &c)
{
	if (std::abs(a[0]) > std::abs(a[1]))
	{
		float invLen = 1.0f / std::sqrt(a[0] * a[0] + a[2] * a[2]);
		c = Vector3f(a[2] * invLen, 0.0f, -a[0] * invLen);
	}
	else
	{
		float invLen = 1.0f / std::sqrt(a[1] * a[1] + a[2] * a[2]);
		c = Vector3f(0.0f, a[2] * invLen, -a[1] * invLen);
	}
	b = c.cross(a);
}

void mycoordinateSystem(const Vector3f &a, Vector3f &b, Vector3f &c)
{
	if (std::abs(a[0]) > std::abs(a[1]))
	{
		float invLen = 1.0f / std::sqrt(a[0] * a[0] + a[2] * a[2]);
		c = Vector3f(a[2] * invLen, 0.0f, -a[0] * invLen);
	}
	else
	{
		float invLen = 1.0f / std::sqrt(a[1] * a[1] + a[2] * a[2]);
		c = Vector3f(0.0f, a[2] * invLen, -a[1] * invLen);
	}
	b = c.cross(a);
}

#endif /* __MITSUBA_CORE_UTIL_H_ */

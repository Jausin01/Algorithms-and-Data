#pragma once
#include "Array.h"
#include <array>
#include <cmath>

struct Vector3
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		std::array<float, 3> v;
	};

	// [x][y][z]
	Vector3() : x(0), y(0), z(0) {}
	Vector3(float s) : x(s), y(s), z(s) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	Vector3 operator-() const { return { -x, -y, -z }; }
	Vector3 operator+(const Vector3& rhs) const { return { x + rhs.x, y + rhs.y, z + rhs.z }; }
	Vector3 operator-(const Vector3& rhs) const { return { x - rhs.x, y - rhs.y, z - rhs.z }; }
	Vector3 operator*(float s) const { return { x * s, y * s, z * s }; }
	Vector3 operator/(float s) const { return { x / s, y / s, z / s }; }

	// <operator>= same line update operator overload
	Vector3& operator+=(const Vector3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
	Vector3& operator-=(const Vector3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
	Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
	Vector3& operator/=(float s) { x /= s; y /= s; z /= s; return *this; }

	// helper functions
	float MagnitudeSqr() const { return (x * x) + (y * y) + (z * z); }
	float Magnitude() const { return sqrtf(MagnitudeSqr()); }
	float DistanceSqr(const Vector3& rhs) const { return (x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y) + (z - rhs.z) * (z - rhs.z); }
	float Distance(const Vector3& rhs) const { return sqrtf(DistanceSqr(rhs)); }
};

#pragma once
#include <algorithm>
#include <cmath>
#include "Vector.hpp"
typedef double f64;
typedef float f32;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
namespace geometry
{
	class Calc
	{
		public:
			static f64 Degrees(f64 angle);
			static f64 Diagonal(f64 width, f64 height);
			static f64 Distance(const Vector& a, const Vector& b);
			static f64 Distance(const Line& a, const Vector& b);
			static f64 GetAngle(const Vector& a, const Vector& b, const Vector& c);
			static f64 GetAngle(f64 slope);
			static f64 GetAngle(const Vector& center, const Vector& Vector);
			static Vector GetVectorOnCircle(const Vector& center, f64 radius, f64 angle);
			static f64 GetSlope(const Vector& a, const Vector& b);
			static bool Intersecting(const Line& a, const Line& b, bool isInfLine = false);
			static Vector VectorOfIntersect(const Line& a, const Line& b, bool isInfLine = false);
	};
}
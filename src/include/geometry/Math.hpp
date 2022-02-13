#pragma once
#include <tuple>
#include <exception>
#include <type_traits>
#include "Vector.hpp"
typedef double f64;
typedef float f32;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
namespace geometry
{

	struct Matrix22
	{
		Vector iHat;
		Vector jHat;
		f64& a = iHat.x;
		f64& c = iHat.y;
		f64& b = jHat.x;
		f64& d = jHat.y;
		Matrix22();
		Matrix22(f64 radians);
		Matrix22(f64 a, f64 b, f64 c, f64 d);
		Matrix22(const Vector& iHat, const Vector& jHat);
		Vector AxisX() const;
		Vector AxisY() const;
		void Set(f64 radians);
		void Set(f64 a, f64 b, f64 c, f64 d);
		Matrix22 Transpose() const;
		Matrix22& operator=(const Matrix22& other);
		bool operator==(const Matrix22& other) const;
		bool operator!=(const Matrix22& other) const;
		Vector operator*(const Vector& v) const;
		Matrix22 operator*(const Matrix22& m) const;
	};

	// | a b c |
	// | d e f |
	// | g h i |
	struct Matrix33
	{
		Vector3 iHat; //a, d, g
		Vector3 jHat; //b, e, h
		Vector3 kHat; //c, f, i
		f64& a = iHat.x, d = iHat.y, g = iHat.z;
		f64& b = jHat.x, e = jHat.y, h = jHat.z;
		f64& c = kHat.x, f = kHat.y, i = kHat.z;
		Matrix33();
		Matrix33(const Matrix22& mat22);
		Matrix33(const Matrix33& mat33);
		Matrix33(const f64& a, const f64& d, const f64& g, const f64& b, const f64& e, const f64& h, const f64& c, const f64& f, const f64& i);
		Matrix33(const Vector3& iHat, const Vector3& jHat, const Vector3& kHat);
		Matrix33& operator=(const Matrix33& other);
		Vector3 AxisX() const;
		Vector3 AxisY() const;
		Vector3 AxisZ() const;
		Matrix33 Transpose() const;
		bool operator==(const Matrix33& other) const;
		bool operator!=(const Matrix33& other) const;
		Vector3 operator*(const Vector3& v) const;
		Matrix33 operator*(const Matrix33& other) const;
	};
}
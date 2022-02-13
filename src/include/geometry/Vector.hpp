#pragma once
#include <cmath>
#include <vector>
#include <tuple>
typedef double f64;
typedef float f32;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
namespace geometry
{
	class Line;
	class Vector
	{
		public:
			f64 x;
			f64 y;
			Vector();
			Vector(f64 x, f64 y);
			f64 magnitude() const;
			f64 magnitudeSquared() const;
			void Normalize();
			Vector Normalized() const;
			f64 Cross(const Vector& v) const noexcept;
			static Vector Cross(const Vector& v, const f64& s);
			static Vector Cross(const f64& s, const Vector& v);
			f64 Dot(const Vector& v) const;
			Vector operator-() const noexcept;
			Vector operator+() const noexcept;
			bool operator==(const Vector& v) const noexcept;
			bool operator!=(const Vector& v) const noexcept;
			Vector operator-(const Vector& v) const noexcept;
			Vector operator-(const f64& d) const noexcept;
			void operator-=(const Vector& v) noexcept;
			void operator-=(const f64& d) noexcept;
			Vector operator+(const Vector& v) const noexcept;
			Vector operator+(const f64& d) const noexcept;
			void operator+=(const Vector& v) noexcept;
			void operator+=(const f64& d) noexcept;
			Vector operator/(const Vector& v) const noexcept;
			Vector operator/(const f64& d) const noexcept;
			void operator/=(const Vector& v) noexcept;
			void operator/=(const f64& d) noexcept;
			Vector operator*(const Vector& v) const noexcept;
			Vector operator*(const f64& d) const noexcept;
			void operator*=(const Vector& v) noexcept;
			void operator*=(const f64& d) noexcept;
			bool operator^(Line l) const;
			bool operator<(const Vector& v) const noexcept;
			bool operator>(const Vector& v) const noexcept;
			Vector operator()() const;
			void Move(f64 offsetX, f64 offsetY) noexcept;
			static Vector Projection(const Vector& lhs, const Vector& rhs) noexcept;
			static Vector Projection(const Vector& vector, const Line& target) noexcept;
			int Quadrant(const Vector& p) const noexcept;
			void Rotate(const Vector& p, f64 angle) noexcept;
			void Set(f64 newX, f64 newY) noexcept;
			std::string ToString() const noexcept;
			std::tuple<f64, f64> ToTuple() const noexcept;
	};
	Vector operator*(const f64& d, const Vector& v) noexcept;
	Vector operator+(const f64& d, const Vector& v) noexcept;
	class Vector3
	{
		public:
			f64 x;
			f64 y;
			f64 z;
			Vector3();
			Vector3(f64 x, f64 y, f64 z);
			f64 magnitude() const;
			f64 magnitudeSquared() const;
			void Normalize();
			Vector3 Normalized() const;
			f64 Dot(const Vector3& v) const;
			Vector3 operator-() const noexcept;
			Vector3 operator+() const noexcept;
			bool operator==(const Vector3& v) const noexcept;
			bool operator!=(const Vector3& v) const noexcept;
			Vector3 operator-(const Vector3& v) const noexcept;
			Vector3 operator-(const f64& d) const noexcept;
			void operator-=(const Vector3& v) noexcept;
			void operator-=(const f64& d) noexcept;
			Vector3 operator+(const Vector3& v) const noexcept;
			Vector3 operator+(const f64& d) const noexcept;
			void operator+=(const Vector3& v) noexcept;
			void operator+=(const f64& d) noexcept;
			Vector3 operator/(const Vector3& v) const noexcept;
			Vector3 operator/(const f64& d) const noexcept;
			void operator/=(const Vector3& v) noexcept;
			void operator/=(const f64& d) noexcept;
			Vector3 operator*(const Vector3& v) const noexcept;
			Vector3 operator*(const f64& d) const noexcept;
			void operator*=(const Vector3& v) noexcept;
			void operator*=(const f64& d) noexcept;
			bool operator<(const Vector3& v) const noexcept;
			bool operator>(const Vector3& v) const noexcept;
			Vector3 operator()() const;
			void Move(f64 offsetX, f64 offsetY, f64 offsetZ) noexcept;
			static Vector3 Projection(const Vector3& lhs, const Vector3& rhs) noexcept;
			std::string ToString() const noexcept;
			std::tuple<f64, f64, f64> ToTuple() const noexcept;
			void Set(f64 newX, f64 newY, f64 newZ) noexcept;
	};
#define Origin Vector(0, 0)
#define Infinity Vector(std::numeric_limits<f64>::infinity(), std::numeric_limits<f64>::infinity())
}
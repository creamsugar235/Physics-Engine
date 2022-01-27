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
	enum ShapeType
	{
		RigidBody,
		StaticBody,
		KinematicBody
	};

	struct Mat22
	{
		union
		{
			struct
			{
				f64 m00, m01;
				f64 m10, m11;
			};
			struct
			{
				f64 xCol;
				f64 yCol;
			};
		};
		Mat22();
		Mat22(f64 radians);
		Mat22(f64 a, f64 b, f64 c, f64 d);
		Vector AxisX() const;
		Vector AxisY() const;
		void Set(f64 readians);
		Mat22 Transpose() const;
		bool operator==(const Mat22& other) const;
		bool operator!=(const Mat22& other) const;
		Vector operator*(const Vector& v) const;
	};
	
	class Exception : public std::runtime_error
	{
		std::string what_message;
		public:
			Exception(std::string message) : std::runtime_error(message)
			{
			}
			const char * what()
			{
				return this->what_message.c_str();
			}
	};

	class Point3D
	{
		public:
			f64 x = 0;
			f64 y = 0;
			f64 z = 0;
			Point3D();
			Point3D(const Point3D& p);
			Point3D(f64 x, f64 y, f64 z);
			void Move(f64 offsetX, f64 offsetY, f64 offsetZ);
	};

	struct Quaternion
	{
		public:
			f64 x;
			f64 y;
			f64 z;
			f64 w;
			Quaternion();
			Quaternion(const Point3D& axis, f64 angle);
			Quaternion(f64 x, f64 y, f64 z, f64 w);
			Quaternion operator*(const Quaternion& other) const noexcept;
			std::tuple<std::tuple<f64, f64, f64>> ToRotationMatrix() const;
			bool operator==(const Quaternion& other) const noexcept;
			bool operator!=(const Quaternion& other) const noexcept;
	};
#define DefaultQuaternion Quaternion()
}
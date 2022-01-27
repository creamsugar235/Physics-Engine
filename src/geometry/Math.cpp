#include "../include/geometry/Math.hpp"
#include <cmath>

namespace geometry
{
	Point3D::Point3D()
	{
	}

	Point3D::Point3D(const Point3D& p)
	{
		x = p.x;
		y =  p.y;
		z = p.z;
	}

	Point3D::Point3D(f64 x, f64 y, f64 z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Point3D::Move(f64 offsetX, f64 offsetY, f64 offsetZ)
	{
		x += offsetX;
		y += offsetY;
		z += offsetZ;
	}


	Quaternion::Quaternion()
	{
		x = 1;
		y = 0;
		z = 0;
		w = 0;
	}

	Quaternion::Quaternion(const Point3D& axis, f64 angle)
	{
		w = cos(angle / 2);
		x = axis.x * sin(angle / 2);
		y = axis.y * sin(angle / 2);
		z = axis.z * sin(angle / 2);
	}

	Quaternion::Quaternion(f64 x, f64 y, f64 z, f64 w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion Quaternion::operator*(const Quaternion& other) const noexcept
	{
		Quaternion q;
		q.w = (w * other.w - x * other.x - y * other.y - z * other.z);
		q.x = (w * other.x + x * other.w + y * other.z - z * other.y);
		q.y = (w * other.y - x * other.z + y * other.w + z * other.x);
		q.z = (w * other.z + x * other.y - y * other.x + z * other.w);
		return q;
	}

	bool Quaternion::operator==(const Quaternion& other) const noexcept
	{
		return w == other.w && x == other.x && y == other.y && z == other.z;
	}

	bool Quaternion::operator!=(const Quaternion& other) const noexcept
	{
		return( w == other.w && x == other.x && y == other.y && z == other.z);
	}

	Mat22::Mat22() {}

	Mat22::Mat22(f64 radians)
	{
		f64 c = cos(radians);
		f64 s = sin(radians);
		m00 = c;
		m01 = -s;
		m10 = s;
		m11 = c;
	}

	Mat22::Mat22(f64 a, f64 b, f64 c, f64 d)
	{
		m00 = a;
		m01 = b;
		m10 = c;
		m11 = d;
	}

	Vector Mat22::AxisX() const
	{
		return Vector(m00, m01);
	}

	Vector Mat22::AxisY() const
	{
		return Vector(m01, m11);
	}

	Mat22 Mat22::Transpose() const
	{
		return Mat22(m00, m10, m01, m11);
	}

	Vector Mat22::operator*(const Vector& v) const
	{
		return Vector(m00 * v.x + m01 * v.y, m10 * v.x + m11 * v.y);
	}

	bool Mat22::operator==(const Mat22& other) const
	{
		return xCol == other.xCol && yCol == other.yCol;
	}

	bool Mat22::operator!=(const Mat22& other) const
	{
		return xCol != other.xCol || yCol != other.yCol;
	}
}
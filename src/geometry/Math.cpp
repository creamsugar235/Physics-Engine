#include "../include/geometry/Math.hpp"
#include <cmath>

namespace geometry
{

	Matrix22::Matrix22()
	{
		a = 1;
		d = 1;
	}

	Matrix22::Matrix22(f64 radians)
	{
		a = cos(radians);
		b = -sin(radians);
		c = sin(radians);
		d = cos(radians);
	}

	Matrix22::Matrix22(f64 a, f64 b, f64 c, f64 d)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
	}

	Matrix22& Matrix22::operator=(const Matrix22& other)
	{
		this->a = other.a;
		this->b = other.b;
		this->c = other.c;
		this->d = other.d;
		return *this;
	}

	Vector Matrix22::AxisX() const
	{
		return Vector(a, c);
	}

	Vector Matrix22::AxisY() const
	{
		return Vector(b, d);
	}

	Matrix22 Matrix22::Transpose() const
	{
		return Matrix22(a, c, b, d);
	}

	Vector Matrix22::operator*(const Vector& v) const
	{
		return Vector(a * v.x + b * v.y, c * v.x + d * v.y);
	}

	Matrix22 Matrix22::operator*(const Matrix22& other) const
	{
		Matrix22 newMatrix;
		Vector I = other.a * iHat;
		Vector II = other.c * jHat;
		Vector III = other.b * iHat;
		Vector IV = other.d * jHat;
		newMatrix.iHat = (I + II);
		newMatrix.jHat = (III + IV);
		return newMatrix;
	}

	bool Matrix22::operator==(const Matrix22& other) const
	{
		return iHat == other.iHat && jHat == other.jHat;
	}

	bool Matrix22::operator!=(const Matrix22& other) const
	{
		return jHat != other.iHat || jHat != other.jHat;
	}

	void Matrix22::Set(f64 radians)
	{
		a = cos(radians);
		b = -sin(radians);
		c = sin(radians);
		d = cos(radians);
	}

	void Matrix22::Set(f64 a, f64 b, f64 c, f64 d)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
	}

	Matrix33::Matrix33()
	{
		a = 1;
		e = 1;
		i = 1;
	}

	Matrix33::Matrix33(const Matrix22& mat22)
	{
		a = mat22.a;
		b = mat22.b;
		d = mat22.c;
		e = mat22.d;
		c = 1, f = 1, g = 0, h = 0, i = 1;
	}

	Matrix33::Matrix33(const Matrix33& mat33)
	{
		iHat = mat33.iHat;
		jHat = mat33.jHat;
		kHat = mat33.kHat;
	}

	Matrix33::Matrix33(const f64& a, const f64& d, const f64& g, const f64& b, const f64& e, const f64& h, const f64& c, const f64& f, const f64& i)
	{
		this->a = a;
		this->d = d;
		this->g = g;
		this->b = b;
		this->e = e;
		this->h = h;
		this->c = c;
		this->f = f;
		this->i = i;
	}

	Matrix33::Matrix33(const Vector3& iHat, const Vector3& jHat, const Vector3& kHat)
	{
		this->iHat = iHat;
		this->jHat = jHat;
		this->kHat = kHat;
	}

	Matrix33& Matrix33::operator=(const Matrix33& other)
	{
		this->iHat = other.iHat;
		this->jHat = other.jHat;
		this->kHat = other.kHat;
		return *this;
	}

	Vector3 Matrix33::AxisX() const
	{
		return iHat;
	}

	Vector3 Matrix33::AxisY() const
	{
		return jHat;
	}

	Vector3 Matrix33::AxisZ() const
	{
		return kHat;
	}

	Matrix33 Matrix33::Transpose() const
	{
		return Matrix33(a, b, c, d, e, f, g, h, i);	
	}

	bool Matrix33::operator==(const Matrix33& other) const
	{
		return iHat == other.iHat && jHat == other.jHat && kHat == other.kHat;
	}

	bool Matrix33::operator!=(const Matrix33& other) const
	{
		return iHat != other.iHat || jHat != other.jHat || kHat != other.kHat;
	}

	Vector3 Matrix33::operator*(const Vector3& other) const
	{
		return Vector3(
			a * other.x + b * other.y + c * other.z,
			d * other.x + e * other.y + f * other.z,
			g * other.x + h * other.y + i * other.z
		);
	}

	Matrix33 Matrix33::operator*(const Matrix33& other) const
	{
		Matrix33 newMatrix;
		Vector3 vecs[9];
		vecs[0] = iHat * other.a;
		vecs[1] = jHat * other.b;
		vecs[2] = kHat * other.c;
		vecs[3] = iHat * other.d;
		vecs[4] = jHat * other.e;
		vecs[5] = kHat * other.f;
		vecs[6] = iHat * other.g;
		vecs[7] = jHat * other.h;
		vecs[8] = kHat * other.i;
		newMatrix.iHat = vecs[0] + vecs[3] + vecs[6];
		newMatrix.jHat = vecs[1] + vecs[4] + vecs[7];
		newMatrix.kHat = vecs[2] + vecs[5] + vecs[8];
		return newMatrix;
	}
}
#include "../include/geometry/Calc.hpp"
#include "../include/geometry/Line.hpp"
#include "../include/geometry/Vector.hpp"

namespace geometry
{
	Vector::Vector()
	{
		x = 0;
		y = 0;
	}

	Vector::Vector(f64 x, f64 y)
	{
		this->x = x;
		this->y = y;
	}

	f64 Vector::Cross(const Vector& v) const noexcept
	{
		return x * v.y - y * v.x;
	}

	Vector Vector::Cross(const Vector& v, const f64& s)
	{
		return Vector(s * v.y, -s * v.x);
	}

	Vector Vector::Cross(const f64& s, const Vector& v)
	{
		return Vector(-s * v.y, s * v.x);
	}

	f64 Vector::Dot(const Vector& v) const
	{
		return x * v.x + y * v.y;
	}

	f64 Vector::magnitude() const
	{
		return sqrt(x * x + y * y);
	}

	f64 Vector::magnitudeSquared() const
	{
		return x * x + y * y;
	}

	void Vector::Normalize()
	{
		f64 mag = magnitude();
		if (mag > 0.00001)
			*this = *this / mag;
		else
			*this = Vector(0, 0);
	}

	Vector Vector::Normalized() const
	{
		Vector v = Vector(this->x, this->y);
		v.Normalize();
		return v;
	}

	Vector operator*(const f64& d, const Vector& v) noexcept
	{
		return Vector(d * v.x, d * v.y);
	}

	Vector operator+(const f64& d, const Vector& v) noexcept
	{
		return Vector(d + v.x, d + v.y);
	}

	Vector Vector::operator-() const noexcept
	{
		return Vector(-x, -y);
	}

	Vector Vector::operator+() const noexcept
	{
		return Vector(+x, +y);
	}

	bool Vector::operator==(const Vector &v) const noexcept
	{
		return x == v.x && y == v.y;
	}

	bool Vector::operator!=(const Vector &v) const noexcept
	{
		return x != v.x || y != v.y;
	}

	Vector Vector::operator+(const Vector& v) const noexcept
	{
		Vector result(*this);
		result.x += v.x;
		result.y += v.y;
		return result;
	}

	Vector Vector::operator+(const f64& d) const noexcept
	{
		Vector result(*this);
		result.x += d;
		result.y += d;
		return result;
	}

	void Vector::operator+=(const Vector& v) noexcept
	{
		x += v.x;
		y += v.y;
	}

	void Vector::operator+=(const f64& d) noexcept
	{
		x += d;
		y += d;
	}

	Vector Vector::operator-(const Vector& v) const noexcept
	{
		Vector result(*this);
		result.x -= v.x;
		result.y -= v.y;
		return result;
	}

	Vector Vector::operator-(const f64& d) const noexcept
	{
		Vector result(*this);
		result.x -= d;
		result.y -= d;
		return result;
	}

	void Vector::operator-=(const Vector& v) noexcept
	{
		x -= v.x;
		y -= v.y;
	}

	void Vector::operator-=(const f64& d) noexcept
	{
		x -= d;
		y -= d;
	}

	Vector Vector::operator*(const Vector& v) const noexcept
	{
		Vector result(*this);
		result.x *= v.x;
		result.y *= v.y;
		return result;
	}

	Vector Vector::operator*(const f64& d) const noexcept
	{
		Vector result(*this);
		result.x *= d;
		result.y *= d;
		return result;
	}

	void Vector::operator*=(const Vector& v) noexcept
	{
		x *= v.x;
		y *= v.y;
	}

	void Vector::operator*=(const f64& d) noexcept
	{
		x *= d;
		y *= d;
	}

	Vector Vector::operator/(const Vector& v) const noexcept
	{
		Vector result(*this);
		result.x /= v.x;
		result.y /= v.y;
		return result;
	}

	Vector Vector::operator/(const f64& d) const noexcept
	{
		Vector result(*this);
		result.x /= d;
		result.y /= d;
		return result;
	}

	void Vector::operator/=(const Vector& v) noexcept
	{
		x /= v.x;
		y /= v.y;
	}

	void Vector::operator/=(const f64& d) noexcept
	{
		x /= d;
		y /= d;
	}

	bool Vector::operator^(Line l) const
	{
		return (Line(l.a(), *this).angle() == Line(*this, l.b()).angle());
	}

	bool Vector::operator<(const Vector& v) const noexcept
	{
		return Calc::Distance(Origin, v) > Calc::Distance(Origin, *this);
	}

	bool Vector::operator>(const Vector& v) const noexcept
	{
		return Calc::Distance(Origin, v) < Calc::Distance(Origin, *this);
	}

	Vector Vector::operator()() const
	{
		return Vector(x, y);
	}

	void Vector::Move(f64 offsetX, f64 offsetY) noexcept
	{
		this->x += offsetX;
		this->y += offsetY;
	}

	Vector Vector::Projection(const Vector& lhs, const Vector& rhs) noexcept
	{
		double rhs_ls = rhs.magnitudeSquared();
		return rhs * (rhs.Dot(lhs) / rhs_ls);
	}

	Vector Vector::Projection(const Vector& vector, const Line& target) noexcept
	{
		Vector AV = vector - target.a;
		Vector AB = target.b - target.a;
		return target.a + AV.Dot(AB) / AB.Dot(AB) * AB;
	}

	int Vector::Quadrant(const Vector& p) const noexcept
	{
		if (p.x < this->x)
		{
			if (p.y < this->y)
			{
				return 3;
			}
			else if (p.y > this->y)
			{
				return 2;
			}
			return 3;
		}
		else if (p.x > this->x)
		{
			if (p.y < this->y)
			{
				return 4;
			}
			else if (p.y > this->y)
			{
				return 1;
			}
			return 1;
		}
		return 0;
	}

	void Vector::Rotate(const Vector& p, f64 angle) noexcept
	{
		f64 currentAngle = Calc::GetAngle(p, *this);
		angle += currentAngle;
		if (angle < 0) {angle += (M_PI * 2);}
		if (angle > (M_PI) * 2) {angle -= M_PI;}
		f64 distance = Calc::Distance(*this, p);
		Vector v2 = Calc::GetVectorOnCircle(p, distance, angle);
		this->x = v2.x;
		this->y = v2.y;
	}

	std::string Vector::ToString() const noexcept
	{
		std::string strX = std::to_string(this->x);
		std::string strY = std::to_string(this->y);
		return "(" + strX + ", " + strY + ")";
	}
	
	std::tuple<f64, f64> Vector::ToTuple() const noexcept
	{
		return std::tuple<f64, f64>(this->x, this->y);
	}
}
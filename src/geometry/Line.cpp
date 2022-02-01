#include "../include/geometry/Calc.hpp"
#include "../include/geometry/Line.hpp"

namespace geometry
{
	Line::Line()
	{
	}

	Line::Line(const Vector& a, const Vector& b)
	{
		this->a = a;
		this->b = b;
		this->_length = Calc::Distance(this->a, this->b);
		this->_angle = Calc::GetAngle(this->a, this->b);
	}

	Line::Line(const Line& l)
	{
		this->a = l.a();
		this->b = l.b();
		this->_length = Calc::Distance(this->a, this->b);
		this->_angle = Calc::GetAngle(this->a, this->b);
	}

	Line::~Line()
	{
	}

	bool Line::operator==(const Line& l) const
	{
		return (this->a == l.a() && this->b == l.b());
	}

	bool Line::operator!=(const Line& l) const
	{
		return !(this->a == l.a() && this->b == l.b());
	}

	f64 Line::angle() const
	{
		return _angle;
	}

	Vector Line::GetVectorAlongLine(f64 distance, bool startFromA) const
	{
		Vector begin = startFromA ? this->b - this->a : this->a - this->b;
		begin.Normalize();
		return begin * distance + (!startFromA ? this->b : this->a);
	}

	Line Line::GetPerpendicular() const
	{
		double xdif = b.x - a.x;
		double ydif = b.y - a.y;
		return Line(Vector(b.x - ydif / 2, b.y + xdif / 2), Vector(b.x + ydif / 2, b.y - xdif / 2));
	}

	f64 Line::length() const
	{
		return this->_length;
	}

	void Line::Move(f64 offsetX, f64 offsetY)
	{
		this->a.Move(offsetX, offsetY);
		this->b.Move(offsetX, offsetY);
	}

	std::string Line::ToString() const
	{
		return "(" + this->a.ToString() + ", " + this->b.ToString() + ")";
	}

	std::tuple<std::tuple<f64, f64>, std::tuple<f64, f64>> Line::ToTuple() const
	{
		return std::tuple<std::tuple<f64, f64>, std::tuple<f64, f64>>(this->a.ToTuple(), this->b.ToTuple());
	}

	void Line::Rotate(const Vector& pivot, f64 angle)
	{
		this->a.Rotate(pivot, angle);
		this->b.Rotate(pivot, angle);
		Update();
	}

	void Line::Update()
	{
		this->_length = Calc::Distance(this->a, this->b);
		this->_angle = Calc::GetAngle(this->a, this->b);
	}

	bool Line::VectorIsOnLine(const Vector& v) const
	{
		return Calc::Distance(a, v) + Calc::Distance(b, v) ==
			length();
	}
}
#include "../include/geometry/main.hpp"
namespace geometry
{
	f64 Calc::Degrees(f64 angle)
	{
		return angle * (180 / M_PI);
	}

	f64 Calc::Diagonal(f64 width, f64 height)
	{
		return sqrt(pow(width, 2) + pow(height, 2));
	}

	f64 Calc::Distance(const Vector &a, const Vector &b)
	{
		f64 dis = (pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
		if (dis < 0) {dis *= -1;}
		return sqrt(dis);
	}

	f64 Calc::DistanceSquared(const Vector& a, const Vector& b)
	{
		f64 dis = (pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
		if (dis < 0) {dis *= -1;}
		return dis;
	}

	f64 Calc::Distance(const Line& a, const Vector& b)
	{
		const Vector ac = b - a.a;
		const Vector ab = a.b - a.a;
		auto project = [&] (const Vector& vA, const Vector& vB) {
			double tmp = vA.Dot(vB) / vB.Dot(vB);
			return Vector(tmp * vB.x, tmp *vB.y);
		};
		const Vector d = project(ac, ab) + a.a;
		const Vector ad = d - a.a;
		auto hypot2 = [&] (const Vector& vA, const Vector& vB) {
			return (vA - vB).Dot(vA - vB);
		};
		const double k = fabs(ab.x) > fabs(ab.y) ? ad.x / ab.x : ad.y / ab.y;
		if (k <= 0)
		{
			return sqrt(hypot2(b, a.a));
		}
		else if (k >= 1)
		{
			return sqrt(hypot2(b, a.b));
		}
		return sqrt(hypot2(b, d));
	}

	f64 Calc::GetAngle(const Vector &a, const Vector &b, const Vector &c)
	{
		f64 result = atan2(c.y - b.y, c.x - b.x) - atan2(a.y - b.y, a.x - b.x);
		result = result < 0 ? -result : (M_PI * 2) - result;
		return result;
	}

	f64 Calc::GetAngle(f64 slope)
	{
		return atan(slope);
	}	

	f64 Calc::GetAngle(const Vector& center, const Vector& Vector)
	{
		return atan2(Vector.y - center.y, Vector.x - center.x);
	}

	Vector Calc::GetVectorOnCircle(const Vector& center, f64 radius, f64 angle)
	{
		radius = radius < 0 ? -radius : radius;
		f64 x = center.x + (radius * cos(angle));
		f64 y = center.y + (radius * sin(angle));
		return Vector(x, y);
	}

	f64 Calc::GetSlope(const Vector& a, const Vector& b)
	{
		if (a.y == b.y || a.x == b.x)
		{return 0;}
		return (b.y - a.y) / (b.x - a.x);
	}

	bool Calc::Intersecting(const Line& a, const Line& b, bool isInfLine)
	{
		return VectorOfIntersect(a, b, isInfLine) != Infinity;
	}

	Vector Calc::VectorOfIntersect(const Line& a, const Line& b, bool isInfLine)
	{
		auto det = [](std::tuple<f64, f64> a, std::tuple<f64, f64> b) -> f64
		{
			return std::get<0>(a) * std::get<1>(b) - std::get<1>(a) * std::get<0>(b);
		};

		auto xdiff = std::tuple<f64, f64>(a.a().x - a.b().x, b.a().x - b.b().x);
		auto ydiff = std::tuple<f64, f64>(a.a().y - a.b().y, b.a().y - b.b().y);
		f64 div = det(xdiff, ydiff);
		if (div == 0) {return Infinity;}
		auto d = std::tuple<f64, f64>(det(std::get<0>(a.ToTuple()), std::get<1>(a.ToTuple())), det(std::get<0>(b.ToTuple()), std::get<1>(b.ToTuple())));
		f64 x = det(d, xdiff) / div;
		f64 y = det(d, ydiff) / div;
		Vector p = Vector(x, y);
		if (isInfLine) {return p;}
		if ((Distance(a.a(), p) + Distance(a.b(), p) == a.length()) && (Distance(b.a(), p) + Distance(b.b(), p) == b.length()))
		{
			return p;
		}
		return Infinity;
	}
}
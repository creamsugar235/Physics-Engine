#include "src/include/geometry/main.hpp"
#include <iostream>

using namespace geometry;

Vector Projecrt(const Line& rhs, const Vector lhs) noexcept
{
	double angle = rhs.angle();	
	angle += M_PI / 2;
	angle = fmod(angle, 2 * M_PI);
	
}

int main()
{
	Vector v(167, 100);
	Line l(Vector(100, 100), Vector(200, 100));
	std::cout<<Calc::Distance(l.a, v)<<" "<<Calc::Distance(l.b, v)<<"\n";
	std::cout<<l.length()<<"\n";
	std::cout<<l.VectorIsOnLine(v);
}
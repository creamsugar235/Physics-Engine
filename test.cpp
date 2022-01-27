#include "src/include/geometry/main.hpp"
#include <iostream>

using namespace geometry;

int main()
{
	Vector v(8, 2);
	Line l(Vector(8, 5), Vector(11, 1));
	Vector v2 = Vector::Projection(v, l);
	std::cerr<<v2.x<<" "<<v2.y<<"\n";
}
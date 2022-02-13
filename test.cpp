#include "src/include/geometry/main.hpp"
#include <iostream>

using namespace geometry;
struct thing
{
	geometry::Vector v;
	f64& x = v.x;
	f64& y = v.y;
};

int main()
{
	std::cerr<<sizeof(thing)<<"\n";
	return 0;
}
#pragma once
#include <tuple>
#include "Vector.hpp"
typedef double f64;
typedef float f32;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;

namespace geometry
{
	class Line
	{
		private:
			f64 _length = 0;
			f64 _angle = 0;
		public:
			Line();
			Line(const Vector& a, const Vector& b);
			Line(const Line& l);
			~Line();
			Vector a;
			Vector b;
			bool operator==(const Line& l) const;
			bool operator!=(const Line& l) const;
			f64 angle() const;
			f64 signedAngle() const;
			Vector GetVectorAlongLine(f64 distance, bool startFromA = true) const;
			Line GetPerpendicular() const;
			f64 length() const;
			void Move(f64 offsetX, f64 offsetY);
			std::string ToString() const;
			std::tuple<std::tuple<f64, f64>, std::tuple<f64, f64>> ToTuple() const;
			void Rotate(const Vector& pivot, f64 angle);
			void Update();
	};
}
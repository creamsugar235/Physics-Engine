#include "../include/physics/Time.hpp"
namespace physics
{
	void Time::Tick()
	{
		std::chrono::time_point<clock> t = clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(t - time).count() / 1000;
		deltaTime = deltaTime == 0 ? 0.0001 : deltaTime;
		time = clock::now();
	}
}
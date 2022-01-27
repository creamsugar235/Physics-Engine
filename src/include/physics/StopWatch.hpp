#pragma once
#include <ctime>
#include <chrono>
namespace physics
{
	class StopWatch;

	class StopWatch
	{
		public:
			typedef std::chrono::high_resolution_clock Clock;
			std::chrono::time_point<Clock> start;
			std::chrono::time_point<Clock> stop;
			void Reset();
			void Start();
			void Stop();
			double Duration() const;
	};
}
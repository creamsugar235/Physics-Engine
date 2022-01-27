#include <chrono>

namespace physics
{
	class Time final
	{
		public:
			typedef std::chrono::high_resolution_clock clock;
			static inline std::chrono::time_point<clock> time = clock::now();
			static inline double deltaTime = -1;
			static void Tick();
	};
}
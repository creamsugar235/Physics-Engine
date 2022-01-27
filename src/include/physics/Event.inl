#include "Event.hpp"
namespace physics
{
	template <typename Function>
	template <typename... Args>
	inline void Event<Function>::operator()(Args... a)
	{
		for (auto& f: functions)
		{
			f(std::forward<Args>(a)...);
		}
	}

	template <typename Function>
	inline void Event<Function>::operator+=(Function& f)
	{
		functions.emplace_back(f);
	}

	template <typename Function>
	inline void Event<Function>::operator-=(Function& f)
	{
		for(auto p = functions.begin(); p < functions.end();p++)
		{
			if (*p == f)
			{
				functions.erase(p);
				break;
			}
		}
	}
}
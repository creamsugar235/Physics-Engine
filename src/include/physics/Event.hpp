#pragma once
#include <functional>
#include <vector>
namespace physics
{
	template <typename Function>
	class Event;

	template <typename Function>
	class Event final
	{
		public:
			template <typename... Args>
			void operator()(Args... a);
			void operator+=(Function& f);
			void operator-=(Function& f);
			std::vector<Function> functions;
	};
}
#include "Event.inl"
#include "../include/physics/Hashable.hpp"

namespace physics
{
	Hashable::~Hashable() noexcept {}

	int Hashable::Hash() const noexcept
	{
		const unsigned char* reader = (const unsigned char*)this;
		int h = 0;
		for (unsigned i = 0; i < sizeof(this);i++)
			h = h * 31 + static_cast<int>(reader[i]);
		return h;
	}

	bool Hashable::operator==(const Hashable& other) const noexcept
	{
		return Hash() == other.Hash();
	}

	bool Hashable::operator!=(const Hashable& other) const noexcept
	{
		return Hash() != other.Hash();
	}

	bool Hashable::Equals(const Hashable& other) const noexcept
	{
		return *this == other;
	}

	bool Hashable::NotEquals(const Hashable& other) const noexcept
	{
		return *this != other;
	}
}
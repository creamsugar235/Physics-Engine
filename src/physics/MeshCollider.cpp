#include "../include/physics/Collision.hpp"

namespace physics
{
	MeshCollider::MeshCollider() noexcept
	{
		classCode = 0x05;
	}

	MeshCollider::MeshCollider(const std::vector<Collider*>& colliders) noexcept
	{
		classCode = 0x05;
		this->colliders = colliders;
	}

	MeshCollider::MeshCollider(const MeshCollider& c) noexcept
	{
		classCode = 0x05;
		for (Collider* cldr: c.colliders)
		{
			this->colliders.push_back(cldr->Clone());
		}
	}

	MeshCollider::~MeshCollider() noexcept {}

	bool MeshCollider::operator==(const Collider& other) const noexcept
	{
		MeshCollider m;
		try
		{
			m = dynamic_cast<const MeshCollider&>(other);	
		}
		catch(const std::bad_cast& e)
		{
			return false;
		}
		if (m.colliders.size() != colliders.size())
		{
			return false;
		}
		for (unsigned i = 0; i < colliders.size(); i++)
		{
			if (colliders.at(i) && m.colliders.at(i))
			{
				if (*colliders.at(i) != *m.colliders.at(i))
					return false;
			}
		}
		return true;
	}

	bool MeshCollider::operator!=(const Collider& other) const noexcept
	{
		MeshCollider m;
		try
		{
			m = dynamic_cast<const MeshCollider&>(other);
		}
		catch(const std::bad_cast& e)
		{
			return true;
		}
		if (colliders.size() != m.colliders.size())
		{
			return true;
		}
		for (unsigned i = 0; i  <colliders.size(); i++)
		{
			if (colliders.at(i) && m.colliders.at(i))
			{
				if (*colliders.at(i) != *m.colliders.at(i))
				{
					return true;
				}
			}
		}
		return false;
	}

	Collider* MeshCollider::Clone() const
	{
		return (Collider*)new MeshCollider(*this);
	}
}
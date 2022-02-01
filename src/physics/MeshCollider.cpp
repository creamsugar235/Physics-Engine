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

	Collider* MeshCollider::Clone() const
	{
		return (Collider*)new MeshCollider(*this);
	}
}
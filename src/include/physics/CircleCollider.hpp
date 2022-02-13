#pragma once
#include "Collider.hpp"

namespace physics
{
	//0x03
	struct CircleCollider : public Collider
	{
		geometry::Vector center = geometry::Vector();
		f64 radius = 0;
		CircleCollider() noexcept;
		CircleCollider(geometry::Vector center, f64 radius) noexcept;
		CircleCollider(const CircleCollider& c) noexcept;
		~CircleCollider() noexcept;
		Collider* Clone() const override;
		virtual geometry::Vector GetCenterOfMass() const noexcept override;
		geometry::Vector Max() const noexcept override;
		geometry::Vector Min() const noexcept override;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const Collider* collider,
			const Transform& colliderTransform) const noexcept override;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const CircleCollider* collider,
			const Transform& colliderTransform) const noexcept override;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const PolygonCollider* collider,
			const Transform& colliderTransform) const noexcept override;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const BoxCollider* collider,
			const Transform& colliderTransform) const noexcept override;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const MeshCollider* collider,
			const Transform& colliderTransform) const noexcept override;
		std::vector<unsigned char> Serialize() const override;
		const unsigned long TotalByteSize() const noexcept override;
		serialization::Serializable* Deserialize(std::vector<byte> v) const override;
	};
}
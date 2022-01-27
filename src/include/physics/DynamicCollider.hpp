#pragma once
#include "Collider.hpp"

namespace physics
{
	
	//0x04
	struct DynamicCollider : public Collider
	{
		geometry::Vector pos;
		std::vector<geometry::Vector> points;
		DynamicCollider();
		DynamicCollider(const DynamicCollider& d) noexcept;
		DynamicCollider(geometry::Vector pos, geometry::Vector a, geometry::Vector b, geometry::Vector c, std::initializer_list<geometry::Vector> extra={}) noexcept;
		~DynamicCollider() noexcept;
		bool operator==(const Collider& other) const noexcept override;
		bool operator!=(const Collider& other) const noexcept override;
		Collider* Clone() const override;
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
			const DynamicCollider* collider,
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
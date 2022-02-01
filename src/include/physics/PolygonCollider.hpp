#pragma once
#include "Collider.hpp"

namespace physics
{
	
	//0x04
	struct PolygonCollider : public Collider
	{
		geometry::Vector pos;
		std::vector<geometry::Vector> points;
		PolygonCollider();
		PolygonCollider(const PolygonCollider& d) noexcept;
		PolygonCollider(const geometry::Vector& pos, double distanceBetweenPoints=1, unsigned long count=3) noexcept;
		PolygonCollider(const geometry::Vector& pos, const geometry::Vector& a, const geometry::Vector& b, const geometry::Vector& c, std::initializer_list<geometry::Vector> extra={}) noexcept;
		~PolygonCollider() noexcept;
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
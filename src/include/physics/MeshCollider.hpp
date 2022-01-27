#pragma once
#include "Collider.hpp"

namespace physics
{
	//0x05
	struct MeshCollider : public Collider
	{
		std::vector<Collider*> colliders;
		MeshCollider() noexcept;
		MeshCollider(const std::vector<Collider*>& colliders) noexcept;
		MeshCollider(const MeshCollider& m) noexcept;
		~MeshCollider() noexcept;
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
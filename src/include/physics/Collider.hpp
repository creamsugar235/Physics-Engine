#pragma once
#include "../geometry/main.hpp"
#include "Hashable.hpp"
#include "Serializable.hpp"
namespace physics
{

	struct Transform;
	struct BoxCollider;
	struct Collider;
	struct CircleCollider;
	struct PolygonCollider;
	struct MeshCollider;
	struct CollisionPoints;

	struct CollisionPoints
	{
		geometry::Vector a;
		geometry::Vector b;
		geometry::Vector normal;
		f64 depth = 0;
		bool hasCollision = false;
		inline bool operator==(const CollisionPoints& other) const noexcept
		{
			return a == other.a && b == other.b && normal == other.normal && hasCollision == other.hasCollision;
		}

		inline bool operator!=(const CollisionPoints& other) const noexcept
		{
			return !(a == other.a && b == other.b && normal == other.normal && hasCollision == other.hasCollision);
		}
	};

	struct Transform : public serialization::Serializable, public Hashable
	{
		geometry::Vector position = geometry::Vector(0, 0);
		geometry::Vector scale = geometry::Vector(1, 1);
		geometry::Mat22 rotation = geometry::Mat22();
		inline Transform() noexcept
		{
			position = geometry::Vector(0, 0);
			scale = geometry::Vector(1, 1);
			rotation = geometry::Mat22();
		}
		inline bool operator==(const Transform& other) const noexcept
		{
			return position == other.position && scale == other.scale && rotation == other.rotation;
		}
		inline bool operator!=(const Transform& other) const noexcept
		{
			return !(position == other.position && scale == other.scale && rotation == other.rotation);
		}
		std::vector<unsigned char> Serialize() const override;
		const unsigned long TotalByteSize() const noexcept override;
		serialization::Serializable* Deserialize(std::vector<byte> v) const override;
	};

	struct Collider : public serialization::Serializable, public Hashable
	{
		virtual Collider* Clone() const = 0;
		virtual ~Collider() noexcept;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const Collider* collider,
			const Transform& colliderTransform) const noexcept = 0;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const CircleCollider* collider,
			const Transform& colliderTransform) const noexcept = 0;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const PolygonCollider* collider,
			const Transform& colliderTransform) const noexcept = 0;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const BoxCollider* collider,
			const Transform& colliderTransform) const noexcept = 0;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const MeshCollider* collider,
			const Transform& colliderTransform) const noexcept = 0;
	};
}
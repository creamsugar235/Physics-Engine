#include "Collision.hpp"
using namespace physics;
namespace algo
{
	CollisionPoints FindDynamicCircleCollisionPoints(
		const DynamicCollider* a, const Transform& ta,
		const CircleCollider* b, const Transform& tb
	);

	CollisionPoints FindDynamicBoxCollisionPoints(
		const DynamicCollider* a, const Transform& ta,
		const BoxCollider* b, const Transform& tb
	);

	CollisionPoints FindDynamicMeshCollisionPoints(
		const DynamicCollider* a, const Transform& ta,
		const MeshCollider* b, const Transform& tb
	);

	CollisionPoints FindCircleCircleCollisionPoints(
		const CircleCollider* a, const Transform& ta,
		const CircleCollider* b, const Transform& tb
	);

	CollisionPoints FindCircleBoxCollisionPoints(
		const CircleCollider* a, const Transform& ta,
		const BoxCollider* b, const Transform& tb
	);

	CollisionPoints FindCircleMeshCollisionPoints(
		const CircleCollider* a, const Transform& ta,
		const MeshCollider* b, const Transform& tb
	);

	CollisionPoints FindBoxMeshCollisionPoints(
		const BoxCollider* a, const Transform& ta,
		const MeshCollider* b, const Transform& tb
	);

	CollisionPoints FindDynamicDynamicCollisionPoints(
		const DynamicCollider* a, const Transform& ta,
		const DynamicCollider* b, const Transform& tb
	);

	CollisionPoints FindBoxBoxCollisionPoints(
		const BoxCollider* a, const Transform& ta,
		const BoxCollider* b, const Transform& tb
	);

	CollisionPoints FindMeshMeshCollisionPoints(
		const MeshCollider* a, const Transform& ta,
		const MeshCollider* b, const Transform& tb
	);

	bool DynamicColliderVectorIsColliding(
		const DynamicCollider* a, const Transform& ta,
		const geometry::Vector& b
	);

	bool LinePassesThroughCircle(
		const geometry::Line& a, const CircleCollider* b,
		const Transform& tb
	);
}
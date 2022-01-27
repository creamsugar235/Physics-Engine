#pragma once
#include "CollisionObject.hpp"
#include "Rigidbody.hpp"
#include "BoxCollider.hpp"
#include "CircleCollider.hpp"
#include "DynamicCollider.hpp"
#include "MeshCollider.hpp"
#include "Entity.hpp"
#include "Serializable.hpp"
namespace physics
{
	namespace serialization
	{
		typedef const unsigned char* reader;
		typedef unsigned char* writer;

		namespace Transform
		{
			Serializable* Deserialize(std::vector<unsigned char> bytes);
			std::vector<unsigned char> Serialize(const physics::Transform& t);
			unsigned long TotalByteSize();
		}

		namespace BoxCollider
		{
			Serializable* Deserialize(std::vector<unsigned char> bytes);
			std::vector<unsigned char> Serialize(const physics::BoxCollider& b);
			unsigned long TotalByteSize();
		}

		namespace CircleCollider
		{
			Serializable* Deserialize(std::vector<unsigned char> bytes);
			std::vector<unsigned char> Serialize(const physics::CircleCollider& c);
			unsigned long TotalByteSize();
		}

		namespace DynamicCollider
		{
			Serializable* Deserialize(std::vector<unsigned char> bytes);
			std::vector<unsigned char> Serialize(const physics::DynamicCollider& d);
			unsigned long TotalByteSize(const physics::DynamicCollider& d);
			unsigned long MinimumByteSize();
		}

		namespace MeshCollider
		{
			Serializable* Deserialize(std::vector<unsigned char> bytes);
			std::vector<unsigned char> Serialize(const physics::MeshCollider& m);
			unsigned long TotalByteSize(const physics::MeshCollider& m);
			unsigned long MinimumByteSize();
		}

		namespace CollisionObject
		{
			Serializable* Deserialize(std::vector<unsigned char> bytes);
			std::vector<unsigned char> Serialize(const physics::CollisionObject& c);
			unsigned long TotalByteSize(physics::CollisionObject& c);
			unsigned long MinimumByteSize();
		}

		namespace Rigidbody
		{
			Serializable* Deserialize(std::vector<unsigned char> bytes);
			std::vector<unsigned char> Serialize(const physics::Rigidbody& r);
			unsigned long TotalByteSize(physics::Rigidbody& r);
			unsigned long MinimumByteSize();
		}

		namespace Entity
		{
			Serializable* Deserialize(std::vector<unsigned char> bytes);
			std::vector<unsigned char> Serialize(const physics::Entity& e);
			unsigned long TotalByteSize(physics::Entity& e);
			unsigned long MinimumByteSize();
		}
		/*Serializable* Deserialize(std::vector<unsigned char> bytes);
		std::vector<unsigned char> Serialize(const Serializable& s);
		unsigned long TotalByteSize();*/
	}
}
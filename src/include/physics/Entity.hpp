#pragma once
#include "../SFML/Graphics.hpp"
#include "Collision.hpp"
#include "CollisionObject.hpp"
#include <memory>

namespace physics
{
	//0x07
	class Entity : public serialization::Serializable
	{
		private:
			CollisionObject* _collider;
			std::string _name;
			sf::Sprite _sprite;
			sf::Texture _texture;
			Transform _transform;
		public:
			unsigned short ClassCode = 0x07;
			Entity(const std::string& name, CollisionObject& c, const Transform& t, const sf::Sprite& s) noexcept;
			Entity(const Entity& e) noexcept;
			virtual ~Entity() noexcept;
			virtual bool operator==(const Entity& other) const noexcept;
			virtual bool operator!=(const Entity& other) const noexcept;
			virtual Entity* Clone() const noexcept;
			virtual CollisionObject& GetCollisionObject() const noexcept;
			std::string GetName() const noexcept;
			virtual sf::Sprite GetSprite() const noexcept;
			virtual Transform GetTransform() const noexcept;
			virtual void SetCollisionObject(CollisionObject& c) noexcept;
			void SetName(const std::string& s) noexcept;
			virtual void SetSprite(const sf::Sprite& s) noexcept;
			virtual void SetTransform(const Transform& t) noexcept;
			virtual void Update() noexcept;
			std::vector<unsigned char> Serialize() const override;
			const unsigned long TotalByteSize() const noexcept override;
			serialization::Serializable* Deserialize(std::vector<byte> v) const override;
	};
}
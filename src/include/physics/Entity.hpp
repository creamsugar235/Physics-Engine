#pragma once
#include "../SFML/Graphics.hpp"
#include "Collision.hpp"
#include "CollisionObject.hpp"
#include <memory>

namespace physics
{
	//0x07
	class Entity : public serialization::Serializable, public Hashable
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
			virtual Entity* Clone() const noexcept;
			virtual bool Equals(const Hashable& other) const noexcept override;
			virtual CollisionObject& GetCollisionObject() const noexcept;
			virtual std::string GetName() const noexcept;
			virtual sf::Sprite GetSprite() const noexcept;
			virtual Transform GetTransform() const noexcept;
			virtual bool NotEquals(const Hashable& other) const noexcept override;
			virtual void SetCollisionObject(CollisionObject& c) noexcept;
			virtual void SetName(const std::string& s) noexcept;
			virtual void SetSprite(const sf::Sprite& s) noexcept;
			virtual void SetTransform(const Transform& t) noexcept;
			virtual void Update() noexcept;
			virtual void FixedUpdate() noexcept;
			std::vector<unsigned char> Serialize() const override;
			const unsigned long TotalByteSize() const noexcept override;
			serialization::Serializable* Deserialize(std::vector<byte> v) const override;
	};
}
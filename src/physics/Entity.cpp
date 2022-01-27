#include "../include/physics/Entity.hpp"
#include <iostream>
#include <cstring>
namespace physics
{
	Entity::Entity(const std::string& name, CollisionObject& c, const Transform& t, const sf::Sprite& s) noexcept
	{
		_name = name;
		_collider = c.Clone();
		_sprite = s;
		if (s.getTexture())
		{
			_texture = sf::Texture(*s.getTexture());
		}
		_sprite.setTexture(_texture);
		_sprite.setPosition(_transform.position.x, _transform.position.y);
		_transform = t;
	}

	Entity::Entity(const Entity& e) noexcept
	{
		_name = e.GetName();
		_collider = e.GetCollisionObject().Clone();
		_sprite = e.GetSprite();
		if (e.GetSprite().getTexture())
		{
			_texture = sf::Texture(*e.GetSprite().getTexture());
		}
		_sprite.setTexture(_texture);
		_sprite.setPosition(_transform.position.x, _transform.position.y);
		_transform = e.GetTransform();
	}

	bool Entity::operator==(const Entity& other) const noexcept
	{
		return _name == other.GetName() && *_collider == other.GetCollisionObject() &&
		_transform == other.GetTransform();
	}

	bool Entity::operator!=(const Entity& other) const noexcept
	{
		return _name != other.GetName() || *_collider != other.GetCollisionObject() ||
		_transform != other.GetTransform();
	}

	Entity::~Entity()
	{
		delete _collider;
	}

	Entity* Entity::Clone() const noexcept
	{
		return new Entity(*this);
	}

	CollisionObject& Entity::GetCollisionObject() const noexcept
	{
		return *_collider;
	}

	std::string Entity::GetName() const noexcept
	{
		return _name;
	}

	sf::Sprite Entity::GetSprite() const noexcept
	{
		return _sprite;
	}

	Transform Entity::GetTransform() const noexcept
	{
		return _transform;
	}

	std::vector<unsigned char> Entity::Serialize() const
	{
		std::vector<byte> v = _collider->Serialize();
		v.push_back(0xff);
		v.push_back(0x00);
		for (const byte& b: _transform.Serialize())
		{
			v.push_back(b);
		}
		v.push_back(0xff);
		v.push_back(0x00);
		//totally safe ;)
		const byte* iter=(const byte*)&_texture;
		for (unsigned i = 0; i < sizeof(_texture); i++)
		{
			v.push_back(*(iter + i));
		}
		v.push_back(0xff);
		v.push_back(0x00);
		for (const char c: _name)
		{
			v.push_back(c);
		}
		v.push_back(0xff);
		v.push_back(0x00);
		v.push_back(ClassCode);
		v.push_back(0xff);
		v.push_back(0xff);
		v.push_back(0xff);
		return v;
	}

	serialization::Serializable* Entity::Deserialize(std::vector<byte> v) const
	{
		Entity* e = new Entity(*this);
		CircleCollider cClass;
		int nullCount = 0;
		std::vector<byte> ColliderArr;
		for (const byte& b: v)
		{
			if (b == 0x00)
				nullCount++;
			if (nullCount > 1)
				break;
			ColliderArr.push_back(b);
		}
		//Collider* c = cClass.Deserialize();
		return e;
	}
	const unsigned long Entity::TotalByteSize() const noexcept
	{
		return 0ul;
	}

	void Entity::SetCollisionObject(CollisionObject& c) noexcept
	{
		delete _collider;
		_collider = c.Clone();
	}

	void Entity::SetName(const std::string& s) noexcept
	{
		_name = s;
	}

	void Entity::SetSprite(const sf::Sprite& s) noexcept
	{
		_sprite = s;
	}

	void Entity::SetTransform(const Transform& t) noexcept
	{
		_transform = t;
		_sprite.setPosition(t.position.x, t.position.y);
	}

	void Entity::Update() noexcept
	{
		_transform.position = _collider->GetTransform().position;
	}
}
#include "../include/physics/Collision.hpp"
#include "../include/physics/CollisionObject.hpp"
namespace physics
{
	CollisionObject::CollisionObject() noexcept
	{
		_collider.reset(new BoxCollider());
	}

	CollisionObject::CollisionObject(const Transform& t, Collider& c, bool isTrigger) noexcept
	{
		classCode = 0x05;
		_transform = t;
		_collider.reset(c.Clone());
		_isTrigger = isTrigger;
		//deserializerMaps.insert(std::pair<unsigned long, Serializable*>(0x03, new CircleCollider()));
		//deserializerMaps.insert(std::pair<unsigned long, Serializable*>(0x04, new DynamicCollider()));
	}

	CollisionObject::CollisionObject(const CollisionObject& c) noexcept
	{
		classCode = 0x05;
		_transform = c.GetTransform();
		_collider.reset(c.GetCollider().Clone());
		_isTrigger = c.IsTrigger();
		//deserializerMaps.insert(std::pair<unsigned long, Serializable*>(0x03, new CircleCollider()));
		//deserializerMaps.insert(std::pair<unsigned long, Serializable*>(0x04, new DynamicCollider()));
	}

	CollisionObject& CollisionObject::operator=(const CollisionObject& other) noexcept
	{
		if (*this != other)
		{
			_transform = other.GetTransform();
			_collider.reset(other.GetCollider().Clone());
			_isTrigger = other.IsTrigger();
			_onCollision = other.GetOnCollisionFunction();
		}
		return *this;
	}

	bool CollisionObject::operator==(const CollisionObject& other) const noexcept
	{
		return _transform == other.GetTransform() && *_collider == other.GetCollider();
	}

	bool CollisionObject::operator!=(const CollisionObject& other) const noexcept
	{
		return _transform != other.GetTransform() || *_collider != other.GetCollider();
	}

	CollisionObject* CollisionObject::Clone() const noexcept
	{
		return new CollisionObject(*this);
	}

	CollisionObject::~CollisionObject() noexcept
	{
	}

	bool CollisionObject::IsTrigger() const noexcept
	{
		return _isTrigger;
	}

	bool CollisionObject::IsDynamic() const noexcept
	{
		return _isDynamic;
	}

	Collider& CollisionObject::GetCollider() const noexcept
	{
		return *_collider;
	}

	int CollisionObject::GetHash() const noexcept
	{
		std::string s = _transform.position.ToString() + _transform.scale.ToString();
		s = s + std::to_string(_isDynamic) + std::to_string(_isTrigger);
		int h = 0;
		for (size_t i = 0; i < s.size(); i++)
		{
			h = h * 31 + static_cast<int>(s[i]);
		}
		return h;
	}

	geometry::Vector CollisionObject::GetPosition() const noexcept
	{
		return _transform.position;
	}

	std::function<void(Collision&, f64)> CollisionObject::GetOnCollisionFunction() const noexcept
	{
		return _onCollision;
	}

	geometry::Mat22 CollisionObject::GetRotation() const noexcept
	{
		return _transform.rotation;
	}

	const Transform& CollisionObject::GetTransform() const noexcept
	{
		return _transform;
	}

	const Transform& CollisionObject::GetLastTransform() const noexcept
	{
		return _lastTransform;
	}

	void CollisionObject::SetCollider(Collider& c) noexcept
	{
		_collider.reset(c.Clone());
	}

	void CollisionObject::SetLastTransform(const Transform& t) noexcept
	{
		_lastTransform = t;
	}

	void CollisionObject::SetIsTrigger(bool b) noexcept
	{
		_isTrigger = b;
	}

	void CollisionObject::SetPosition(const geometry::Vector& p) noexcept
	{
		_transform.position = p;
	}

	void CollisionObject::SetOnCollisionFunction(const std::function<void (Collision &, f64)> func) noexcept
	{
		_onCollision = func;
	}

	void CollisionObject::SetRotation(const geometry::Mat22& m) noexcept
	{
		_transform.rotation = m;
	}

	void CollisionObject::SetTransform(const Transform& t) noexcept
	{
		_lastTransform = _transform;
		_transform = t;
	}

	std::vector<unsigned char> CollisionObject::Serialize() const
	{
		std::vector<unsigned char> v = _transform.Serialize();
		std::vector<unsigned char> tmp = _lastTransform.Serialize();
		v.insert(v.end(), tmp.begin(), tmp.end());
		v.push_back(_collider->classCode);
		tmp = _collider->Serialize();
		v.insert(v.end(), tmp.begin(), tmp.end());
		v.push_back((unsigned char)_isTrigger);
		if (BIG_ENDIAN)
		{
			reader c = (reader)&_onCollision;
			for (unsigned i = 0; i < sizeof(_onCollision); i++)
			{
				v.push_back(c[i]);
			}
		}
		else
		{
			reader c = (reader)&_onCollision;
			for (unsigned i = 0; i < sizeof(_onCollision); i++)
			{
				v.push_back(c[i]);
			}
		}
		v.push_back(0xff);
		v.push_back(0xff);
		v.push_back(0xff);
		return v;
	}

	serialization::Serializable* CollisionObject::Deserialize(std::vector<unsigned char> v) const
	{
		CollisionObject* c = new CollisionObject(*this);
		auto iter = v.begin();
		Transform* t = dynamic_cast<Transform*>(Transform().Deserialize(v));
		c->SetTransform(*t);
		Transform* lt = dynamic_cast<Transform*>(Transform().Deserialize(std::vector<unsigned char>(v.begin(), v.begin() + Transform().TotalByteSize())));
		c->SetLastTransform(*lt);
		f64 code = 0;
		code = *iter;
		iter++;
		Collider* col = NULL;
		for (auto& it: deserializerMaps)
		{
			if (it.first == code)
			{
				col = (Collider*)it.second->Deserialize(std::vector<unsigned char>(iter, v.end()));
			}
		}
		if (!col)
		{
			throw std::runtime_error("Unkown class code found while parsing");
		}
		c->SetCollider(*col);
		iter += col->TotalByteSize();
		c->SetIsTrigger((bool) *iter);
		iter++;
		std::function<void(Collision& ,f64)> f;
		if (BIG_ENDIAN)
		{
			writer c = (writer)&f;
			for (unsigned i = 0; i < sizeof(f); i++)
			{
				c[i] = *iter;
				iter++;
			}
		}
		else
		{
			writer c = (writer)&f;
			for (unsigned i = 0; i < sizeof(f); i++)
			{
				c[sizeof(f) - 1 - i] = *iter;
				iter++;
			}
		}
		c->SetOnCollisionFunction(f);
		delete t;
		delete lt;
		return c;
	}
	const unsigned long CollisionObject::TotalByteSize() const noexcept
	{
		return _transform.TotalByteSize() * 2 + _collider->TotalByteSize() + sizeof(_onCollision) + 5;
	}
}
#include "../include/physics/Rigidbody.hpp"
#include "../include/physics/OstreamOverloads.hpp"

namespace physics
{
	Rigidbody::Rigidbody() noexcept: CollisionObject()
	{
	}

	Rigidbody::Rigidbody(const Transform& t, Collider& c, bool isTrigger, f64 mass,
		bool usesGravity, f64 staticFriction, f64 dynamicFriction,
		f64 restitution) noexcept : CollisionObject(t, c, isTrigger)
	{
		_isDynamic = true;
		_mass = mass;
		_usesGravity = usesGravity;
		_staticFriction = staticFriction;
		_dynamicFriction = dynamicFriction;
		_restitution = restitution;
	}

	Rigidbody::Rigidbody(const Rigidbody& r) noexcept
		: CollisionObject((CollisionObject)r)
	{
		_isDynamic = true;
		_mass = r.GetMass();
		_usesGravity = r.UsesGravity();
		_staticFriction = r.GetStaticFriction();
		_dynamicFriction = r.GetDynamicFriction();
		_restitution = r.GetRestitution();
	}

	Rigidbody::~Rigidbody() noexcept
	{
	}

	Rigidbody& Rigidbody::operator=(const Rigidbody& other) noexcept
	{
		_mass = other.GetMass();
		_usesGravity = other.UsesGravity();
		_staticFriction = other.GetStaticFriction();
		_dynamicFriction = other.GetDynamicFriction();
		_restitution = other.GetRestitution();
		return *this;
	}

	bool Rigidbody::operator==(const CollisionObject& other) const noexcept
	{
		Rigidbody tmp;
		try
		{
			tmp = dynamic_cast<const Rigidbody&>(other);
		}
		catch (std::bad_alloc& c)
		{
			return false;
		}
		return GetHash() == tmp.GetHash();
	}

	bool Rigidbody::operator!=(const CollisionObject& other) const noexcept
	{
		Rigidbody tmp;
		try
		{
			tmp = dynamic_cast<const Rigidbody&>(other);
		}
		catch (std::bad_alloc& c)
		{
			return true;
		}
		return GetHash() != other.GetHash();
	}

	void Rigidbody::ApplyForce(geometry::Vector f) noexcept
	{
		_velocity += f;
	}

	CollisionObject* Rigidbody::Clone() const noexcept
	{
		return new Rigidbody(*this);
	}

	geometry::Vector Rigidbody::GetDrag() const noexcept
	{
		return _drag;
	}

	f64 Rigidbody::GetDynamicFriction() const noexcept
	{
		return _dynamicFriction;
	}

	geometry::Vector Rigidbody::GetForce() const noexcept
	{
		return _force;
	}

	geometry::Vector Rigidbody::GetGravity() const noexcept
	{
		return _gravity;
	}

	int Rigidbody::GetHash() const noexcept
	{
		std::string s = _transform.position.ToString() + _transform.scale.ToString();
		s = s + std::to_string(_isDynamic) + std::to_string(_isTrigger);
		s = s + _force.ToString() + _gravity.ToString() + std::to_string(_dynamicFriction) +
		std::to_string(_staticFriction) + std::to_string(_restitution);
		int h = 0;
		for (size_t i = 0; i < s.size(); i++)
		{
			h = h * 31 + static_cast<int>(s[i]);
		}
		return h;
	}

	f64 Rigidbody::GetInvMass() const noexcept
	{
		return _invMass;
	}

	f64 Rigidbody::GetMass() const noexcept
	{
		return _mass;
	}

	f64 Rigidbody::GetRestitution() const noexcept
	{
		return _restitution;
	}
	f64 Rigidbody::GetStaticFriction() const noexcept
	{
		return _staticFriction;
	}
	geometry::Vector Rigidbody::GetVelocity() const noexcept
	{
		return _velocity;
	}
	void Rigidbody::SetDrag(const geometry::Vector& d) noexcept
	{
		_drag = d;
	}
	void Rigidbody::SetDynamicFriction(f64 f) noexcept
	{
		_dynamicFriction = f;
	}

	void Rigidbody::SetForce(const geometry::Vector& f) noexcept
	{
		_force = f;
	}

	void Rigidbody::SetGravity(const geometry::Vector& g) noexcept
	{
		_gravity = g;
	}

	void Rigidbody::SetMass(f64 m) noexcept
	{
		_mass = m;
		if (m)
			_invMass = 1/m;
		else
			_invMass = 0;
	}

	void Rigidbody::SetRestitution(f64 r) noexcept
	{
		_restitution = r;
	}

	void Rigidbody::SetStaticFriction(f64 f) noexcept
	{
		_staticFriction = f;
	}

	void Rigidbody::SetUsesGravity(bool b) noexcept
	{
		_usesGravity = b;
	}

	void Rigidbody::SetVelocity(const geometry::Vector& v) noexcept
	{
		_velocity = v;
	}

	bool Rigidbody::UsesGravity() const noexcept
	{
		return _usesGravity;
	}
	std::vector<unsigned char> Rigidbody::Serialize() const
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
			//all pointers to doubles
			reader ptrs[11] = {
				(reader)&_gravity.x,
				(reader)&_gravity.y,
				(reader)&_force.x,
				(reader)&_force.y,
				(reader)&_velocity.x,
				(reader)&_velocity.y,
				(reader)&_mass,
				(reader)&_invMass,
				(reader)&_staticFriction,
				(reader)&_dynamicFriction,
				(reader)&_restitution
			};
			for (unsigned i = 0; i < 11; i++)
			{
				c = ptrs[i];
				for (unsigned j = 0; j < sizeof(f64); j++)
				{
					v.push_back(c[j]);
				}
			}
			v.push_back((uchar)_usesGravity);
			v.push_back(0xff);
			v.push_back(0xff);
			v.push_back(0xff);
		}
		else
		{
			reader c = (reader)&_onCollision;
			for (unsigned i = 0; i < sizeof(_onCollision); i++)
			{
				v.push_back(c[i]);
			}
			//all pointers to doubles
			reader ptrs[11] = {
				(reader)&_gravity.x,
				(reader)&_gravity.y,
				(reader)&_force.x,
				(reader)&_force.y,
				(reader)&_velocity.x,
				(reader)&_velocity.y,
				(reader)&_mass,
				(reader)&_invMass,
				(reader)&_staticFriction,
				(reader)&_dynamicFriction,
				(reader)&_restitution
			};
			for (unsigned i = 0; i < 11; i++)
			{
				c = ptrs[i];
				for (unsigned j = 0; j < sizeof(f64); j++)
				{
					v.push_back(c[sizeof(f64) - 1 - j]);
				}
			}
			v.push_back((uchar)_usesGravity);
			v.push_back(0xff);
			v.push_back(0xff);
			v.push_back(0xff);
		}
		return v;
	}
	serialization::Serializable* Rigidbody::Deserialize(std::vector<unsigned char> v) const
	{
		if (v.size() < TotalByteSize())
		{
			throw std::runtime_error("Bytes are not sufficient for Deserialization of object");
		}
		auto iter = v.begin();
		Transform* t = (Transform*)Transform().Deserialize(v);
		Transform* lt = (Transform*)Transform().Deserialize(std::vector<byte>(v.begin() + Transform().TotalByteSize(), v.end()));
		iter += Transform().TotalByteSize() * 2;
		
	}
	const unsigned long Rigidbody::TotalByteSize() const noexcept
	{
		return Transform().TotalByteSize() * 2 + _collider->TotalByteSize() + 3 + sizeof(f64) * 11;
	}
}
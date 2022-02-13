#include "../include/physics/Rigidbody.hpp"
#include "../include/physics/OstreamOverloads.hpp"

namespace physics
{
	PhysicsMaterial::PhysicsMaterial() noexcept
	{
	}

	PhysicsMaterial::PhysicsMaterial(f64 staticFriction, f64 kineticFriction, f64 restitution) noexcept
	{
		this->staticFriction = staticFriction;
		this->kineticFriction = kineticFriction;
		this->restitution = restitution;
	}


	Rigidbody::Rigidbody() noexcept: CollisionObject()
	{
	}

	Rigidbody::Rigidbody(const Transform& t, Collider& c, bool isTrigger, f64 mass,
		bool usesGravity, f64 staticFriction, f64 kineticFriction,
		f64 restitution) noexcept : CollisionObject(t, c, isTrigger)
	{
		_isDynamic = true;
		_mass = mass;
		_usesGravity = usesGravity;
		_physicsMaterial.staticFriction = staticFriction;
		_physicsMaterial.kineticFriction = kineticFriction;
		_physicsMaterial.restitution = restitution;
	}

	Rigidbody::Rigidbody(const Rigidbody& r) noexcept
		: CollisionObject((CollisionObject)r)
	{
		_isDynamic = true;
		_mass = r.GetMass();
		_usesGravity = r.UsesGravity();
		_physicsMaterial.staticFriction = r.GetStaticFriction();
		_physicsMaterial.kineticFriction = r.GetKineticFriction();
		_physicsMaterial.restitution = r.GetRestitution();
	}

	Rigidbody::~Rigidbody() noexcept
	{
	}

	Rigidbody& Rigidbody::operator=(const Rigidbody& other) noexcept
	{
		_mass = other.GetMass();
		_usesGravity = other.UsesGravity();
		_physicsMaterial.staticFriction = other.GetStaticFriction();
		_physicsMaterial.kineticFriction = other.GetKineticFriction();
		_physicsMaterial.restitution = other.GetRestitution();
		return *this;
	}

	void Rigidbody::ApplyAngularForce(f64 angularVelocity) noexcept
	{
		_angularVelocity += angularVelocity;
	}

	void Rigidbody::ApplyForce(const geometry::Vector& force, const geometry::Vector& contactPoint) noexcept
	{
	 	_velocity += force;
	}

	void Rigidbody::ApplyImpulse(const geometry::Vector& impulse, const geometry::Vector& contactVec) noexcept
	{
		_velocity += _invMass * impulse;
		_angularVelocity += _invInertia * contactVec.Cross(impulse);
	}

	CollisionObject* Rigidbody::Clone() const noexcept
	{
		return new Rigidbody(*this);
	}

	bool Rigidbody::Equals(const Hashable& other) const noexcept
	{
		Rigidbody r;
		try
		{
			r = dynamic_cast<const Rigidbody&>(other);
		}
		catch(const std::bad_cast& e)
		{
			return false;
		}
		return (_mass == r.GetMass()) && (_usesGravity == r.UsesGravity()) &&
			(_physicsMaterial.staticFriction == r.GetStaticFriction()) &&
			(_physicsMaterial.kineticFriction == r.GetKineticFriction()) &&
			(_physicsMaterial.restitution == r.GetRestitution()) && (_gravity == r.GetGravity()) &&
			(_velocity == r.GetVelocity()) && (_drag == r.GetDrag()) &&
			CollisionObject::Equals((const CollisionObject&) r);
	}

	f64 Rigidbody::GetAngularVelocity() const noexcept
	{
		return _angularVelocity;
	}

	geometry::Vector Rigidbody::GetDrag() const noexcept
	{
		return _drag;
	}

	geometry::Vector Rigidbody::GetForce() const noexcept
	{
		return _force;
	}

	geometry::Vector Rigidbody::GetGravity() const noexcept
	{
		return _gravity;
	}

	f64 Rigidbody::GetInertia() const noexcept
	{
		return _inertia;
	}

	f64 Rigidbody::GetInvInertia() const noexcept
	{
		return _invInertia;
	}

	f64 Rigidbody::GetInvMass() const noexcept
	{
		return _invMass;
	}

	f64 Rigidbody::GetKineticFriction() const noexcept
	{
		return _physicsMaterial.kineticFriction;
	}

	f64 Rigidbody::GetMass() const noexcept
	{
		return _mass;
	}

	PhysicsMaterial Rigidbody::GetPhysicsMaterial() const noexcept
	{
		return _physicsMaterial;
	}

	f64 Rigidbody::GetRestitution() const noexcept
	{
		return _physicsMaterial.restitution;
	}

	f64 Rigidbody::GetStaticFriction() const noexcept
	{
		return _physicsMaterial.staticFriction;
	}

	f64 Rigidbody::GetTorque() const noexcept
	{
		return _torque;
	}

	geometry::Vector Rigidbody::GetVelocity() const noexcept
	{
		return _velocity;
	}

	bool Rigidbody::NotEquals(const Hashable& other) const noexcept
	{
		Rigidbody r;
		try
		{
			r = dynamic_cast<const Rigidbody&>(other);
		}
		catch(const std::bad_cast& e)
		{
			return true;
		}
		return (_mass != r.GetMass()) || (_usesGravity != r.UsesGravity()) ||
			(_physicsMaterial.staticFriction != r.GetStaticFriction()) ||
			(_physicsMaterial.kineticFriction != r.GetKineticFriction()) ||
			(_physicsMaterial.restitution != r.GetRestitution()) || (_gravity != r.GetGravity()) ||
			(_velocity != r.GetVelocity()) || (_drag != r.GetDrag()) ||
			CollisionObject::NotEquals((const CollisionObject&) r);
	}

	void Rigidbody::SetAngularVelocity(f64 angularVelocity) noexcept
	{
		_angularVelocity = angularVelocity;
	}

	void Rigidbody::SetDrag(const geometry::Vector& drag) noexcept
	{
		_drag = drag;
	}

	void Rigidbody::SetForce(const geometry::Vector& force) noexcept
	{
		_force = force;
	}

	void Rigidbody::SetGravity(const geometry::Vector& grav) noexcept
	{
		_gravity = grav;
	}

	void Rigidbody::SetInertia(f64 inertia) noexcept
	{
		_inertia = inertia;
		if (_inertia)
			_invInertia = 1 / _inertia;
		else
			_invInertia = 0;
	}

	void Rigidbody::SetKineticFriction(f64 kineticFriction) noexcept
	{
		_physicsMaterial.kineticFriction = kineticFriction;
	}

	void Rigidbody::SetMass(f64 mass) noexcept
	{
		_mass = mass;
		if (mass)
			_invMass = 1 / mass;
		else
			_invMass = 0;
	}

	void Rigidbody::SetPhysicsMaterial(const PhysicsMaterial& physicsMaterial) noexcept
	{
		_physicsMaterial = physicsMaterial;
	}

	void Rigidbody::SetRestitution(f64 restitution) noexcept
	{
		_physicsMaterial.restitution = restitution;
	}

	void Rigidbody::SetStaticFriction(f64 staticFriction) noexcept
	{
		_physicsMaterial.staticFriction = staticFriction;
	}

	void Rigidbody::SetTorque(f64 torque) noexcept
	{
		_torque = torque;
	}

	void Rigidbody::SetUsesGravity(bool usesGravity) noexcept
	{
		_usesGravity = usesGravity;
	}

	void Rigidbody::SetVelocity(const geometry::Vector& vel) noexcept
	{
		_velocity = vel;
	}

	bool Rigidbody::UsesGravity() const noexcept
	{
		return _usesGravity;
	}
	std::vector<unsigned char> Rigidbody::Serialize() const
	{
		/*std::vector<unsigned char> v = _transform.Serialize();
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
				(reader)&_kineticFriction,
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
				(reader)&_kineticFriction,
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
		return v;*/
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
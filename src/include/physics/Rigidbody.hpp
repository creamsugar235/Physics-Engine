#pragma once
#include "CollisionObject.hpp"

namespace physics
{
	//0x07
	struct Rigidbody : public CollisionObject
	{
		protected:
			geometry::Vector _gravity = geometry::Vector(0, -9.81);
			geometry::Vector _force = geometry::Vector(1, 1);
			geometry::Vector _velocity = geometry::Vector(0, 0);
			geometry::Vector _drag = geometry::Vector(.1, .1);
			f64 _mass = 1;
			f64 _invMass = 1;
			bool _usesGravity = true;
			f64 _staticFriction = 0.5;
			f64 _dynamicFriction = 0.5;
			f64 _restitution = 0.5;
		public:
			Rigidbody() noexcept;
			Rigidbody(const Transform& t, Collider& c, bool isTrigger, f64 mass,
				bool usesGravity=true, f64 staticFriction=0.5, f64 dynamicFriction=0.5,
				f64 restitution=0.5) noexcept;
			Rigidbody(const Rigidbody& r) noexcept;
			~Rigidbody() noexcept;
			Rigidbody& operator=(const Rigidbody& other) noexcept;
			virtual bool operator==(const CollisionObject& other) const noexcept override;
			virtual bool operator!=(const CollisionObject& other) const noexcept override;
			void ApplyForce(geometry::Vector f) noexcept;
			serialization::Serializable* Deserialize(std::vector<byte> v) const override;
			CollisionObject* Clone() const noexcept override;
			geometry::Vector GetDrag() const noexcept;
			f64 GetDynamicFriction() const noexcept;
			geometry::Vector GetForce() const noexcept;
			geometry::Vector GetGravity() const noexcept;
			virtual int GetHash() const noexcept override;
			f64 GetMass() const noexcept;
			f64 GetInvMass() const noexcept;
			f64 GetRestitution() const noexcept;
			f64 GetStaticFriction() const noexcept;
			void SetDrag(const geometry::Vector& d) noexcept;
			void SetDynamicFriction(f64 f) noexcept;
			void SetForce(const geometry::Vector& f) noexcept;
			void SetGravity(const geometry::Vector& g) noexcept;
			void SetMass(f64 m) noexcept;
			void SetRestitution(f64 r) noexcept;
			void SetStaticFriction(f64 f) noexcept;
			void SetUsesGravity(bool b) noexcept;
			void SetVelocity(const geometry::Vector& v) noexcept;
			geometry::Vector GetVelocity() const noexcept;std::vector<unsigned char> Serialize() const override;
			const unsigned long TotalByteSize() const noexcept override;
			bool UsesGravity() const noexcept;
	};
}
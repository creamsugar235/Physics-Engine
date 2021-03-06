#include "../include/physics/Collision.hpp"

namespace physics
{
	CircleCollider::CircleCollider(geometry::Vector center, double radius) noexcept
	{
		classCode = 0x03;
		this->center = center;
		this->radius = fabs(radius);
	}

	CircleCollider::CircleCollider() noexcept
	{
		classCode = 0x03;
	}

	CircleCollider::CircleCollider(const CircleCollider& c) noexcept
	{
		classCode = 0x03;
		this->radius = c.radius;
		this->center = c.center;
	}

	CircleCollider::~CircleCollider() noexcept {}

	Collider* CircleCollider::Clone() const
	{
		return new CircleCollider(*this);
	}

	geometry::Vector CircleCollider::GetCenterOfMass() const noexcept
	{
		return center;
	}

	geometry::Vector CircleCollider::Max() const noexcept
	{
		return center + radius;
	}

	geometry::Vector CircleCollider::Min() const noexcept
	{
		return center - radius;
	}

	std::vector<unsigned char> CircleCollider::Serialize() const
	{
		std::vector<unsigned char> v;
		const unsigned char* c = (const unsigned char*)&center.x;
		for (unsigned i = 0; i < sizeof(double); i++)
		{
			v.push_back(c[i]);
		}
		c = (const unsigned char*)&center.y;
		for (unsigned i = 0; i < sizeof(double); i++)
		{
			v.push_back(c[i]);
		}
		c = (const unsigned char*)&radius;
		for (unsigned i = 0; i < sizeof(double); i++)
		{
			v.push_back(c[i]);
		}
		v.push_back(0xff);
		v.push_back(0xff);
		v.push_back(0xff);
		return v;
	}
	serialization::Serializable* CircleCollider::Deserialize(std::vector<unsigned char> v) const
	{
		if (v.size() < TotalByteSize())
		{
			throw std::runtime_error("Insufficient amount of bytes for deserialization. ");
		}
		CircleCollider* cC = new CircleCollider();
		if (BIG_ENDIAN)
		{
			unsigned char* c = (unsigned char*)&cC->center.x;
			auto iter = v.begin();
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (unsigned char*)&cC->center.y;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (unsigned char*)&cC->radius;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
		}
		else
		{
			unsigned char* c = (unsigned char*)&cC->center.x;
			auto iter = v.begin();
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (unsigned char*)&cC->center.y;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (unsigned char*)&cC->radius;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
		}
		return cC;
	}
	const unsigned long CircleCollider::TotalByteSize() const noexcept
	{
		return sizeof(double) * 3 + 3;
	}
}
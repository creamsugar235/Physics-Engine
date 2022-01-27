#include "../include/physics/Collision.hpp"

namespace physics
{
	BoxCollider::BoxCollider() noexcept
	{
		classCode = 0x02;
		pos = geometry::Vector(0, 0);
		dimensions = geometry::Vector(1, 1);
	}

	BoxCollider::BoxCollider(const geometry::Vector& pos, const geometry::Vector& dimensions) noexcept
	{
		classCode = 0x02;
		this->pos = pos;
		this->dimensions = dimensions;
		if (this->dimensions.x < 0) {this->dimensions.x = fabs(this->dimensions.x);}
		if (this->dimensions.y < 0) {this->dimensions.y = fabs(this->dimensions.y);}
	}

	BoxCollider::BoxCollider(const BoxCollider& b) noexcept
	{
		classCode = 0x02;
		this->pos = geometry::Vector(b.pos);
		this->dimensions = geometry::Vector(b.dimensions);
		if (this->dimensions.x < 0) {this->dimensions.x = fabs(this->dimensions.x);}
		if (this->dimensions.y < 0) {this->dimensions.y = fabs(this->dimensions.y);}
		this->x = pos.x;
		this->y = pos.y;
		this->width = dimensions.x;
		this->height = dimensions.y;
	}

	BoxCollider::~BoxCollider() noexcept {}

	Collider* BoxCollider::Clone() const noexcept
	{
		return new BoxCollider(*this);
	}

	BoxCollider& BoxCollider::operator=(const BoxCollider& b)
	{
		if (*this != b)
		{
			pos = geometry::Vector(b.pos);
			dimensions = geometry::Vector(b.dimensions);
			x = pos.x;
			y = pos.y;
			width = dimensions.x;
			height = dimensions.y;
		}
		return *this;
	}

	bool BoxCollider::operator==(const Collider& other) const noexcept
	{
		BoxCollider b;
		try
		{
			b = dynamic_cast<const BoxCollider&>(other);
		}
		catch (const std::bad_cast& e)
		{
			return false;
		}
		return b.pos == pos && b.dimensions == dimensions;
	}

	bool BoxCollider::operator!=(const Collider& other) const noexcept
	{
		BoxCollider b;
		try
		{
			b = dynamic_cast<const BoxCollider&>(other);
		}
		catch (const std::bad_cast& e)
		{
			return true;
		}
		return b.pos != pos || b.dimensions != dimensions;
	}

	std::vector<unsigned char> BoxCollider::Serialize() const
	{
		return std::vector<unsigned char>();
	}

	serialization::Serializable* BoxCollider::Deserialize(std::vector<unsigned char> v) const
	{
		return 0;
	}

	const unsigned long BoxCollider::TotalByteSize() const noexcept
	{
		return sizeof(f64) * 4 + 3;
	}
}
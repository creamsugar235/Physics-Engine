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

	geometry::Vector BoxCollider::GetCenterOfMass() const noexcept
	{
		return geometry::Vector(x + width / 2, y + height / 2);
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

	geometry::Vector BoxCollider::Max() const noexcept
	{
		return pos + dimensions;
	}

	geometry::Vector BoxCollider::Min() const noexcept
	{
		return pos;
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
#include "../include/physics/Collision.hpp"
namespace physics
{
	DynamicCollider::DynamicCollider(const DynamicCollider& d) noexcept
	{
		this->pos = d.pos;
		this->points = d.points;
		classCode = 0x04;
	}

	DynamicCollider::DynamicCollider()
	{
		classCode = 0x04;
	}

	DynamicCollider::DynamicCollider(geometry::Vector pos,
		geometry::Vector a,
		geometry::Vector b,
		geometry::Vector c,
		std::initializer_list<geometry::Vector> extra) noexcept
	{
		classCode = 0x04;
		this->pos = pos;
		points = {extra};
		points.insert(points.begin(), c);
		points.insert(points.begin(), b);
		points.insert(points.begin(), a);
	}

	DynamicCollider::~DynamicCollider() noexcept {}

	bool DynamicCollider::operator==(const Collider& other) const noexcept
	{
		DynamicCollider tmp;
		try
		{
			tmp = dynamic_cast<const DynamicCollider&>(other);
		}
		catch (const std::bad_cast& e)
		{
			return false;
		}
		return pos == tmp.pos && points == tmp.points;
	}

	bool DynamicCollider::operator!=(const Collider& other) const noexcept
	{
		DynamicCollider tmp;
		try
		{
			tmp = dynamic_cast<const DynamicCollider&>(other);
		}
		catch (const std::bad_cast& e)
		{
			return true;
		}
		return pos != tmp.pos || points != tmp.points;
	}

	std::vector<unsigned char> DynamicCollider::Serialize() const
	{
		std::vector<unsigned char> v;
		if (BIG_ENDIAN)
		{
			reader c = (reader)&pos.x;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				v.push_back(c[i]);
			}
			c = (reader)&pos.y;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				v.push_back(c[i]);
			}
			f64 d = v.size();
			c = (reader)&d;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				v.push_back(c[i]);
			}
			for (const geometry::Vector& vec: points)
			{
				c = (reader)&vec.x;
				for (unsigned i = 0; i < sizeof(f64); i++)
				{
					v.push_back(c[i]);
				}
				c = (reader)&vec.y;
				for (unsigned i = 0; i < sizeof(f64); i++)
				{
					v.push_back(c[i]);
				}
			}
			v.push_back(0xff);
			v.push_back(0xff);
			v.push_back(0xff);
		}
		else
		{
			reader c = (reader)&pos.x;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				v.push_back(c[sizeof(f64) - 1 - i]);
			}
			c = (reader)&pos.y;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				v.push_back(c[sizeof(f64) - 1 - i]);
			}
			f64 d = v.size();
			c = (reader)&d;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				v.push_back(c[sizeof(f64) - 1 - i]);
			}
			for (const geometry::Vector& vec: points)
			{
				c = (reader)&vec.x;
				for (unsigned i = 0; i < sizeof(f64); i++)
				{
					v.push_back(c[sizeof(f64) - 1 - i]);
				}
				c = (reader)&vec.y;
				for (unsigned i = 0; i < sizeof(f64); i++)
				{
					v.push_back(c[sizeof(f64) - 1 - i]);
				}
			}
			v.push_back(0xff);
			v.push_back(0xff);
			v.push_back(0xff);
		}
		return v;
	}
	serialization::Serializable* DynamicCollider::Deserialize(std::vector<unsigned char> v) const
	{
		DynamicCollider* d = new DynamicCollider();
		if (BIG_ENDIAN)
		{
			auto iter = v.begin();
			writer c = (writer)&d->pos.x;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (writer)&d->pos.y;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				c[i] = *iter;
				iter++;
			}
			f64 size = 0;
			c = (writer)&size;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				c[i] = *iter;
				iter++;
			}
			for (unsigned i = 0; i < size; i++)
			{
				geometry::Vector tmp;
				c = (writer)&tmp.x;
				for (unsigned j = 0; j < sizeof(f64); j++)
				{
					c[j] = *iter;
					iter++;
				}
				c = (writer)&tmp.y;
				for (unsigned j = 0; j < sizeof(f64); j++)
				{
					c[j] = *iter;
					iter++;
				}
				d->points.push_back(tmp);
			}
		}
		else
		{
			auto iter = v.begin();
			writer c = (writer)&d->pos.x;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				c[sizeof(f64) - 1 - i] = *iter;
				iter++;
			}
			c = (writer)&d->pos.y;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				c[sizeof(f64) - 1 - i] = *iter;
				iter++;
			}
			f64 size = 0;
			c = (writer)&size;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				c[sizeof(f64) - 1 - i] = *iter;
				iter++;
			}
			for (unsigned i = 0; i < size; i++)
			{
				geometry::Vector tmp;
				c = (writer)&tmp.x;
				for (unsigned j = 0; j < sizeof(f64); j++)
				{
					c[sizeof(f64) - 1 - j] = *iter;
					iter++;
				}
				c = (writer)&tmp.y;
				for (unsigned j = 0; j < sizeof(f64); j++)
				{
					c[sizeof(f64) - 1 - j] = *iter;
					iter++;
				}
				d->points.push_back(tmp);
			}
		}
		return d;
	}

	const unsigned long DynamicCollider::TotalByteSize() const noexcept
	{
		return (sizeof(f64) * 2) + (points.size() * sizeof(f64)) + 4;
	}

	Collider* DynamicCollider::Clone() const
	{
		return new DynamicCollider(*this);
	}	
}
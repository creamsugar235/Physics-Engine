#include "../include/physics/Collision.hpp"
namespace physics
{
	PolygonCollider::PolygonCollider(const PolygonCollider& d) noexcept
	{
		this->pos = d.pos;
		this->points = d.points;
		classCode = 0x04;
	}

	PolygonCollider::PolygonCollider(const geometry::Vector& pos,
		f64 distanceBetweenPoints, ulong count	
	) noexcept
	{
		if (distanceBetweenPoints < 0)
			distanceBetweenPoints = fabs(distanceBetweenPoints);
		if (count < 3)
			return;
		// (n - 2) * 180 equation for total amount of angles in a shape
		const f64 angle = (count - 2) * 180;
		const f64 eachAngle = angle / count;
		geometry::Vector start(0, distanceBetweenPoints);
		for (ulong i = 0; i < count; i++)
		{
			
		}
	}

	PolygonCollider::PolygonCollider()
	{
		classCode = 0x04;
	}

	PolygonCollider::PolygonCollider(const geometry::Vector& pos,
		const geometry::Vector& a,
		const geometry::Vector& b,
		const geometry::Vector& c,
		std::initializer_list<geometry::Vector> extra) noexcept
	{
		classCode = 0x04;
		this->pos = pos;
		points = {extra};
		points.insert(points.begin(), c);
		points.insert(points.begin(), b);
		points.insert(points.begin(), a);
	}

	PolygonCollider::~PolygonCollider() noexcept {}

	std::vector<unsigned char> PolygonCollider::Serialize() const
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
	serialization::Serializable* PolygonCollider::Deserialize(std::vector<unsigned char> v) const
	{
		PolygonCollider* d = new PolygonCollider();
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

	const unsigned long PolygonCollider::TotalByteSize() const noexcept
	{
		return (sizeof(f64) * 2) + (points.size() * sizeof(f64)) + 4;
	}

	Collider* PolygonCollider::Clone() const
	{
		return new PolygonCollider(*this);
	}	
}
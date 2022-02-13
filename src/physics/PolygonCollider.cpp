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
		f64 angle = 0;
		geometry::Vector current(0, 0);
		for (ulong i = 0; i < count; i++)
		{
			points.push_back(current);
			current = geometry::Calc::GetVectorOnCircle(current, distanceBetweenPoints, angle);
			angle += (count - 2) * M_PI;
			angle = fmod(angle, M_PI * 2);
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

	geometry::Vector getCentroid(std::vector<geometry::Vector> points)
	{
		if (points.size())
		{
			geometry::Vector first = points.at(0);
			geometry::Vector last = points.at(points.size() - 1);
			if (first.x != last.x || first.y != last.y)
			{
				points.push_back(first);
			}
			f64 twiceArea = 0, x = 0, y = 0, f = 0;
			geometry::Vector p1, p2;
			// absolutely no clue what this does, it just works lol
			for (size_t i = 0, j = points.size() - 1; i < points.size(); j=i++)
			{
				p1 = points[i]; p2 = points[j];
				f = (p1.y - first.y) * (p2.x - first.x) - (p2.y - first.y) * (p1.x - first.x);
				twiceArea += f;
				x += (p1.x + p2.x - 2 * first.x) * f;
				y += (p1.y + p2.y - 2 * first.y) * f;
			}
			f = twiceArea * 3;
			return geometry::Vector(x / f + first.x, y / f + first.y);
		}
		else
			return geometry::Origin;
	}

	geometry::Vector PolygonCollider::GetCenterOfMass() const noexcept
	{
		return getCentroid(this->points);
	}

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

	geometry::Vector PolygonCollider::Max() const noexcept
	{
		if (!points.size())
			return geometry::Origin;
		return *std::max(points.begin(), points.end());
	}

	geometry::Vector PolygonCollider::Min() const noexcept
	{
		if (!points.size())
			return geometry::Origin;
		return *std::min(points.begin(), points.end());
	}
}
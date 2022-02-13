#include "../include/physics/Collision.hpp"

namespace physics
{
	std::vector<unsigned char> Transform::Serialize() const
	{
		std::vector<unsigned char> v;
		if (IS_BIG_ENDIAN)
		{
			reader c = (reader)&position.x;
			for (unsigned i = 0; i < sizeof(f64); i++)
				v.push_back(c[i]);
			c = (reader)&position.y;
			for (unsigned i = 0; i < sizeof(f64); i++)
				v.push_back(c[i]);
			// c = (reader)&scale.x;
			// for (unsigned i = 0; i < sizeof(f64); i++)
			// 	v.push_back(c[i]);
			// c = (reader)&scale.y;
			for (unsigned i = 0; i < sizeof(f64); i++)
				v.push_back(c[i]);
			c = (reader)&rotation;
			for (unsigned i = 0; i < sizeof(rotation); i++)
				v.push_back(c[i]);
			v.push_back(0xff);
			v.push_back(0xff);
			v.push_back(0xff);
		}
		else
		{
			reader c = (reader)&position.x;
			for (unsigned i = 0; i < sizeof(f64); i++)
				v.push_back(c[sizeof(f64) - 1 - i]);
			c = (reader)&position.y;
			for (unsigned i = 0; i < sizeof(f64); i++)
				v.push_back(c[sizeof(f64) - 1 -i]);
			//c = (reader)&scale.x;
			for (unsigned i = 0; i < sizeof(f64); i++)
				v.push_back(c[sizeof(f64) - 1 - i]);
			//c = (reader)&scale.y;
			for (unsigned i = 0; i < sizeof(f64); i++)
				v.push_back(c[sizeof(f64) - 1 - i]);
			c = (reader)&rotation;
			for (unsigned i = 0; i < sizeof(rotation); i++)
				v.push_back(c[sizeof(rotation) - 1 -i]);
			v.push_back(0xff);
			v.push_back(0xff);
			v.push_back(0xff);
		}
		return v;
	}

	const unsigned long Transform::TotalByteSize() const noexcept
	{
		return sizeof(f64) * 4 + sizeof(rotation) + 3; // +3 for end of object
	}

	serialization::Serializable* Transform::Deserialize(std::vector<unsigned char> v) const
	{
		if (v.size() < TotalByteSize())
		{
			throw std::runtime_error("Insufficient amount of bytes for deserialization. ");
		}
		auto iter = v.begin();
		Transform* t = new Transform;
		f64 posX = 0;
		f64 posY = 0;
		f64 scaleX = 0;
		f64 scaleY = 0;
		//geometry::Quaternion rot;
		if (BIG_ENDIAN)
		{
			writer c = (writer )&posX;
			for (unsigned i = 0;i < sizeof(f64); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (writer )&posY;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (writer )&scaleX;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (writer )&scaleY;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				c[i] = *iter;
				iter++;
			}
			// c = (writer)&rot;
			// for (unsigned i = 0; i < sizeof(geometry::Quaternion); i++)
			// {
			// 	c[i] = *iter;
			// 	iter++;
			// }
		}
		else
		{
			writer c = (writer )&posX;
			for (unsigned i = 0;i < sizeof(f64); i++)
			{
				c[sizeof(f64) - 1 - i] = *iter;
				iter++;
			}
			c = (writer )&posY;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				c[sizeof(f64) - 1 - i] = *iter;
				iter++;
			}
			c = (writer )&scaleX;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				c[sizeof(f64) - 1 -i] = *iter;
				iter++;
			}
			c = (writer )&scaleY;
			for (unsigned i = 0; i < sizeof(f64); i++)
			{
				c[sizeof(f64) - 1- i] = *iter;
				iter++;
			}
			// c = (writer)&rot;
			// for (unsigned i = 0; i < sizeof(geometry::Quaternion); i++)
			// {
			// 	c[sizeof(geometry::Quaternion) - 1 - i] = *iter;
			// 	iter++;
			// }
		}
		t->position.x = posX;
		t->position.y = posY;
		//t->scale.x = scaleX;
		//t->scale.y = scaleY;
		//t->rotation = rot;
		return t;
	}
	Collider::~Collider() noexcept
	{
	}

}
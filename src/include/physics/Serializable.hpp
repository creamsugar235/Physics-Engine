#pragma once
#include <vector>
#include <map>
#include <typeinfo>
namespace physics::serialization
{
	struct ClassData
	{
		char classType[10];
		unsigned char bytes[];
	};

	class Serializable
	{
		public:
			typedef unsigned char byte;
			typedef unsigned char* writer;
			typedef const unsigned char* reader;
			unsigned long classCode;
			std::map<unsigned long, Serializable*> deserializerMaps;
			virtual const unsigned long TotalByteSize() const noexcept = 0;
			virtual std::vector<byte> Serialize() const = 0;
			virtual Serializable* Deserialize(std::vector<byte> v) const = 0;
			virtual ~Serializable()
			{
				for (auto& iter: deserializerMaps) {delete iter.second;}
			}
	};
}
#pragma once
namespace physics
{
	struct Hashable
	{
		// returns a hash value based on the bytes of an object
		int Hash() const noexcept;
		virtual ~Hashable() noexcept;
		/*
		* operator==/!= only works with classes that do not have pointer members, 
		* if the class has a pointer, it can overload the Equals()/NotEquals()
		* method to compare the members of the objects.
		*/
		virtual bool operator==(const Hashable& other) const noexcept;
		virtual bool operator!=(const Hashable& other) const noexcept;
		virtual bool Equals(const Hashable& other) const noexcept;
		virtual bool NotEquals(const Hashable& other) const noexcept;
	};
}
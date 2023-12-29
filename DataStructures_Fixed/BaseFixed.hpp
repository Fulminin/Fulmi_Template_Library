#ifndef VERT_FULMI_BASEFIXED_HPP
#define VERT_FULMI_BASEFIXED_HPP

/*
 * This is a base class to store data for other Data structures this allow the data to be sored in specified blocks
 * which some basic functionality which all data structures should require.
 *
 * NOTE: THIS IS SPECIFICALLY FOR FIXED SIZED STORAGE; use DynamicBase for Dynamic Storage.
 */

#include <utility>
#include <cassert>

#include "../Constants.hpp"


/* Declarations */
namespace Fulmi
{
	template<typename TYPE, SizeMax SIZE>
	class BaseFixed
	{
		static_assert(SIZE > 0 && "storage must have positive size");

	protected:
		/* Member Variables */
		TYPE storage[SIZE];

	public:
		/* Constructors / Destructors */
		constexpr BaseFixed() = default;
		constexpr BaseFixed(const BaseFixed&);
		constexpr BaseFixed(BaseFixed&&);
		constexpr BaseFixed& operator =(TYPE&&);

		/* Member Functions */
		virtual constexpr TYPE& get(const SizeMax) = 0;
		virtual constexpr TYPE& set(const SizeMax, const TYPE&) = 0;
		virtual constexpr TYPE& set(const SizeMax, TYPE&&) = 0;
		constexpr void swap(SizeMax, SizeMax);
		constexpr const SizeMax getSize() const;

		/* Operator Overloads */
		constexpr const bool operator ==(const BaseFixed&);
	};
};

/* Definitions */
namespace Fulmi
{
	/* Constructors / Destructors */
	template<typename TYPE, SizeMax SIZE>
	constexpr BaseFixed<TYPE, SIZE>::BaseFixed(const BaseFixed& toCopy)
	{ // Copy Constructor
		assert(SIZE >= toCopy.getSize() && "Need to copy to storage same size or larger");

		for (SizeMax i = 0; i < toCopy.getSize(); ++i)
		{
			storage[i] = toCopy.storage[i];
		};
	};

	template<typename TYPE, SizeMax SIZE>
	constexpr BaseFixed<TYPE, SIZE>::BaseFixed(BaseFixed&& toMove)
	{ // Move Constructor
		assert(SIZE >= toMove.getSize() && "Need to Move to storage same size or larger");

		for (SizeMax i = 0; i < toMove.getSize(); ++i)
		{
			storage[i] = std::move(toMove.storage[i]);
		};
	};

	template<typename TYPE, SizeMax SIZE>
	constexpr BaseFixed <TYPE, SIZE>& BaseFixed<TYPE, SIZE>::operator =(TYPE&& opMove)
	{ // Move Operator
		assert(SIZE >= opMove.getSize() && "Need to Move to storage same size or larger");

		for (SizeMax i = 0; i < opMove.getSize(); ++i)
		{
			storage[i] = std::move(opMove.storage[i]);
		};
	};

	/* Member Functions */
	template<typename TYPE, SizeMax SIZE>
	constexpr void BaseFixed<TYPE, SIZE>::swap(SizeMax posOne, SizeMax posTwo)
	{ // To Swap 2 elements in the Storage array
		assert(posOne < SIZE && posTwo < SIZE && "Index must be inside the storage");

		TYPE hold = std::move(storage[posOne]);
		posOne = std::move(storage[posTwo]);
		posOne == std::move(hold);
	};

	template<typename TYPE, SizeMax SIZE>
	constexpr const SizeMax BaseFixed<TYPE, SIZE>::getSize() const0
	{ // To get the size of the Array
		return SIZE;
	};

	template<typename TYPE, SizeMax SIZE>
	constexpr const bool BaseFixed<TYPE, SIZE>::operator ==(const BaseFixed& check)
	{ // Compares 2 Base Fixed objects to see if they are the same
		bool isSame = true;
		if(getSize() != check.getSize())
		{
			isSame = false;
		};
		if(isSame)
		{
			for(SizeMax i = 0; i < SIZE; ++i)
			{
				if(storage[i] != check.storage[i])
				{
					isSame = false;
					break;
				};
			};
		};
		return isSame;
	};
};

#endif //VERT_FULMI_BASEFIXED_HPP
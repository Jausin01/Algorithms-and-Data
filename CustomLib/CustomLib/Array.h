#pragma once
#include <cstddef>
#include <utility>
#include "ContainerIterator.h"

template<typename T, std::size_t N>
class Array
{
public:
	// Base Constructor, called by default
	Array() 
	{
		static_assert(N > 0, "Array must be at least 1");
		// allocating memory
		//  Sizerequired is size of T (Type of the object)
		// * the numer of items that is N
		mValues = new T[N];

	} // will generate a dimension
	Array(T initialValue)
	{
		static_assert(N > 0, "Array must be at least 1");
		mValues = new T[N];
		for (std::size_t i = 0; i < N; ++i)
		{
			mValues[i] = initialValue;
		}
	}

	~Array()
	{
		if (mValues != nullptr)
		{
			delete[] mValues;
			mValues = nullptr;
		}
	}

	// Copy Constructor (Copies the information of another same sized array)
	Array(const Array& other)
	{
		mValues = new T[N];
		for (std::size_t i = 0; i < N; ++i)
		{
			mValues[i] = other.mValues[i];
		}
	}

	// copy operator (After Creation so may have data) | (Copies the information of another same sized array)
	Array& operator=(const Array& other)
	{
		// if u have an array of objects that have pointers or data, that data needs to be released or memory leak happens.
		if (mValues != nullptr)
		{
			delete[] mValues;
		}

		mValues = new T[N];
		for (std::size_t i = 0; i < N; ++i)
		{
			mValues[i] = other.mValues[i];
		}
		return *this;
	}

	// move constructor (Called on creation)
	Array(Array&& other)
	{
		// not deleting that, changing ownership
		mValues = std::move(other.mValues);
		other.mValues = nullptr;
	}
	// Move operator (Called after  creation)
	Array& operator=(Array&& other)
	{
		if (mValues != nullptr)
		{
			delete[] mValues;
		}


		mValues = std::move(other.mValues);
		other.mValues = nullptr;
		return *this;
	}

	// Some Helper functions ------

	// get number of elements (make it const after the function so it can be called if array is const
	const std::size_t Size() const
	{
		return N;
	}

	// get the stored data
	T* Data()
	{
		return mValues;
	}

	const T* Data() const
	{
		return mValues;
	}

	// operator overload []
	T& operator[](std::size_t index)
	{
		// can throw assert if out of range.
		return mValues[index];
	}

	const T& operator[](std::size_t index) const
	{
		return mValues[index];
	}
	
	// iterator definitions
	using Iterator = ContainerIterator<T>;
	using Const_Iterator = ContainerIterator<const T>;
	Iterator Begin() { return Iterator(mValues); }
	Iterator End() { return Iterator(mValues + N); }
	Const_Iterator Begin() const { return Iterator(mValues); }
	Const_Iterator End() const { return Iterator(mValues + N); }


private:
	// T is the type we Declare/
	// point to a section of memory where the array will be.
	T* mValues = nullptr;
};
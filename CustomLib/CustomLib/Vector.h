#pragma once
#include <cstddef>
#include <utility>
#include <cassert>
#include <algorithm>
#include "ContainerIterator.h"

template<typename T>
class Vector
{
public:
	Vector()
		: mValues(nullptr), mCapacity(0), mSize(0)
	{

	}

	~Vector()
	{
		delete[] mValues;
		mValues = nullptr;
		mCapacity = 0;
		mSize = 0;
	}

	// Copy Constructor
	Vector(const Vector& other)
	{
		if (other.mCapacity > 0)
		{
			mValues = new T[other.mCapacity];

			for (std::size_t i = 0; i < other.mSize; ++i)
			{
				mValues[i] = other.mValues[i];
			}
		}

		mCapacity = other.mCapacity;
		mSize = other.mSize;
	}

	// Copy Assignment
	Vector& operator=(const Vector& other)
	{
		if (this == &other)
			return *this;

		delete[] mValues;
		mValues = nullptr;

		if (other.mCapacity > 0)
		{
			mValues = new T[other.mCapacity];

			for (std::size_t i = 0; i < other.mSize; ++i)
			{
				mValues[i] = other.mValues[i];
			}
		}

		mCapacity = other.mCapacity;
		mSize = other.mSize;

		return *this;
	}

	// Move Constructor
	Vector(Vector&& other)
		: mValues(other.mValues),
		mCapacity(other.mCapacity),
		mSize(other.mSize)
	{
		other.mValues = nullptr;
		other.mCapacity = 0;
		other.mSize = 0;
	}

	// Move Assignment
	Vector& operator=(Vector&& other)
	{
		if (this == &other)
			return *this;

		delete[] mValues;

		mValues = other.mValues;
		mCapacity = other.mCapacity;
		mSize = other.mSize;

		other.mValues = nullptr;
		other.mCapacity = 0;
		other.mSize = 0;

		return *this;
	}


	// Reserve - Pre allocate memory
	void Reserve(std::size_t capacity)
	{
		if (capacity > mCapacity)
		{
			T* newValues = new T[capacity];

			for (std::size_t i = 0; i < mSize; ++i)
			{
				newValues[i] = mValues[i];
			}

			delete[] mValues;

			mValues = newValues;
			mCapacity = capacity;
		}
	}


	// Resize
	void Resize(std::size_t size, const T& initialValue = T())
	{
		if (size == mSize)
			return;


		if (size < mSize)
		{
			// Destroy removed elements
			for (std::size_t i = size; i < mSize; ++i)
			{
				mValues[i].~T();
			}
		}
		else
		{
			if (size > mCapacity)
			{
				std::size_t newCapacity = std::max(size, mCapacity * 2);
				Reserve(newCapacity);
			}

			for (std::size_t i = mSize; i < size; ++i)
			{
				mValues[i] = initialValue;
			}
		}

		mSize = size;
	}


	void Clear()
	{
		Resize(0);
	}


	std::size_t Size() const
	{
		return mSize;
	}


	std::size_t Capacity() const
	{
		return mCapacity;
	}


	// Add element
	void PushBack(const T& value)
	{
		if (mSize >= mCapacity)
		{
			std::size_t newCapacity = (mCapacity == 0) ? 10 : mCapacity * 2;
			Reserve(newCapacity);
		}

		mValues[mSize] = value;
		++mSize;
	}


	// Remove last element
	void PopBack()
	{
		assert(mSize > 0 && "No elements in the vector");

		--mSize;
		mValues[mSize].~T();
	}

	void PopFront()
	{
		// swap the front index all the way to the back and pop it.
		mValues[0].~T();
		for (std::size_t i = 0; i < mSize - 1; ++i)
		{

			mValues[i] = mValues[i + 1];

		}
		PopBack();
	}

	T& operator[](std::size_t index)
	{
		assert(index < mSize && "Index out of range");
		return mValues[index];
	}


	const T& operator[](std::size_t index) const
	{
		assert(index < mSize && "Index out of range");

		return mValues[index];
	}

	// iterator section
	using Iterator = ContainerIterator<T>;
	using Const_Iterator = ContainerIterator<const T>;
	Iterator Begin() { return Iterator(mValues); }
	Iterator End() { return Iterator(mValues + mSize); }
	Const_Iterator Begin() const { return Iterator(mValues); }
	Const_Iterator End() const { return Iterator(mValues + mSize); }

private:

	T* mValues = nullptr;
	std::size_t mCapacity = 0; // allocated memory
	std::size_t mSize = 0;     // number of elements
};
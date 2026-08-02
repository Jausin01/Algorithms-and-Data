#pragma once

#include "Vector.h"

template<typename T>
class Queue
{
public:
	void Enqueue(const T& value)
	{
		mValues.PushBack(value);
	}
	
	void Dequeue()
	{
		assert(!Empty(), "ERROR! Trying to dequeue an empty dequeue!");
		mValues.PopFront();
	}

	const T& Front() const
	{
		assert(!Empty(), "ERROR! Trying to view the front of an empty dequeue");
		return mValues[0];
	}

	std::size_t Size() const
	{
		return mValues.Size();
	}

	bool Empty() const
	{
		return mValues.Size() == 0;
	}


private:
	Vector<T> mValues;

};


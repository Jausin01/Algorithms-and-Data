#pragma once

/* gives accesibility to iterator functions
can be tied into and used with std::sorting functions (std::sort, priorityqueue)
iterate over containers insted of indexing through them
*/

#include <algorithm>
#include <iterator>
#include <cstddef>

template<typename T>
class ContainerIterator
{
public:
	// Defines ids/names for stl use (std::sort, std::find, std::find_if
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = T*;
	using reference = T&;
	
	ContainerIterator(T* ptr) : mPtr(ptr){}
	T& operator*() const { return *mPtr; }
	T* operator->() const { return mPtr; }

	// ++iter
	ContainerIterator& operator++() { ++mPtr; return *this; }
	// --iter
	ContainerIterator& operator--() { --mPtr; return *this; }
	// iter++
	ContainerIterator operator++(int) { ContainerIterator tmp = *this; ++(*this); return tmp; }
	// iter--
	ContainerIterator operator--(int) { ContainerIterator tmp = *this; --(*this); return tmp; }

	// (+ and -) doesnt modify the object
	ContainerIterator operator+(difference_type n) const { return ContainerIterator(mPtr + n); }
	ContainerIterator operator-(difference_type n) const { return ContainerIterator(mPtr - n); }

	// (+= and -=) modifies the object
	ContainerIterator& operator+=(difference_type n) { mPtr += n; return *this; }
	ContainerIterator& operator-=(difference_type n) { mPtr -= n; return *this; }

	difference_type operator-(const ContainerIterator& rhs) const { return mPtr - rhs.mPtr; }

	// comparison
	bool operator==(const ContainerIterator& rhs) const { return mPtr == rhs.mPtr; }
	bool operator!=(const ContainerIterator& rhs) const { return mPtr != rhs.mPtr; }
	bool operator<(const ContainerIterator& rhs) const { return mPtr < rhs.mPtr; }
	bool operator>(const ContainerIterator& rhs) const { return mPtr > rhs.mPtr; }
	bool operator<=(const ContainerIterator& rhs) const { return mPtr <= rhs.mPtr; }
	bool operator>=(const ContainerIterator& rhs) const { return mPtr >= rhs.mPtr; }

private:
	T* mPtr = nullptr;

};
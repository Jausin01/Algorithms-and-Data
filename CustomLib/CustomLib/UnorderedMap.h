#pragma once

#include <algorithm>
#include <functional>
#include "Vector.h"
#include "Global.h"

template<typename KeyType, typename ValueType>
class UnorderedMap
{
private:
	struct KeyValuePair
	{
		KeyType key;
		ValueType value;
	};

public:
	UnorderedMap(std::size_t initialBucketSize = 8, double loadFactor = 0.8)
		:mLoadFactorThreashold(loadFactor), mCount(0)
	{
		mBucketCount = std::max<std::size_t>(initialBucketSize, 1);
		mTable.Resize(mBucketCount);
	}
	// delete copy/moves
	// prevent duplicating or losing content
	UnorderedMap(const UnorderedMap&) = delete;
	UnorderedMap(UnorderedMap&&) = delete;
	UnorderedMap& operator=(const UnorderedMap&) = delete;
	UnorderedMap& operator=(UnorderedMap&&) = delete;

	void Insert(const KeyType& key, const ValueType& value)
	{
		std::size_t index = GetTableIndex(key);
		// check if something is there
		Vector<KeyValuePair*>& bucket = mTable[index];
		for (std::size_t i = 0; i < bucket.Size(); ++i)
		{	
			if (bucket[i]->key == key)
			{
				// if we already added, update the value and return
				bucket[i]->value = value;
				return;
			}
			
		}

		// otherwise add the new keyvalue pair
		KeyValuePair* kv = new KeyValuePair();
		kv->key = key;
		kv->value = value;
		mTable[index].PushBack(kv);
		++mCount;

		if ((double)mCount / (double)mBucketCount > mLoadFactorThreashold)
		{
			// if too many items, very possible too many collisions, resize and rehas index locations
			ReHash();
		}
	}

	//			
	bool Find(const KeyType& key, ValueType& outValue) const
	{
		std::size_t index = GetTableIndex(key);
		Vector<KeyValuePair*> bucket = mTable[index];
		for (std::size_t i = 0; i < bucket.Size(); ++i)
		{
			if (bucket[i]->key == key)
			{
				outValue = bucket[i]->value;
				return true;
			}
		}
		return false;
	}

	bool Has(const KeyType& key) const
	{
		std::size_t index = GetTableIndex(key);
		const Vector<KeyValuePair*>& bucket = mTable[index];
		for (std::size_t i = 0; i < bucket.Size(); ++i)
		{
			if (bucket[i]->key == key)
			{
				return true;
			}
		}
		return false;
	}

	bool Remove(const KeyType& key)
	{
		std::size_t index = GetTableIndex(key);
		Vector<KeyValuePair*>& bucket = mTable[index];
		for (std::size_t i = 0; i < bucket.Size(); ++i)
		{
			if (bucket[i]->key == key)
			{
				KeyValuePair* tmp = bucket[i];
				bucket[i] = bucket[bucket.Size() - 1];
				bucket[bucket.Size() - 1] = tmp;
				// delete the data
				delete tmp;
				tmp = nullptr;
				// pop off the bucket
				bucket.PopBack();
				return true;
			}
		}
		return false;
	}

	std::size_t Count() const
	{
		return mCount;
	}

	void Clear()
	{
		for (std::size_t t = 0; t < mTable.Size(); ++t)
		{
			Vector<KeyValuePair*>& bucket = mTable[t];
			for (std::size_t b = 0; b < bucket.Size(); ++b)
			{
				delete bucket[b];
				bucket[b] = nullptr;
			}
			bucket.Clear();
		}
		mCount = 0;
	}

	ValueType& operator[](const KeyType& key)
	{
		if (!Has(key))
		{
			// I don't have it, so insert and find again
			Insert(key, mDefault);
		}

		std::size_t index = GetTableIndex(key);
		Vector<KeyValuePair*>& bucket = mTable[index];
		for (std::size_t i = 0; i < bucket.Size(); ++i)
		{
			if (bucket[i]->key == key)
			{
				return bucket[i]->value;
			}
		}
		
		assert(false, "UnorderedMap: Key never Gets Added");
		return mDefault;


	}

	const ValueType& operator[](const KeyType& key) const
	{
		std::size_t index = GetTableIndex(key);
		const Vector<KeyValuePair*>& bucket = mTable[index];
		for (std::size_t i = 0; i < bucket.Size(); ++i)
		{
			if (bucket[i]->key == key)
			{
				return bucket[i]->value;
			}
		}
		return mDefault;
	}

private:
	std::size_t GetTableIndex(const KeyType& key) const
	{
		// if there is a resize, need to remove and re add all elements
		// the table index will change because the mbucketCount will increase
		return mHashFunction(key) % mBucketCount;
	}

	void ReHash()
	{
		// remove all items and add in  the updated table indices
		std::size_t newBucketCount = mBucketCount * 2;
		Vector<Vector<KeyValuePair*>> newTable;
		newTable.Resize(newBucketCount);

		mBucketCount = newBucketCount;
		for (std::size_t t = 0; t < mTable.Size(); ++t)
		{
			Vector<KeyValuePair*>& bucket = mTable[t];
			for (std::size_t b = 0; b < bucket.Size(); ++b)
			{
				std::size_t index = GetTableIndex(bucket[b]->key);
				newTable[index].PushBack(bucket[b]);
			}
			bucket.Clear();
		}
		mTable = std::move(newTable);
		newTable.Clear();
	}


	ValueType mDefault; // used if something can't be found
	// Table is the main vector, bucket is the vector of objects using the same index
	Vector<Vector<KeyValuePair*>> mTable;
	// max indices the table can use to store individual values
	std::size_t mBucketCount = 0;
	std::size_t mCount = 0;
	// how many items in the bucket before we need to resize the table
	double mLoadFactorThreashold = 1.0;
	// stl version of hashFunction to allow any type of key value to be hashed
	std::hash<KeyType> mHashFunction;
	
};
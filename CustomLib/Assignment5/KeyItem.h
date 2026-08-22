#pragma once
#include <string>
#include <iostream>
#include "Map.h"

class KeyItem
{
public:
	void Initialize(std::string name, int count = 0)
	{
		mName = name;
		mCount = count;
	}

	void Add(int amount)
	{
		mCount += amount;
	}

	void Consume(int amount)
	{
		mCount -= amount;
	}

	int GetCount()
	{
		return mCount;
	}

	void Print()
	{
		std::cout << mName << ": " << mCount << "\n";
	}

private:

	std::string mName;
	int mCount = 0;

};
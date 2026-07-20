#pragma once
#include "Vector.h"
#include "Array.h"
#include "PriorityQueue.h"
#include "Item.h"

class Inventory
{
public:
	Inventory()
	{
		
		for (int i = 0; i < 20; ++i)
		{
			int value = rand() % 15 - 7;
			value = value == 0 ? 1 : value;
			mInventory.PushBack(Item((ItemType)i, value));
		}
	}

	void Initialize()
	{
		for (int i = 0; i < 100; ++i)
		{
			AddItem((ItemType)(rand() % 20));
		}
	}

	void AddItem(ItemType type)
	{
		for (int i = 0; i < mInventory.Size(); ++i)
		{
			if (mInventory[i].GetType() == type)
			{
				mInventory[i].AddItem();
			}
		}
	}

	void DisplayInventory()
	{
		PririotyQueue<Item, Item::CompareCount> queueInventory;
		
		for (Vector<Item>::Iterator it = mInventory.Begin(); it != mInventory.End(); ++it)
		{
			queueInventory.Push((*it));
		}

		std::string buffName = "";
		std::cout << "\n======= Inventory =======\n";
		while (!queueInventory.Empty())
		{
			buffName = queueInventory.Top().GetValue() > 0 ? "buff" : "debuff";

			std::cout << "Name: " << queueInventory.Top().GetName() << " | Amount: " << queueInventory.Top().GetAmount() << " " << buffName << " " << queueInventory.Top().GetValue() << "\n";
			queueInventory.Pop();
		}

	}

private:
	Vector<Item> mInventory;
};
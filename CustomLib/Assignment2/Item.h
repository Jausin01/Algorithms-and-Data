#pragma once
#include <string>

enum class ItemType
{
	SmallPotion,
	MediumPotion,
	LargePotion,
	HealthCrystal,
	ManaCrystal,
	Sword,
	Shild,
	Helmet,
	Chestplate,
	Leggings,
	Boot,
	ShoulderPads,
	Axe,
	Bow,
	Arrow,
	Amulet,
	Ring,
	Glove,
	Earring,
	Necklace,
	Coat
};

class Item
{
public:
	Item(ItemType itemType, int value)
		: mType(itemType), mValue(value)
	{
		mName = ItemTypeToString(itemType);
		mCount = 1;
	}
	Item()
	{

	}

	std::string ItemTypeToString(ItemType type)
	{
		switch (type)
		{
		case ItemType::SmallPotion:   return "Small Potion";
		case ItemType::MediumPotion:  return "Medium Potion";
		case ItemType::LargePotion:   return "Large Potion";
		case ItemType::HealthCrystal: return "Health Crystal";
		case ItemType::ManaCrystal:   return "Mana Crystal";
		case ItemType::Sword:         return "Sword";
		case ItemType::Shild:         return "Shild";
		case ItemType::Helmet:        return "Helmet";
		case ItemType::Chestplate:    return "Chestplate";
		case ItemType::Leggings:      return "Leggings";
		case ItemType::Boot:          return "Boot";
		case ItemType::ShoulderPads:  return "Shoulder Pads";
		case ItemType::Axe:           return "Axe";
		case ItemType::Bow:           return "Bow";
		case ItemType::Arrow:         return "Arrow";
		case ItemType::Amulet:        return "Amulet";
		case ItemType::Ring:          return "Ring";
		case ItemType::Glove:         return "Glove";
		case ItemType::Earring:       return "Earring";
		case ItemType::Necklace:      return "Necklace";
		case ItemType::Coat:          return "Coat";
		}

		return "Unknown";
	}

	void ConsumeItem()
	{
		if (mCount > 0)
		{
			mCount--;
			std::cout << mName << " was used!" << " | " << mValue << " value!\n";
		}
		else
		{
			std::cout << "You don't have it on your inventory to use it!\n";
		}
	};

	void AddItem()
	{
		mCount++;
		std::cout << mName << " was added to the inventory!\nCurrent amount of " << mName << ": " << mCount << "\n";
	
	};

	ItemType GetType() const
	{
		return mType;
	}

	std::string GetName() const
	{
		return mName;
	}

	int GetAmount() const
	{
		return mCount;
	}

	int GetValue() const
	{
		return mValue;
	}

	struct CompareCount
	{
		bool operator()(const Item& a, const Item& b)
		{
			return a.mCount < b.mCount;
		};
	};

private:
	ItemType mType;
	std::string mName;
	int mValue;
	int mCount;
};
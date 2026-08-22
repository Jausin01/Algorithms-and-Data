#pragma once
#include "KeyItem.h"

int openedDoors = 0;
int failedDoors = 0;


class Inventory
{
public:
    static Inventory& GetInstance()
    {
        static Inventory instance;
        return instance;
    }

    Inventory(const Inventory&) = delete;
    Inventory& operator=(const Inventory&) = delete;

    void PickupKey(const std::string& keyName, int amount)
    {

        if (!mKeys.Has(keyName))
        {
            KeyItem newItem;
            newItem.Initialize(keyName);
            newItem.Add(amount);
            mKeys.Insert(keyName, newItem);
        }
        else
        {
            mKeys[keyName].Add(amount);
        }
        std::cout << "You got a " << keyName << " now you have: " << mKeys[keyName].GetCount() << "\n";
        
    }

    void UseKey(const std::string& keyName, int amount)
    {
        if (mKeys.Has(keyName))
        {
            mKeys[keyName].Consume(amount);
            std::cout << "You had this key!\n";
            if (mKeys[keyName].GetCount() <= 0)
            {
                mKeys.Remove(keyName);
                std::cout << "You used your last " << keyName << "\n";
            }
            openedDoors++;
        }
        else
        {
            std::cout << "'You stare at the door without the key needed. Frustrated you go back\n";
            failedDoors++;
        }

    }

    void PrintInventory()
    {
        Vector<std::string> keys;
        mKeys.ObtainKeys(keys);
        for (int i = 0; i < keys.Size(); ++i)
        {
            mKeys[keys[i]].Print();
        }
    }

private:
    Inventory() = default;
    ~Inventory() = default;
    Map<std::string, KeyItem> mKeys;
};
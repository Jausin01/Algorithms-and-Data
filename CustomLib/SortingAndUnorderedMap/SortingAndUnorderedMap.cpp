#include <iostream>
#include "Global.h"
#include <UnorderedMap.h>

void Exercise1SortCheck()
{
    Vector<int> numbersBubble;
    Vector<int> NumbersSelection;
    for (int i = 0; i < 10; ++i)
    {
        int value = rand() % 200 + 1;
        numbersBubble.PushBack(value);
        NumbersSelection.PushBack(value);
        std::cout << value << " ";
    }

    std::cout << "\n";
    auto oddEvenSort = [](const int& a, const int& b)->bool
    {
       bool aIsOdd = a % 2 == 1;
       bool bIsOdd = b % 2 == 1;
       if (aIsOdd == bIsOdd)
       {
           return a < b;
       }
       if (aIsOdd)
       {
           return true;
       }
       return false;
          
    };
    Global::BubbleSort(numbersBubble, oddEvenSort);
    Global::SelectionSort(NumbersSelection, oddEvenSort);

    std::cout << "Bubble Sort:\n";
    for (int i = 0; i < numbersBubble.Size(); ++i)
    {
        std::cout << numbersBubble[i] << " ";
    }

    std::cout << "\n";
    std::cout << "Selection Sort:\n";
    for (int i = 0; i < NumbersSelection.Size(); ++i)
    {
        std::cout << NumbersSelection[i] << " ";
    }
    std::cout << "\n";
}

void Exercise2CheckUnorderedMap()
{
    UnorderedMap<std::size_t, int> mapTest;
    for (std::size_t i = 1; i <= 20; ++i)
    {
        mapTest.Insert(i, rand() % 1000);
    }

    std::cout << "Unordered Map:\n";
    for (std::size_t i = 1; i <= 20; ++i)
    {
        std::cout << mapTest[i] << " ";
    }
    std::cout << "\n";
    std::cout << "Map Has Key 30: " << mapTest.Has(30) << "\n";
    int outValue = 0;
    if (mapTest.Find(15, outValue))
    {
        std::cout << "Map has Key 15: " << outValue << "\n";
    }
    else
    {
        std::cout << "Map does not have Key 15!\n";
    }

    if (mapTest.Remove(15))
    {
        std::cout << "Map removed Key 10\n";
    }
    else
    {
        std::cout << "Map failed to remove key 10\n";
    }

    mapTest[35] = 2;
    std::cout << "Map Value 35: " << mapTest[35] << "\n";
    std::cout << "Map Value 40: " << mapTest[40] << "\n";
    mapTest.Clear();
        
}

void Exercise3UnorderedMapString()
{
    std::cout << "Unordered Map with String Keys:\n";
    UnorderedMap<std::string, int> myCarPrices;
    myCarPrices.Insert("Ford", 50);
    myCarPrices.Insert("Honda", 100000);
    myCarPrices.Insert("Dodge", 99990);
    myCarPrices.Insert("Dodge", 7690);
    myCarPrices.Insert("BMW", 14500);
    myCarPrices["Kia"] = 140000;

    std::cout << "Price of a Ford: " << myCarPrices["Ford"] << "\n";
    std::cout << "Price of a Audi: " << myCarPrices["Audi"] << "\n";
}

int main()
{
    Exercise1SortCheck();
    Exercise2CheckUnorderedMap();
}


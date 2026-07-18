// ArraysAndVectors.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Array.h>
#include <Vector.h>
#include <random>

// build an array of 10 ints
// initialize them to 0
// iterate through them all and set the values to random numbers.
// create a new array of 10 int
// make it equal to the initial array
// iterate through all the elements and add  5 (print the numbers)

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 20);
    int randomNumber = dist(gen);



    std::cout << "0s being assigned!\n";
    Array<int, 10> myCustomArray(0);


    for (int i = 0; i < myCustomArray.Size(); ++i)
    {
        std::cout << myCustomArray[i] << " ";
    }
    std::cout << "\nAll Values Assigned\n";

    for (int i = 0; i < myCustomArray.Size(); ++i)
    {
        myCustomArray[i] = randomNumber;
        randomNumber = dist(gen);
    }
    for (int i = 0; i < myCustomArray.Size(); ++i)
    {
        std::cout << myCustomArray[i] << " ";
    }
    std::cout << "\nAll Values Assigned to the second array + 5\n";
    Array<int, 10> myCustomArray2;
    myCustomArray2 = myCustomArray;

    for (int i = 0; i < myCustomArray2.Size(); ++i)
    {
        std::cout << myCustomArray2[i] + 5 << " ";
    }

    // VECTOR
        
    Vector<int> myVector;
    myVector.PushBack(10);
    


}


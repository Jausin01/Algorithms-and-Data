#include <iostream>
#include "Inventory.h"
#include "Vector.h"

int main()
{
    Vector<std::string> keyNames;
    keyNames.PushBack("Spade Key");              
    keyNames.PushBack("Sword Key");              
    keyNames.PushBack("Shield Key");             
    keyNames.PushBack("Armor Key");              
    keyNames.PushBack("Crow Key");               
    keyNames.PushBack("Crank");                  
    keyNames.PushBack("Basement Key");           
    keyNames.PushBack("Antique Shop Key");       
    keyNames.PushBack("Small Key");              
    keyNames.PushBack("Big Key");                
    keyNames.PushBack("Boss Key");               
    keyNames.PushBack("Skeleton Key");           
    keyNames.PushBack("Golden Key");             
    keyNames.PushBack("Red Keycard");            
    keyNames.PushBack("Blue Keycard");           
    keyNames.PushBack("Yellow Keycard");         
    keyNames.PushBack("Graveyard Key");          
    keyNames.PushBack("Clock Key");              
    keyNames.PushBack("Mysterious Key");         
    keyNames.PushBack("Key to the City");        

    for (int i = 0; i < 100; ++i)
    {
        Inventory::GetInstance().PickupKey(keyNames[rand() % 20], 1);
    }

    Inventory::GetInstance().PrintInventory();

    int option = 0;
    std::cout << "\n\nWelcome to the Dungeon of Fears and Hunger!\n";
    do
    {
        std::cout << "Choose what to do!\n1 - Leave the dungeon\n2 - Open a Door\n3 - Obtain a Key\n4 - Check your Keys\n5 - Clear Messages\n";
        std::cin >> option;

        if (option == 1)
        {
            std::cout << "There is no such thing as escaping from these dungeons the only thing you have left is death.\n";
            Inventory::GetInstance().PrintInventory();
            std::cout << "You opened: " << openedDoors << " doors\n";
            std::cout << "You failed to open: " << failedDoors << " doors\n";
            
        }
        else if (option == 2)
        {
            std::string keyNeeded = keyNames[rand() % keyNames.Size()];
            std::cout << "This door requires a " << keyNeeded << " to open it!\n";
            Inventory::GetInstance().UseKey(keyNeeded, 1);
        }
        else if (option == 3)
        {
            std::string keyObtained = keyNames[rand() % keyNames.Size()];
            Inventory::GetInstance().PickupKey(keyObtained, 1);
        }
        else if (option == 4)
        {
            Inventory::GetInstance().PrintInventory();
        }
        else if (option == 5)
        {
            system("cls");
        }



    } while (option != 1);

}


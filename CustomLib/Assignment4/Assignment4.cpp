#include <iostream>
#include "Entity.h"

int main()
{
    Vector<Entity> myEntities;
    Entity player, player2;
    player.Initialize("ProtagonistTexture.png");
    player2.Initialize("SidekickTexture.png");
    myEntities.PushBack(player);
    myEntities.PushBack(player2);
    

    for (int i = 0; i < 20; ++i)
    {
        Entity enemy;
        enemy.Initialize("DefaultMonster.png");
        myEntities.PushBack(enemy);
    }
    
    for (int i = 0; i < myEntities.Size(); ++i)
    {
        myEntities[i].Update();
    }

    Global::BubbleSort(myEntities, SortByDistance);
    std::cout << "\n\nFirst Render: \n\n";
    for (int i = 0; i < myEntities.Size(); ++i)
    {
        myEntities[i].Render();
    }


    std::cout << "\n\nSecond Render: \n\n";
    for (int i = 0; i < myEntities.Size(); ++i)
    {
        myEntities[i].Update();
    }

    Global::BubbleSort(myEntities, SortByDistance);
    for (int i = 0; i < myEntities.Size(); ++i)
    {
        myEntities[i].Render();
    }

    std::cout << "\n\nThird Render: \n\n";
    for (int i = 0; i < myEntities.Size(); ++i)
    {
        myEntities[i].Update();
    }

    Global::BubbleSort(myEntities, SortByDistance);
    for (int i = 0; i < myEntities.Size(); ++i)
    {
        myEntities[i].Render();
    }

    std::cout << "\n\nFourth Render: \n";
    for (int i = 0; i < myEntities.Size(); ++i)
    {
        myEntities[i].Update();
    }

    Global::BubbleSort(myEntities, SortByDistance);
    for (int i = 0; i < myEntities.Size(); ++i)
    {
        myEntities[i].Render();
    }
}


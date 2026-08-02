#include <iostream>
#include <random>
#include "PickUpManager.h"

void CreateRandomPickUps(PickUpManager& manager, int count, float minCoord = 0.0f, float maxCoord = 500.0f)
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> typeDist(1, (int)PickUpType::SpecialItem);
	std::uniform_real_distribution<float> coordDist(minCoord, maxCoord);

	for (int i = 0; i < count; ++i)
	{
		PickUpType type = (PickUpType)typeDist(rng);
		float x = coordDist(rng);
		float y = coordDist(rng);
		float z = coordDist(rng);
		manager.AddItem(type, Vector3(x, y, z));
	}
}

int main()
{
	std::cout << "PickUp test!\n";

	PickUpManager manager(200);

	Vector3 playerPos(200.0f, 200.0f, 200.0f);

	
	/*
	manager.AddItem(PickUpType::Coins, playerPos + Vector3(5.0f, 0.0f, 0.0f));      
	manager.AddItem(PickUpType::WeaponAmmo, playerPos + Vector3(0.0f, -8.0f, 0.0f));
	manager.AddItem(PickUpType::Health, playerPos + Vector3(30.0f, 0.0f, 0.0f));    
	manager.AddItem(PickUpType::Health, playerPos + Vector3(0.0f, 0.0f, -45.0f));   
	*/

	CreateRandomPickUps(manager, 100);

	std::cout << "\n-- Attract range (10.0f) --\n";
	manager.ObtainPickUpsInRange(playerPos, 10.0f);

	std::cout << "\n-- Health search (50.0f) --\n";
	manager.FindPickUpsInRange(playerPos, 50.0f, PickUpType::Health);

	std::cout << "\n-- Closest Pickup --\n";
	const PickUp* closest = manager.GetClosestPickUp(playerPos);
	if (closest != nullptr)
	{
		std::cout << "Closest pickup: " << closest->GetName()
			<< " at (" << closest->GetPos().x << ", " << closest->GetPos().y << ", " << closest->GetPos().z << ")\n";
	}
	else
	{
		std::cout << "None found.\n";
	}
}
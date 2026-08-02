#include "PickUpManager.h"

PickUpManager::PickUpManager(std::size_t maxPickUps)
{
	pickUps.Resize(maxPickUps); 
}

void PickUpManager::AddItem(PickUpType pickupType, const Vector3& pos)
{
	assert(mCount < pickUps.Size() && "PickUpManager Full");
	pickUps[mCount] = PickUp(pickupType, pos);
	PickUp* stored = &pickUps[mCount];
	pickUpTree.AddItem(stored->GetPos().v.data(), stored);
	++mCount;
	pickUpTree.BuildTree();
}

const PickUp* PickUpManager::GetClosestPickUp(const Vector3& pos)
{
	return (const PickUp*)pickUpTree.FindNearest(pos.v.data());
}

void PickUpManager::ObtainPickUpsInRange(const Vector3& pos, float range)
{
	Vector3 minRange = pos - Vector3(range);
	Vector3 maxRange = pos + Vector3(range);

	Vector<const void*> found;
	FilterByRange filter{ pos, range * range };
	pickUpTree.FindInRange(found, minRange.v.data(), maxRange.v.data(), filter);

	for (auto iter = found.Begin(); iter != found.End(); ++iter)
	{
		const PickUp* pickup = (const PickUp*)(*iter);
		std::cout << "Picked up: " << pickup->GetName()
			<< " at (" << pickup->GetPos().x << ", " << pickup->GetPos().y << ", " << pickup->GetPos().z << ")\n";
	}
}

void PickUpManager::FindPickUpsInRange(const Vector3& pos, float range, PickUpType type)
{
	Vector3 minRange = pos - Vector3(range);
	Vector3 maxRange = pos + Vector3(range);

	Vector<const void*> found;
	FilterByTypeAndRange filter{ type, pos, range * range };
	pickUpTree.FindInRange(found, minRange.v.data(), maxRange.v.data(), filter);

	for (auto iter = found.Begin(); iter != found.End(); ++iter)
	{
		const PickUp* pickup = (const PickUp*)(*iter);
		std::cout << "Health pickup: " << pickup->GetName()
			<< " at (" << pickup->GetPos().x << ", " << pickup->GetPos().y << ", " << pickup->GetPos().z << ")\n";
	}
}

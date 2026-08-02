#pragma once
#include "PickUp.h"
#include "KDTree.h"

class PickUpManager
{
public:
	explicit PickUpManager(std::size_t maxPickUps);
	void AddItem(PickUpType picktype, const Vector3& pos);
	const PickUp* GetClosestPickUp(const Vector3& pos);
	void ObtainPickUpsInRange(const Vector3& pos, float range);
	void FindPickUpsInRange(const Vector3& pos, float range, PickUpType type);
private:
	Vector<PickUp> pickUps;
	std::size_t mCount = 0;
	KDTree<float, 3> pickUpTree;
};
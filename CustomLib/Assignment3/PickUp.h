#pragma once
#include <string>
#include "Vector.h"
#include "Vector2.h"
#include "Vector3.h"

enum class PickUpType
{
	Invalid,
	Health,
	WeaponAmmo,
	Coins,
	Upgrade,
	SpecialItem
};

class PickUp
{
public:
	PickUp() : mType(PickUpType::Invalid), mPos(Vector3()) {}

	PickUp(PickUpType pickupType, const Vector3& pos)
		:mType(pickupType), mPos(pos)
	{
		if (pickupType == PickUpType::Health)
		{
			mName = "Health";
		}
		else if (pickupType == PickUpType::WeaponAmmo)
		{
			mName = "Weapon Ammo";
		}
		else if (pickupType == PickUpType::Coins)
		{
			mName = "Coins";
		}
		else if (pickupType == PickUpType::Upgrade)
		{
			mName = "Upgrade";
		}
		else if (pickupType == PickUpType::SpecialItem)
		{
			mName = "Special Item";
		}
		else 
		{
			mName = "Invalid";
		}
	}

	const Vector3& GetPos() const { return mPos; }
	PickUpType GetType() const { return mType; }
	const std::string& GetName() const { return mName; }




private:
	std::string mName;
	PickUpType mType;
	Vector3 mPos;
};

struct FilterByType
{
	PickUpType itemType;
	bool operator()(const void* data) const
	{
		const PickUp* pickup = (const PickUp*)data;
		return pickup->GetType() == itemType;
	}
};

struct FilterByTypeAndRange
{
	PickUpType itemType;
	Vector3 origin;
	float rangeSqr;
	bool operator()(const void* data) const
	{
		const PickUp* pickup = (const PickUp*)data;
		return pickup->GetType() == itemType && pickup->GetPos().DistanceSqr(origin) <= rangeSqr;
	}
};

struct FilterByRange
{
	Vector3 origin;
	float rangeSqr;
	bool operator()(const void* data) const
	{
		const PickUp* pickup = (const PickUp*)data;
		return pickup->GetPos().DistanceSqr(origin) <= rangeSqr;
	}
};
#pragma once
#include "Player.h"
#include "Vector.h"
#include "Global.h"
#include <iostream>

class Team
{
public:
	void Initialize(int numPlayers, std::string teamName)
	{
		mTeamName = teamName;

		for (int i = 0; i < numPlayers; ++i)
		{
			Player player;

			player.Initialize("Player" + std::to_string(i));

			mPlayers.PushBack(player);
		}
	}

	Player* GetNextBattlingPlayer()
	{
		OrderPlayers();

		for (int i = 0; i < mPlayers.Size(); ++i)
		{
			if (mPlayers[i].IsAlive() && mPlayers[i].GetStat(Stat::AttackCount) == 1)
			{
				return &mPlayers[i];
			}
		}

		return nullptr;
	}

	void DamagePlayer(Player* player)
	{
		Vector<int> livingPlayers;

		for (int i = 0; i < mPlayers.Size(); ++i)
		{
			if (mPlayers[i].IsAlive())
			{
				livingPlayers.PushBack(i);
			}
		}

		int randomLivingIndex = rand() % livingPlayers.Size();
		int targetIndex = livingPlayers[randomLivingIndex];

		Player& target = mPlayers[targetIndex];

		int damage = player->GetStat(Stat::Attack);

		target.SetStat(Stat::Health,target.GetStat(Stat::Health) - damage);

		std::cout << player->GetName() << " attacks " << target.GetName() << " for " << damage << " damage!\n";


		int slowedPossibility = (rand() % 4) + 1;

		if (slowedPossibility == 1)
		{
			int newSpeed = target.GetStat(Stat::Speed) - 10;

			if (newSpeed < 5)
			{
				newSpeed = 5;
			}

			target.SetStat(Stat::Speed, newSpeed);

			std::cout << target.GetName() << " was slowed to " << target.GetStat(Stat::Speed) << " speed!\n";
		}

		int attackerSpeedPossibility = (rand() % 10) + 1;

		if (attackerSpeedPossibility == 1)
		{
			player->SetStat(Stat::Speed,player->GetStat(Stat::Speed) + 5);

			std::cout << player->GetName() << " gained 5 speed!\n";
		}

		player->SetStat(Stat::AttackCount, 0);
	}

	int GetRemainingPlayers()
	{
		int aliveCount = 0;
		for (int i = 0; i < mPlayers.Size(); ++i)
		{
			if (mPlayers[i].IsAlive())
			{
				++aliveCount;
			}
		}

		return aliveCount;
	}

	void OrderPlayers()
	{
		Global::IntroSort(
			mPlayers.Begin(),
			mPlayers.End(),
			SpeedComparator{}
		);
	}

	void StartTurn()
	{
		for (int i = 0; i < mPlayers.Size(); ++i)
		{
			if (mPlayers[i].IsAlive())
			{
				mPlayers[i].SetStat(Stat::AttackCount, 1);
			}
		}

		OrderPlayers();
	}

	bool AllPlayersAttacked()
	{
		for (int i = 0; i < mPlayers.Size(); ++i)
		{
			if (mPlayers[i].IsAlive() &&
				mPlayers[i].GetStat(Stat::AttackCount) == 1)
			{
				return false;
			}
		}

		return true;
	}

	std::string GetTeamName() const
	{
		return mTeamName;
	}

private:
	std::string mTeamName;
	Vector<Player> mPlayers;
};


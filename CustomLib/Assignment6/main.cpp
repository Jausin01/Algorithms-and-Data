#include "Team.h"
#include <iostream>

int main()
{
	srand(time(NULL));
	Team teamA;
	teamA.Initialize(20, "Team Blue");

	Team teamB;
	teamB.Initialize(20, "Team Red");

	while (teamA.GetRemainingPlayers() > 0 && teamB.GetRemainingPlayers() > 0)
	{
		std::cout << "\n========== NEW TURN ==========\n";

		teamA.StartTurn();
		teamB.StartTurn();

		while (teamA.GetRemainingPlayers() > 0 && teamB.GetRemainingPlayers() > 0 && (!teamA.AllPlayersAttacked() || !teamB.AllPlayersAttacked()))
		{
			Player* atkPlayerA = teamA.GetNextBattlingPlayer();
			Player* atkPlayerB = teamB.GetNextBattlingPlayer();

			if (atkPlayerA != nullptr && atkPlayerB != nullptr)
			{
				if (atkPlayerA->GetStat(Stat::Speed) > atkPlayerB->GetStat(Stat::Speed))
				{
					teamB.DamagePlayer(atkPlayerA);
				}
				else
				{
					teamA.DamagePlayer(atkPlayerB);
				}
			}
			else if (atkPlayerA != nullptr)
			{
				teamB.DamagePlayer(atkPlayerA);
			}
			else if (atkPlayerB != nullptr)
			{
				teamA.DamagePlayer(atkPlayerB);
			}

			teamA.OrderPlayers();
			teamB.OrderPlayers();
		}
	}

	std::cout << "\n========== FIGHT OVER ==========\n";

	if (teamA.GetRemainingPlayers() > 0)
	{
		std::cout << teamA.GetTeamName() << " WON!\n";
	}
	else
	{
		std::cout << teamB.GetTeamName() << " WON!\n";
	}

	return 0;
}
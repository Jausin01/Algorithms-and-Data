#include <iostream>
#include <Vector.h>
#include <Array.h>
#include "Player.h"

std::string GenerateRandomName()
{
	Vector<std::string> names;

	names.PushBack("Arthur");
	names.PushBack("Luna");
	names.PushBack("Kael");
	names.PushBack("Evelyn");
	names.PushBack("Cedric");
	names.PushBack("Scarlett");
	names.PushBack("Darius");
	names.PushBack("Sylvia");
	names.PushBack("Rowan");
	names.PushBack("Elena");
	names.PushBack("Magnus");
	names.PushBack("Freya");
	names.PushBack("Orion");
	names.PushBack("Raven");
	names.PushBack("Leon");
	names.PushBack("Selene");
	names.PushBack("Finn");
	names.PushBack("Astra");
	names.PushBack("Victor");
	names.PushBack("Iris");

	names.PushBack("Alden");
	names.PushBack("Bianca");
	names.PushBack("Cyrus");
	names.PushBack("Daphne");
	names.PushBack("Edgar");
	names.PushBack("Fiona");
	names.PushBack("Gareth");
	names.PushBack("Helena");
	names.PushBack("Isaac");
	names.PushBack("Jasmine");
	names.PushBack("Kieran");
	names.PushBack("Lilith");
	names.PushBack("Marcus");
	names.PushBack("Natalia");
	names.PushBack("Oscar");
	names.PushBack("Penelope");
	names.PushBack("Quentin");
	names.PushBack("Rosalind");
	names.PushBack("Sebastian");
	names.PushBack("Valeria");

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<std::size_t> dist(0, names.Size() - 1);

	return names[dist(gen)];
}

void FightWithTwoPlayers(Vector<Player>& players)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<std::size_t> dist(0, players.Size() - 1);
	int randomNumber = dist(gen);

	Player& playerA = players[randomNumber];
	randomNumber = dist(gen);
	Player& playerB = players[randomNumber];

	std::cout << "Fighter's Profiles\n\n";
	playerA.PrintPlayerProfile();
	playerB.PrintPlayerProfile();

	int playerAScore = playerA.GetStat(Stats::Health) - (playerB.GetStat(Stats::Attack) * playerB.GetStat(Stats::Stamina) - (playerA.GetStat(Stats::Defense) * playerA.GetStat(Stats::Speed)));
	int playerBScore = playerB.GetStat(Stats::Health) - (playerA.GetStat(Stats::Attack) * playerA.GetStat(Stats::Stamina) - (playerB.GetStat(Stats::Defense) * playerB.GetStat(Stats::Speed)));
	std::cout << playerA.GetName() << " Scored: " << playerAScore << " against " << playerB.GetName() << "\n";
	std::cout << playerB.GetName() << " Scored: " << playerBScore << " against " << playerA.GetName() << "\n";
	if (playerAScore > playerBScore)
	{
		std::cout << playerA.GetName() << " WINS!\n";
	}
	else if (playerAScore == playerBScore)
	{
		std::uniform_int_distribution<std::size_t> dist2(1, 2);
		int coinFlip = dist(gen);
		if (coinFlip == 1)
		{
			std::cout << "A tie is decided by coin flip! The Winner is.... " << playerA.GetName();
		}
		else
		{
			std::cout << "A tie is decided by coin flip! The Winner is.... " << playerB.GetName();
		}
		
	}
	else
	{
		std::cout << playerB.GetName() << " WINS!\n";
	}

}

int main()
{

    Vector<Player> players;
    for (int i = 0; i < 10; ++i)
    {
		Player newPlayer(GenerateRandomName());
		players.PushBack(newPlayer);
    }

	for (int i = 0; i < 10; ++i)
	{
		players[i].PrintPlayerProfile();
		std::cout << "\n";
	}

	std::cout << "\nTHE HUNGER GAMES START\n";
	for (int i = 0; i < 6; ++i)
	{
		players.PopBack();
	}

	for (int i = 0; i < 16; ++i)
	{
		Player newPlayer(GenerateRandomName());
		players.PushBack(newPlayer);
	}

	int i = 0;
	do
	{
		players[i].PrintPlayerProfile();
		std::cout << "\n"; 
		++i;

	} while (i < 20);

	std::cout << "\n\nTHE FIGHT WILL START!!!\n\n";
	FightWithTwoPlayers(players);
}


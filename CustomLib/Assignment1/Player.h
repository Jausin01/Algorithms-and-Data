#pragma once
#include <string>
#include <Array.h>
#include <random>
#include <iostream>

enum class Stats
{
	Health, 
	Attack, 
	Defense, 
	Stamina, 
	Speed
};

class Player
{
public:
	Player()
	{
		mName = "Unknown";

		mStats[0] = 100;

		for (int i = 1; i < 5; i++)
		{
			mStats[i] = GetRandomValue();
		}
	}

	Player(std::string name)
		:mName(name)
	{
		mStats[0] = 100;
		for (int i = 1; i < 5; i++)
		{
			mStats[i] = GetRandomValue();
		}
	}

	// Helper Function for playerCreation
	int GetRandomValue()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(1, 5);
		int randomNumber = dist(gen);

		return randomNumber;
	}


	void PrintPlayerProfile()
	{
		std::cout << "====== " << mName << " ======\n";
		std::cout << "Health: " << mStats[0] << "\n";
		std::cout << "Attack: " << mStats[1] << "\n";
		std::cout << "Defense: " << mStats[2] << "\n";
		std::cout << "Stamina: " << mStats[3] << "\n";
		std::cout << "Speed: " << mStats[4] << "\n\n";
	}

	std::string GetName()
	{
		return mName;
	}

	int GetStat(Stats stat)
	{
		return mStats[static_cast<int>(stat)];
	}

private:

	std::string mName;
	Array<int, 5> mStats; // ORDER IS ->	Health,Attack,Defense,Stamina,Speed
};

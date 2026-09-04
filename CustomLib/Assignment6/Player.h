#pragma once
#include "string"


enum class Stat
{
	Health,
	Attack,
	Speed,
	AttackCount,
};

class Player
{
public:
	void Initialize(std::string name)
	{
		mStats[0] = 100;
		mStats[1] = (rand() % 16) + 5;
		mStats[2] = (rand() % 81) + 20;
		mStats[3] = 1;
		mName = name;
	}
	
	int GetStat(Stat stat) const
	{
		if (stat == Stat::Health)
		{
			return mStats[0];
		}
		else if (stat == Stat::Attack)
		{
			return mStats[1];
		}
		else if (stat == Stat::Speed)
		{
			return mStats[2];
		}
		else if (stat == Stat::AttackCount)
		{
			return mStats[3];
		}
		else
		{
			return 0;
		}
	}

	void SetStat(Stat stat, int value)
	{
		if (stat == Stat::Health)
		{
			mStats[0] = value;
		}
		else if (stat == Stat::Attack)
		{
			mStats[1] = value;
		}
		else if (stat == Stat::Speed)
		{
			mStats[2] = value;
		}
		else if (stat == Stat::AttackCount)
		{
			mStats[3] = value;
		}
	}

	std::string GetName()
	{
		return mName;
	}

	bool IsAlive() const
	{
		if (mStats[0] > 0)
		{
			return true;
		}

		return false;
	}



private:
	std::string mName;
	int mStats[4];
	
};


struct SpeedComparator
{
	bool operator()(const Player& a, const Player& b) const
	{
		int speedA = a.GetStat(Stat::Speed);
		int speedB = b.GetStat(Stat::Speed);

		if (a.GetStat(Stat::Health) == 0 || a.GetStat(Stat::AttackCount) == 0)
		{
			speedA = 0;
		}

		if (b.GetStat(Stat::Health) == 0 || b.GetStat(Stat::AttackCount) == 0)
		{
			speedB = 0;
		}

		return speedA > speedB;
	}
};
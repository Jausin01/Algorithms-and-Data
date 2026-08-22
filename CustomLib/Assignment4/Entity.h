#pragma once
#include "Vector2.h"
#include <string>
#include "TextureManager.h"


class Entity
{
public:
	void Initialize(const std::string& filePath)
	{
		mTextureId = TextureManager::GetInstance().LoadTexture(filePath);

		int x = rand() % 100 + 1;
		int y = rand() % 100 + 1;
		mPos = { (float)x, (float)y };
	}

	void Update()
	{
		mPos.x = (rand() % 401) - 200;
		mPos.y = (rand() % 401) - 200;

	}

	void Render()
	{
		Texture texture;
		if (TextureManager::GetInstance().GetTexture(mTextureId, texture))
		{
			texture.Print();
			std::cout << "Entity Position: " << mPos.x << "|" << mPos.y << "\n";
		}

	}

	Vector2 GetPosition() const
	{
		return mPos;
	}

private:

	size_t mTextureId;
	Vector2 mPos;
};

auto SortByDistance = [](const Entity& a, const Entity& b) -> bool
	{
		Vector2 posA = a.GetPosition();
		Vector2 posB = b.GetPosition();

		float distanceA = std::abs(posA.x) + std::abs(posA.y);
		float distanceB = std::abs(posB.x) + std::abs(posB.y);

		return distanceA < distanceB;
	};
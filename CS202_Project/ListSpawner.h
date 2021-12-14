#ifndef LISTSPAWNER_H
#define LISTSPAWNER_H

#include "Enemy.h"
#include "GameWorld.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include "Spawner.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

class ListSpawner : public ISaveable
{
private:
	vector<Spawner> listSpawner;

	void deleteUnusedSpawners(int viewY)
	{
		for (auto spawner = listSpawner.begin(); spawner != listSpawner.end(); spawner++)
		{
			if (spawner->getPosition().y + 20 > viewY)
			{
				spawner->deleteAllEnemies();
				listSpawner.erase(spawner);
			}
		}
	}

public:
	ListSpawner()
	{}

	void setup(vector<pair<string, int>> spawnInfo)
	{
		string animals[] = { "Dinosaur", "Bird" };
		string vehicles[] = { "Truck", "Car" };

		for (int i = spawnInfo.size() - 1; i >= 0; i -= TILES_PER_LANE)
		{
			bool moveToLeft = rand() % 2 > 0;
			float timeToSpawn = rand() % 3 + 3;
			Vector2f position = moveToLeft ? Vector2f(GAME_WIDTH, spawnInfo[i].second - 64) : Vector2f(0, spawnInfo[i].second - 64);

			if (spawnInfo[i].first == "Road")
			{
				int vehicle = rand() % 2;
				listSpawner.push_back(Spawner(timeToSpawn, position, vehicles[vehicle], moveToLeft));
			}
			else if (spawnInfo[i].first == "Rock")
			{
				int animal = rand() % 2;
				listSpawner.push_back(Spawner(timeToSpawn, position, animals[animal], moveToLeft));
			}
		}
	}

	void draw(RenderWindow& window, Player& mainPlayer, int cameraYPosition)
	{
		cameraYPosition += 368;
		const float playerYPosition = mainPlayer.getBody().getPosition().y;
		for (auto spawner = listSpawner.begin(); spawner != listSpawner.end(); spawner++)
			if (spawner->getPosition().y <= cameraYPosition && spawner->getPosition().y >= playerYPosition - SCREEN_HEIGHT)
				spawner->draw(window);
			else
				break;
	}

	void update(float deltaTime, Player& mainPlayer, int cameraYPosition)
	{
		cameraYPosition += 368;
		const float playerYPosition = mainPlayer.getBody().getPosition().y;
		for (auto spawner = listSpawner.begin(); spawner != listSpawner.end(); spawner++)
		{
			if (spawner->getPosition().y <= cameraYPosition && spawner->getPosition().y >= playerYPosition - SCREEN_HEIGHT)
				spawner->update(deltaTime);
			else
				break;
		}

		deleteUnusedSpawners(cameraYPosition);
	}

	bool isCollidedWithPlayer(Player& mainPlayer)
	{
		const FloatRect playerBounds = mainPlayer.getBody().getGlobalBounds();
		const float playerYPosition = mainPlayer.getBody().getPosition().y;
		for (auto spawner = listSpawner.begin(); spawner != listSpawner.end(); spawner++)
			if (spawner->getPosition().y >= playerYPosition - SCREEN_HEIGHT)
			{
				if (spawner->isCollidedWithPlayer(playerBounds))
					return true;
			}
			else
				return false;
		return false;
	}

	void save(ostream& out)
	{
		out << 1;
	}

	void load(istream& in)
	{
		int x;
		in >> x;
	}
};
#endif
#ifndef LISTSPAWNER_H
#define LISTSPAWNER_H

#include "Enemy.h"
#include "GameWorld.h"
#include "MovingObject.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include "Spawner.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

class ListSpawner
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
	ListSpawner(vector<pair<int, int>> pos)
	{
		int randDirect = 0;
		int randAnimal = 0;
		int randVehicle = 0;
		int randTime = 0;
		for (int i = pos.size() - 1; i >= 0; i -= 4)
		{
			randDirect = rand() % 2;
			randAnimal = rand() % 2;
			randVehicle = rand() % 2;
			randTime = 2;
			if (pos[i].first == 1)
			{
				continue;
			}
			else if (pos[i].first == 2)
			{
				if (randVehicle == 0 && randDirect == 0)
				{
					listSpawner.push_back(Spawner(randTime, Vector2f(0, pos[i].second - 64), "Car", randDirect));
				}
				else if (randVehicle == 0 && randDirect == 1)
				{
					listSpawner.push_back(Spawner(randTime, Vector2f(GAME_WIDTH, pos[i].second - 64), "Car", randDirect));
				}
				else if (randVehicle == 1 && randDirect == 0)
				{
					listSpawner.push_back(Spawner(randTime, Vector2f(0, pos[i].second - 96), "Truck", randDirect));
				}
				else if (randVehicle == 1 && randDirect == 1)
				{
					listSpawner.push_back(Spawner(randTime, Vector2f(GAME_WIDTH, pos[i].second - 96), "Truck", randDirect));
				}
			}
			else if (pos[i].first == 3)
			{
				if (randAnimal == 0 && randDirect == 0)
				{
					listSpawner.push_back(Spawner(randTime, Vector2f(0, pos[i].second - 32), "Bird", randDirect));
				}
				else if (randAnimal == 0 && randDirect == 1)
				{
					listSpawner.push_back(Spawner(randTime, Vector2f(GAME_WIDTH, pos[i].second - 32), "Bird", randDirect));
				}
				else if (randAnimal == 1 && randDirect == 0)
				{
					listSpawner.push_back(Spawner(randTime, Vector2f(0, pos[i].second - 64), "Dinosaur", randDirect));
				}
				else if (randAnimal == 1 && randDirect == 1)
				{
					listSpawner.push_back(Spawner(randTime, Vector2f(GAME_WIDTH, pos[i].second - 64), "Dinosaur", randDirect));
				}
			}
		}
	}

	void draw(RenderWindow& window, Player& mainPlayer, int cameraYPosition)
	{
		cameraYPosition += 368;
		const float playerYPosition = mainPlayer.getBody().getPosition().y;
		for (auto spawner = listSpawner.begin(); spawner != listSpawner.end(); spawner++)
			if (spawner->getPosition().y <= cameraYPosition && spawner->getPosition().y >= playerYPosition - HEIGHT)
				spawner->draw(window);
			else
				break;
	}

	void update(float deltaTime, Player& mainPlayer, int cameraYPosition)
	{
		cameraYPosition += 368;
		const float playerYPosition = mainPlayer.getBody().getPosition().y;
		for (auto i = listSpawner.begin(); i != listSpawner.end(); i++)
		{
			if (i->getPosition().y <= cameraYPosition && i->getPosition().y >= playerYPosition - HEIGHT)
				i->update(deltaTime);
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
			if (spawner->getPosition().y >= playerYPosition - HEIGHT)
			{
				if (spawner->isCollidedWithPlayer(playerBounds))
					return true;
			}
			else
				return false;
		return false;
	}
};
#endif
#ifndef LISTSPAWNER_H
#define LISTSPAWNER_H
#include "Enemy.h"
#include "GameWorld.h"
#include "MovingObject.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include "Spawner.h"
#include "fstream"
#include "string"
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;
class ListSpawner
{
private:
	vector<Spawner> listSpawner;
	int yDistance = 992;
	void deleteUnusedSpawner(int viewY)
	{
		for (auto i = listSpawner.begin(); i != listSpawner.end(); i++)
		{
			if (i->getPosition().y + 20 > viewY)
			{
				i->deleteAllEnemy();
				listSpawner.erase(i);
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
			randTime = (rand() % 3) + 4;
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
	void draw(RenderWindow &window, Player mainPlayer, int viewY)
	{
		viewY += 368;
		const float yPos = mainPlayer.getBody().getPosition().y;
		for (auto i = listSpawner.begin(); i != listSpawner.end(); i++)
		{
			if (i->getPosition().y <= viewY && i->getPosition().y >= yPos - yDistance)
				i->draw(window);
			else
				break;
		}
	}
	void update(float dt, Player mainPlayer, int viewY)
	{
		viewY += 368;
		const float yPos = mainPlayer.getBody().getPosition().y;
		for (auto i = listSpawner.begin(); i != listSpawner.end(); i++)
		{
			if (i->getPosition().y <= viewY && i->getPosition().y >= yPos - yDistance)
				i->update(dt);
			else
				break;
		}
		deleteUnusedSpawner(viewY);
	}

	bool UpdateCollsion(Player mainPlayer)
	{
		const FloatRect playerBounds = mainPlayer.getBody().getGlobalBounds();
		const float yPos = mainPlayer.getBody().getPosition().y;
		for (auto spawner = listSpawner.begin(); spawner != listSpawner.end(); spawner++)
		{
			if (spawner->getPosition().y >= yPos - yDistance)
			{
				if (spawner->UpdateCollsion(playerBounds))
					return true;
			}
			else
				break;
		}
		return false;
	}
};
#endif
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
		for (int spawner = 0; spawner < listSpawner.size(); spawner++)
		{
			if (listSpawner[spawner].getPosition().y + 20 > viewY)
			{
				listSpawner[spawner].deleteAllEnemies();
				listSpawner.erase(listSpawner.begin() + spawner);
			}
		}
	}

	void deleteAllSpawners()
	{
		listSpawner.clear();
	}

	string typeIntToString(int type)
	{
		if (type == 0)
			return "Dinosaur";

		if (type == 1)
			return "Bird";

		if (type == 2)
			return "Truck";

		return "Car";
	}

	int typeStringToInt(string type)
	{
		if (type == "Dinosaur")
			return 0;

		if (type == "Bird")
			return 1;

		if (type == "Truck")
			return 2;

		return 3;
	}

public:
	ListSpawner()
	{}

	void setupFromNewGame(vector<float> lanePositionYs)
	{
		string enemies[] = { "Dinosaur", "Bird", "Truck", "Car" };

		for (int i = lanePositionYs.size() - 1; i >= 0; i -= TILES_PER_LANE)
		{
			bool moveToLeft = rand() % 2 > 0;
			float timeToSpawn = rand() % 3 + 3;
			Vector2f position = moveToLeft ? Vector2f(GAME_WIDTH, lanePositionYs[i] - 64) : Vector2f(0, lanePositionYs[i] - 64);

			int enemy = rand() % 4;
			listSpawner.push_back(Spawner(timeToSpawn, position, enemies[enemy], moveToLeft));
		}
	}

	void draw(RenderWindow& window, Player& mainPlayer, int cameraYPosition)
	{
		cameraYPosition += 368;
		const float playerYPosition = mainPlayer.getBody().getPosition().y;
		for (vector<Spawner>::iterator spawner = listSpawner.begin(); spawner != listSpawner.end(); spawner++)
			if (spawner->getPosition().y <= cameraYPosition && spawner->getPosition().y >= playerYPosition - SCREEN_HEIGHT)
				spawner->draw(window);
			else
				break;
	}

	void update(float deltaTime, Player& mainPlayer, int cameraYPosition)
	{
		cameraYPosition += 368;
		const float playerYPosition = mainPlayer.getBody().getPosition().y;
		for (int spawner = 0; spawner < listSpawner.size(); ++spawner)
		{	
			
			if (listSpawner[spawner].getPosition().y <= cameraYPosition && listSpawner[spawner].getPosition().y >= playerYPosition - SCREEN_HEIGHT) {
				listSpawner[spawner].update(deltaTime);
			}
			else {
				break;
			}
			
		}
		deleteUnusedSpawners(cameraYPosition);
	}

	bool isCollidedWithPlayer(Player& mainPlayer)
	{
		const FloatRect playerBounds = mainPlayer.getBody().getGlobalBounds();
		const float playerYPosition = mainPlayer.getBody().getPosition().y;
		for (vector<Spawner>::iterator spawner = listSpawner.begin(); spawner != listSpawner.end(); spawner++)
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
		int listSpawnerSize = listSpawner.size();
		out.write((char*)&listSpawnerSize, sizeof(listSpawnerSize));

		for (vector<Spawner>::iterator spawner = listSpawner.begin(); spawner != listSpawner.end(); spawner++)
		{
			float timeToSpawn = spawner->getTimeToSpawn();
			out.write((char*)&timeToSpawn, sizeof(timeToSpawn));

			Vector2f position = spawner->getPosition();
			out.write((char*)&position, sizeof(position));

			int type = typeStringToInt(spawner->getType());
			out.write((char*)&type, sizeof(type));

			bool moveToLeft = spawner->isMoveToLeft();
			out.write((char*)&moveToLeft, sizeof(moveToLeft));
		}
	}

	void load(istream& in)
	{
		deleteAllSpawners();

		int listSpawnerSize = listSpawner.size();
		in.read((char*)&listSpawnerSize, sizeof(listSpawnerSize));

		for (int i = 0; i < listSpawnerSize; ++i)
		{
			float timeToSpawn;
			in.read((char*)&timeToSpawn, sizeof(timeToSpawn));

			Vector2f position;
			in.read((char*)&position, sizeof(position));

			int type;
			in.read((char*)&type, sizeof(type));

			bool moveToLeft;
			in.read((char*)&moveToLeft, sizeof(moveToLeft));

			listSpawner.push_back(Spawner(timeToSpawn, position, typeIntToString(type), moveToLeft));
		}
	}
};
#endif
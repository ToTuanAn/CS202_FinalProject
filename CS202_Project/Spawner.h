#ifndef SPAWNER_H
#define SPAWNER_H

#include "Enemy.h"
#include "GameWorld.h"
#include "IObject.h"
#include "ISaveable.h"
#include "SFML/Graphics.hpp"
#include "TrafficLight.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

class Spawner : public IObject
{
private:
	bool moveToLeft;
	float timeFromLastSpawn, timeToSpawn;
	Vector2f position;
	string type;
	vector<Enemy*> listEnemy;
	TrafficLight* trafficLight;

	void updateEnemies(float deltaTime)
	{
		for (vector<Enemy*>::iterator enemy = listEnemy.begin(); enemy != listEnemy.end(); enemy++)
		{
			(*enemy)->update(deltaTime);
		}
	}

	void addEnemy(float deltaTime)
	{
		if (timeFromLastSpawn >= timeToSpawn)
		{
			Enemy* e = new Enemy(type, position, moveToLeft);
			listEnemy.push_back(e);
			timeFromLastSpawn = 0;
		}

		timeFromLastSpawn += deltaTime;
	}

	void deleteUnusedEnemies()
	{
		if ((int)listEnemy.size() == 0)
			return;

		std::vector<Enemy*>::iterator enemy = listEnemy.begin();
		if ((*enemy)->getBody().getPosition().x > (float)GAME_WIDTH)
		{
			delete (*enemy);
			listEnemy.erase(enemy);
		}
	}

public:
	Spawner(float timeToSpawn, Vector2f position, string type, bool moveToLeft)
	{
		this->moveToLeft = moveToLeft;
		this->timeToSpawn = timeToSpawn;
		this->position = position;
		this->type = type;

		timeFromLastSpawn = timeToSpawn;
		trafficLight = new TrafficLight(Vector2f(GAME_WIDTH / 2, position.y));
	}

	~Spawner()
	{
		deleteAllEnemies();
	}

	void deleteAllEnemies()
	{
		if ((int)listEnemy.size() == 0)
			return;

		for (vector<Enemy*>::iterator enemy = listEnemy.begin(); enemy != listEnemy.end(); enemy++)
			if ((*enemy)->getBody().getPosition().x > (float)GAME_WIDTH)
			{
				delete (*enemy);
				listEnemy.erase(enemy);
			}
	}

	void draw(RenderWindow& window)
	{
		for (vector<Enemy*>::iterator enemy = listEnemy.begin(); enemy != listEnemy.end(); enemy++)
		{
			if ((*enemy)->getType() == "Truck" || (*enemy)->getType() == "Car")
				window.draw(trafficLight->getModel());

			window.draw((*enemy)->getModel());
		}
	}

	float update(float deltaTime)
	{

		if (trafficLight->getType() == "Red" && (this->type == "Car" || this->type == "Truck"))
		{
			trafficLight->update(deltaTime);
			return deltaTime;
		}

		addEnemy(deltaTime);
		updateEnemies(deltaTime);

		trafficLight->update(deltaTime);

		deleteUnusedEnemies();

		return deltaTime;
	}

	bool isCollidedWithPlayer(FloatRect const playerBounds)
	{
		for (vector<Enemy*>::iterator enemy = listEnemy.begin(); enemy != listEnemy.end(); enemy++)
		{
			FloatRect enemyBounds = (*enemy)->getBody().getGlobalBounds();
			if (enemyBounds.intersects(playerBounds))
				return true;
		}

		return false;
	}

	bool isMoveToLeft()
	{
		return moveToLeft;
	}

	float getTimeToSpawn()
	{
		return timeToSpawn;
	}

	Vector2f getPosition()
	{
		return position;
	}

	string getType()
	{
		return type;
	}
};
#endif
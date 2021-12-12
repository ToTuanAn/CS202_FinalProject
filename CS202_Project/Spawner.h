#ifndef SPAWNER_H
#define SPAWNER_H

#include "Enemy.h"
#include "GameWorld.h"
#include "IObject.h"
#include "ISaveable.h"
#include "SFML/Graphics.hpp"

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
	float speed, timeFromLastSwitchAnim, timeToSpawn;
	Vector2f position;
	string type;
	vector<Enemy*> listEnemy;

	void updateEnemies(float dt)
	{
		for (auto enemy = listEnemy.begin(); enemy != listEnemy.end(); enemy++)
			(*enemy)->update(dt);
	}

	void addEnemy(float dt)
	{
		if (timeFromLastSwitchAnim >= timeToSpawn)
		{
			Enemy* e = new Enemy(type, position, moveToLeft);
			listEnemy.push_back(e);
			timeFromLastSwitchAnim = 0;
		}

		timeFromLastSwitchAnim += dt;
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

		timeFromLastSwitchAnim = timeToSpawn;
	}

	~Spawner()
	{
		for (auto enemy : listEnemy)
			delete enemy;
	}

	void deleteAllEnemies()
	{
		if ((int)listEnemy.size() == 0)
			return;

		for (auto enemy = listEnemy.begin(); enemy != listEnemy.end(); enemy++)
			if ((*enemy)->getBody().getPosition().x > (float)GAME_WIDTH)
			{
				delete (*enemy);
				listEnemy.erase(enemy);
			}
	}

	Vector2f getPosition()
	{
		return position;
	}

	void draw(RenderWindow& window)
	{
		for (auto enemy = listEnemy.begin(); enemy != listEnemy.end(); enemy++)
			window.draw((*enemy)->getModel());
	}

	float update(float deltaTime)
	{
		addEnemy(deltaTime);
		updateEnemies(deltaTime);
		deleteUnusedEnemies();

		return deltaTime;
	}

	bool isCollidedWithPlayer(FloatRect const playerBounds)
	{
		for (auto enemy = listEnemy.begin(); enemy != listEnemy.end(); enemy++)
		{
			FloatRect enemyBounds = (*enemy)->getBody().getGlobalBounds();
			if (enemyBounds.intersects(playerBounds))
				return true;
		}
		return false;
	}
};
#endif
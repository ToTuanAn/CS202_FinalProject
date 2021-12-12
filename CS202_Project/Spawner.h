#ifndef SPAWNER_H
#define SPAWNER_H

#include "Enemy.h"
#include "GameWorld.h"
#include "IObject.h"
#include "ISaveable.h"
#include "MovingObject.h"
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
	float speed, timeFromLastSwitchAnim = 0, newObjectTime;
	Vector2f position;
	string type;
	vector<MovingObject*> listEnemy;

	void updateEnemy(float dt)
	{
		for (auto i = listEnemy.begin(); i != listEnemy.end(); i++)
			(*i)->update(dt);
	}

	void addEnemyToList(float dt)
	{
		if (timeFromLastSwitchAnim >= newObjectTime)
		{
			MovingObject* e = new Enemy(type, position, moveToLeft);
			listEnemy.push_back(e);
			timeFromLastSwitchAnim = 0;
		}
		timeFromLastSwitchAnim += dt;
	}

	void deleteUnusedEnemy()
	{
		if ((int)listEnemy.size() == 0)
			return;
		std::vector<MovingObject*>::iterator i = listEnemy.begin();
		if ((*i)->getBody().getPosition().x > (float)GAME_WIDTH)
		{
			delete (*i);
			listEnemy.erase(i);
		}
	}

public:
	void deleteAllEnemy()
	{
		if ((int)listEnemy.size() == 0)
			return;
		for (auto i = listEnemy.begin(); i != listEnemy.end(); i++)
			if ((*i)->getBody().getPosition().x > (float)GAME_WIDTH)
			{
				delete (*i);
				listEnemy.erase(i);
			}
	}

	Spawner(float newObjectTime, Vector2f position, string type, bool moveToLeft)
	{
		this->moveToLeft = moveToLeft;
		this->newObjectTime = newObjectTime;
		this->position = position;
		this->type = type;
		timeFromLastSwitchAnim = newObjectTime;
	}

	Vector2f getPosition()
	{
		return position;
	}

	void draw(RenderWindow& window)
	{
		for (auto i = listEnemy.begin(); i != listEnemy.end(); i++)
		{
			window.draw((*i)->getModel());
		}
	}

	void update(float deltaTime)
	{
		addEnemyToList(deltaTime);
		updateEnemy(deltaTime);
		deleteUnusedEnemy();
	}

	bool UpdateCollsion(FloatRect const playerBounds)
	{
		for (auto i = listEnemy.begin(); i != listEnemy.end(); i++)
		{
			FloatRect enemyBounds = (*i)->getBody().getGlobalBounds();
			if (enemyBounds.intersects(playerBounds))
			{
				return true;
			}
		}
		return false;
	}
};
#endif
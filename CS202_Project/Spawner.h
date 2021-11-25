#ifndef SPAWNER_H
#define SPAWNER_H
#include "Enemy.h"
#include "GameWorld.h"
#include "MovingObject.h"
#include "SFML/Graphics.hpp"
#include "fstream"
#include "string"
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;
class Spawner
{
private:
    float speed, timeFromLastSwitchAnim = 0, newObjectTime;
    Vector2f position;
    string type;
    vector<MovingObject *> listEnemy;
    void updateEnemy()
    {
        for (auto i = listEnemy.begin(); i != listEnemy.end(); i++)
            (*i)->update(dt);
    }

public:
    Spawner(float newObjectTime, Vector2f position, string type)
    {
        this->newObjectTime = newObjectTime;
        this->position = position;
        this->type = type;
    }
};

#endif
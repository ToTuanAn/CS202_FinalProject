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
    void updateEnemy(float dt)
    {
        for (auto i = listEnemy.begin(); i != listEnemy.end(); i++)
            (*i)->update(dt);
    }
    void addEnemyToList(float dt)
    {
        if (timeFromLastSwitchAnim >= newObjectTime)
        {
            MovingObject *e = new Enemy(type, position, false);
            listEnemy.push_back(e);
            timeFromLastSwitchAnim = 0;
        }
        timeFromLastSwitchAnim += dt;
    }
    void deleteUnusedEnemy()
    {
        if ((int)listEnemy.size() == 0)
            return;
        std::vector<MovingObject *>::iterator i = listEnemy.begin();
        if ((*i)->getRectangleShape().getPosition().x > (float)GAME_WIDTH)
        {
            listEnemy.erase(i);
            cout << "delete" << endl;
        }
    }

public:
    Spawner(float newObjectTime, Vector2f position, string type)
    {
        this->newObjectTime = newObjectTime;
        this->position = position;
        this->type = type;
    }
    void draw(RenderWindow &window)
    {
        for (auto i = listEnemy.begin(); i != listEnemy.end(); i++)
        {
            window.draw((*i)->getModel());
        }
    }
    void update(float dt)
    {
        addEnemyToList(dt);
        updateEnemy(dt);
        deleteUnusedEnemy();
    }
};

#endif
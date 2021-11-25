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
    int yDistance = 200;

public:
    ListSpawner()
    {
        listSpawner.push_back(Spawner(6, Vector2f(0, 2880 - GAME_WIDTH / 16), "Bird"));
        listSpawner.push_back(Spawner(5, Vector2f(0, 2880 - (GAME_WIDTH / 16) * 2), "Dinosaur"));
        listSpawner.push_back(Spawner(5, Vector2f(0, 2880 - (GAME_WIDTH / 16) * 4), "Bird"));
        listSpawner.push_back(Spawner(4, Vector2f(0, 2880 - (GAME_WIDTH / 16) * 5), "Dinosaur"));
        listSpawner.push_back(Spawner(3, Vector2f(0, 2880 - (GAME_WIDTH / 16) * 6), "Dinosaur"));
        listSpawner.push_back(Spawner(3, Vector2f(0, 2880 - (GAME_WIDTH / 16) * 8), "Bird"));
        listSpawner.push_back(Spawner(2, Vector2f(0, 2880 - (GAME_WIDTH / 16) * 9), "Dinosaur"));
    }
};
#endif
#ifndef _GAMEWORLD_H_
#define _GAMEWORLD_H_

#include <iostream>
#include "SFML/Graphics.hpp"
#include "GameTile.h"

using namespace std;

const int GAME_HEIGHT = 2880;
const int GAME_WIDTH = 960;

class GameWorld
{
private:
	sf::Vector2i exitPos;
	void setUpInitialState();
	void setUpTiles();
	void setUpUnPassible();

public:
	std::vector<std::vector<GameTile *>> map;
	vector<pair<int, int>> terrainSpawn;
	int gridWidth = GAME_WIDTH / 16;
	int gridHeight = GAME_HEIGHT / 16;
	int offset = gridHeight + 30; //HEIGHT =992
	GameWorld();
};

std::string grassStart();
std::string grassEnd();
std::string grassMid();

std::string roadStart();
std::string roadMid();
std::string roadEnd();

std::string rockStart();
std::string rockMid();
std::string rockEnd();

#endif // !_GAMEWORLD_H_

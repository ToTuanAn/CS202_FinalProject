#ifndef _GAMEWORLD_H_
#define _GAMEWORLD_H_

#include<iostream>
#include"SFML/Graphics.hpp"
#include"GameTile.h"

using namespace std;

class GameWorld {
private:
	sf::Vector2i exitPos;
	void setUpInitialState();
	void setUpTiles();
public:
	std::vector< std::vector < GameTile*> > map;
	int gridWidth = 30;
	int gridHeight = 38;
	GameWorld();
};



#endif // !_GAMEWORLD_H_

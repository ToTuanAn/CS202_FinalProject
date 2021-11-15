#ifndef _GAMEWORLD_H_
#define _GAMEWORLD_H_

#include<iostream>
#include"SFML/Graphics.hpp"
#include"GameTile.h"

using namespace std;

const int WIDTH = 960;
const int HEIGHT = 992;

class GameWorld {
private:
	sf::Vector2i exitPos;
	void setUpInitialState();
	void setUpTiles();
public:
	std::vector< std::vector < GameTile*> > map;
	int gridWidth = WIDTH/16;
	int gridHeight = HEIGHT/16;
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

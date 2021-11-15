#ifndef _GAMETILE_H_
#define _GAMETILE_H_

#include<iostream>
#include"SFML/Graphics.hpp"


using namespace std;
using namespace sf;

class GameTile {
public:
	GameTile(std::string textureName, float x, float y, bool isPassible, bool isExit);
	bool setUpSprite(std::string textureName);
public:
	bool isPassible;
	bool isExit;
	Vector2f pos;
	Texture texture;
	Sprite sprite;
};

#endif // !_GAMETILE_H_


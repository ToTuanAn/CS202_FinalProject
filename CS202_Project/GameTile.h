#ifndef _GAMETILE_H_
#define _GAMETILE_H_

#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class GameTile
{
public:
	bool isPassible;
	bool isExit;
	Vector2f pos;
	Texture texture;
	Sprite sprite;

	GameTile(std::string textureName, float x, float y, bool isPassible, bool isExit)
	{
		if (!setUpSprite(textureName))
			return;

		pos = Vector2f(x, y);
		sprite.setPosition(pos);
		this->isPassible = isPassible;
		this->isExit = isExit;
	}

	bool setUpSprite(std::string textureName)
	{
		if (!texture.loadFromFile(textureName))
			return false;

		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
		return true;
	}
};
#endif
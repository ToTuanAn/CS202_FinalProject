#ifndef _GAMETILE_
#define _GAMETILE_

#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;

class GameTile
{
private:
	bool isPassible;
	bool isExit;
	Vector2f pos;
	Texture texture;
	Sprite sprite;

public:
	GameTile(string textureName, float x, float y, bool isPassible, bool isExit)
	{
		if (!setUpSprite(textureName))
			return;

		pos = Vector2f(x, y);
		sprite.setPosition(pos);
		this->isPassible = isPassible;
		this->isExit = isExit;
	}

	bool setUpSprite(string textureName)
	{
		if (!texture.loadFromFile(textureName))
			return false;

		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
		return true;
	}

	Sprite getSprite()
	{
		return sprite;
	}
};
#endif
#include<iostream>
#include"GameTile.h"

using namespace std;
using namespace sf;

GameTile::GameTile(std::string textureName, float x, float y, bool pass, bool exit) {
	if (!setUpSprite(textureName)) {
		return;
	}
	pos = Vector2f(x, y);
	sprite.setPosition(pos);
	isPassible = pass;
	isExit = exit;
}

bool GameTile::setUpSprite(std::string textureName) {
	if (!texture.loadFromFile(textureName)) {
		return false;
	}
	texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	return true;
}
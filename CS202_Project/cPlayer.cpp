#include<iostream>
#include"cPlayer.h"

using namespace std;

const int WIDTH = 960;
const int HEIGHT = 1000;

Player::Player(int w, int h) {
	this->width = w;
	this->height = h;
	this->position.x = WIDTH/2;
	this->position.y = HEIGHT - this->height;
	this->playerBox.setSize(Vector2f(w, h));
	this->playerBox.setPosition(Vector2f(this->position.x, this->position.y));
}

RectangleShape Player::playerBoxDisplay() {
	return this->playerBox;
}
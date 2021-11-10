#include<iostream>
#include"cPlayer.h"

using namespace std;

const int WIDTH = 960;
const int HEIGHT = 1000;

Player::Player() {
	this->size.w = 60;
	this->size.h = 80;
	this->position.x = WIDTH/2;
	this->position.y = HEIGHT - this->size.h;
	this->playerBox.setSize(Vector2f(this->size.w, this->size.h));
	this->playerBox.setPosition(Vector2f(this->position.x, this->position.y));
}

RectangleShape Player::playerBoxDisplay() {
	return this->playerBox;
}
#include<iostream>
#include"cPlayer.h"

using namespace std;

const int WIDTH = 480;
const int HEIGHT = 608;

Player::Player() {
	this->size.w = 16;
	this->size.h = 16;
	this->position.x = WIDTH/2;
	this->position.y = HEIGHT - this->size.h;
	this->playerBox.setSize(Vector2f(this->size.w, this->size.h));
	this->playerBox.setPosition(Vector2f(this->position.x, this->position.y));
}

void Player::movement(float dt) {
	Vector2f velocity;
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		velocity.x -= this->speed * dt;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)) {
		velocity.x += this->speed * dt;
	}
	else if (Keyboard::isKeyPressed(Keyboard::W)) {
		velocity.y -= this->speed * dt;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S)) {
		velocity.y += this->speed * dt;
	}
	this->playerBox.move(velocity);
}

RectangleShape Player::playerBoxDisplay() {
	return this->playerBox;
}
#ifndef _MOVING_OBJECT_H_
#define _MOVING_OBJECT_H_

#include<iostream>
#include<fstream>
#include"SFML/Graphics.hpp"

using namespace sf;
using namespace std;

const string DATA_PATH = "Data/";
const string MOVING_OBJECT_TYPE[] = { "Player", "Bird", "Dinosaur", "Car", "Truck" };

class MovingObject {
private:
	float speed;
	RectangleShape model;
	bool moveToLeft;

	void LoadData(string type) {
		string path = DATA_PATH + type + ".txt";

		ifstream in(path);
		if (in.is_open()) {
			in >> speed;

			int width, height;
			in >> width >> height;
			model.setSize(Vector2f(width, height));
		}

		in.close();
	}

public:
	MovingObject(string type, Vector2f position, bool moveToLeft) {
		LoadData(type);
		model.setPosition(position);
		this->moveToLeft = moveToLeft;
	}

	virtual void move() {
		Vector2f moveDirection(moveToLeft ? 1 : -1, 0);
		model.move(moveDirection * speed);
	}
};
#endif // !_MOVING_OBJECT_H_

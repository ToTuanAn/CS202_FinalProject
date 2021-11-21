#ifndef _MOVING_OBJECT_H_
#define _MOVING_OBJECT_H_

#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

struct Position {
	int x;  int y;
};

struct Size {
	int w;	int h;
};

const string DATA_PATH = "Data/";

class MovingObject
{
private:
	void LoadData(string type)
	{
		string path = DATA_PATH + type + "/info.txt";

		ifstream in(path);
		if (in.is_open())
		{
			in >> speed;

			int width, height;
			in >> width >> height;
			model.setSize(Vector2f(width, height));

			in >> animSwitchTime;
			in >> animCount;
		}

		in.close();
	}

protected:
	float speed = 100.0f, animSwitchTime, timeFromLastSwitchAnim;
	int animCount, currentAnimIndex;
	RectangleShape model;

	virtual void loadAnimations() = 0;
	virtual void updateAnimation() = 0;
	virtual void move(float dt) = 0;

public:
	MovingObject(string type, Vector2f position , Vector2f size)
	{
		LoadData(type);
		model.setPosition(position);
		cout << position.x << " " << position.y << endl;
		model.setSize(size);
		cout << size.x << " " << size.y << endl;
		timeFromLastSwitchAnim = 0;
	}

	virtual void update(float deltaTime) = 0;
};
#endif // !_MOVING_OBJECT_H_

#ifndef _MOVING_OBJECT_H_
#define _MOVING_OBJECT_H_

#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

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
	float speed, animSwitchTime, timeFromLastSwitchAnim;
	int animCount;
	RectangleShape model;

	virtual void loadAnimations();

public:
	MovingObject(string type, Vector2f position)
	{
		LoadData(type);
		loadAnimations();
		model.setPosition(position);
		timeFromLastSwitchAnim = 0;
	}

	virtual void move();
};
#endif // !_MOVING_OBJECT_H_

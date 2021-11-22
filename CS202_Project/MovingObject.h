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
	int animCount, currentAnimIndex;
	RectangleShape model;
	Sprite sprite;

	virtual void loadAnimations() = 0;
	virtual void updateAnimation() = 0;
	virtual void move(float deltaTime) = 0;

public:
	MovingObject(string type, Vector2f position)
	{
		//LoadData(type);
		model.setPosition(position);
		timeFromLastSwitchAnim = 0;
	}

	virtual void update(float deltaTime) = 0;

#pragma region Get Methods
	RectangleShape getModel()
	{
		return model;
	}
#pragma endregion
};
#endif // !_MOVING_OBJECT_H_

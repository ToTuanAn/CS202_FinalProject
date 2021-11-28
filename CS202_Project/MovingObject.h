#ifndef _MOVING_OBJECT_H_
#define _MOVING_OBJECT_H_

#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>

using namespace sf;
using namespace std;

const string DATA_PATH = "Data/";
const float ANIM_SWITCH_TIME = 0.1;
const int FRAME_PER_ANIM = 4;

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
			//cout << "speed: " << speed << endl;

			int width, height;
			in >> width >> height;
			body.setSize(Vector2f(width, height));
			model.setTextureRect(IntRect(0, 0, width, height));
			//cout << "size: " << width << ", " << height << endl;

			float scale;
			in >> scale;
			model.setScale(Vector2f(scale, scale));
		}

		in.close();
	}

protected:
	float speed, timeFromLastSwitchAnim;
	int currentAnimIndex;
	RectangleShape body;
	Sprite model;

	virtual void loadAnimations() = 0;
	virtual void updateAnimation() = 0;
	virtual void move(float deltaTime) = 0;

public:
	MovingObject(string type, Vector2f position)
	{
		LoadData(type);
		body.setPosition(position);
		model.setPosition(position);
		timeFromLastSwitchAnim = 0;
		currentAnimIndex = 0;
	}
	RectangleShape getRectangleShape()
	{
		return body;
	}
	virtual void update(float deltaTime) = 0;

	RectangleShape getBody()
	{
		return body;
	}
	Sprite getModel()
	{
		return model;
	}
	virtual ~MovingObject()
	{
		// cout << "Destructor Base " << speed << endl; //debug
	}
};
#endif

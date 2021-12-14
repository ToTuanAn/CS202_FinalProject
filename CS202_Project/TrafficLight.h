#ifndef _TRAFFICLIGHT_
#define _TRAFFICLIGHT_

#include "MovingObject.h"
#include <vector>

const float SWITCH_COLOR_TIME = 2;

class TrafficLight : public MovingObject
{
private:
	vector<Texture> anim;
	string type;

	void loadAnimations()
	{
		for (int i = 0; i < 2; ++i)
		{
			string path = DATA_PATH + "Traffic Light/texture (" + to_string(i + 1) + ").png";

			Texture texture;
			texture.loadFromFile(path);
			anim.push_back(texture);
		}
	}

	void updateAnimation()
	{
		if (type == "Green")
		{
			model.setTexture(anim[1]);
			type = "Red";
		}
		else
		{
			model.setTexture(anim[0]);
			type = "Green";
		}
	}

	void move(float deltaTime)
	{
		Vector2f moveDirection(1, 0);
		body.move(moveDirection * speed * deltaTime);
		model.setPosition(body.getPosition());
	}

public:
	TrafficLight(Vector2f position) :
		MovingObject("Light", position)
	{
		loadAnimations();
		model.setTexture(anim[0]);
		type = "Green";
	}

	~TrafficLight()
	{
	}

	float update(float deltaTime)
	{
		timeFromLastSwitchAnim += deltaTime;
		if (timeFromLastSwitchAnim >= SWITCH_COLOR_TIME)
		{
			updateAnimation();
			timeFromLastSwitchAnim = 0;
		}

		return deltaTime;
	}

	string getType()
	{
		return type;
	}
};
#endif
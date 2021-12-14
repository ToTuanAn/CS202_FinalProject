#ifndef _TRAFFICLIGHT_
#define _TRAFFICLIGHT_

#include "MovingObject.h"
#include <vector>

class TrafficLight : public MovingObject
{
private:
	vector<Texture> anim;
	const float switchColorTime = 2;
	string type = "green";

	void loadAnimations()
	{
		for (int i = 0; i <= 1; ++i)
		{
			string path = DATA_PATH + "Light/" + to_string(i) + ".png";
			Texture texture;
			texture.loadFromFile(path);
			anim.push_back(texture);
		}
	}
	void updateAnimation()
	{
		if (type == "green")
		{
			model.setTexture(anim[1]);
			type = "red";
		}
		else
		{
			model.setTexture(anim[0]);
			type = "green";
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
		cout << "Create" << endl;
	}

	~TrafficLight()
	{
	}

	float update(float deltaTime)
	{
		timeFromLastSwitchAnim += deltaTime;
		if (timeFromLastSwitchAnim >= switchColorTime)
		{
			updateAnimation();
			cout << "update"
				 << " " << type << endl;
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
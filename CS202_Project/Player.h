#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "MovingObject.h"
#include <vector>

//int WIDTH = 960;
//int HEIGHT = 992;
const Vector2f PLAYER_STARTING_POSITION(960 / 2, 2880 - 32);
const Vector2f PLAYER_SIZE(32, 32);
const int FRAME_PER_ANIM = 4;

class Player : public MovingObject
{
private:
	vector<Texture> leftAnim, rightAnim, frontAnim, backAnim;
	vector<Texture> currentAnim;

	void loadAnimations()
	{
		vector<Texture> anim;
		for (int i = 1; i <= 16; ++i)
		{
			string path = DATA_PATH + "Player/texture (" + to_string(i) + ").png";
			Texture texture;
			texture.loadFromFile(path);
			anim.push_back(texture);
		}

	frontAnim.assign(anim.begin(), anim.begin() + 4);
		leftAnim.assign(anim.begin() + 4, anim.begin() + 8);
		rightAnim.assign(anim.begin() + 8, anim.begin() + 12);
		backAnim.assign(anim.begin() + 12, anim.begin() + 16);
	}

	void updateAnimation()
	{
		if (timeFromLastSwitchAnim < animSwitchTime)
			return;

		timeFromLastSwitchAnim = 0;
		currentAnimIndex = currentAnimIndex >= currentAnim.size() - 1 ? 0 : currentAnimIndex + 1;

		Texture texture = currentAnim[currentAnimIndex];
		model.setTexture(&texture);
	}

	void move(float deltaTime)
	{
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			model.move(Vector2f(-speed, 0) * deltaTime);
			currentAnim = leftAnim;
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			model.move(Vector2f(speed, 0) * deltaTime);
			currentAnim = rightAnim;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			model.move(Vector2f(0, speed) * deltaTime);
			currentAnim = frontAnim;
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			model.move(Vector2f(0, -speed) * deltaTime);
			currentAnim = backAnim;
		}
	}

public:
	Player() : MovingObject("Player", PLAYER_STARTING_POSITION)
	{
		this->speed = 150.f;
		loadAnimations();
	}

	void update(float deltaTime)
	{
		move(deltaTime);
		timeFromLastSwitchAnim += deltaTime;
		//updateAnimation();
	}
};
#endif // !_PLAYER_H_

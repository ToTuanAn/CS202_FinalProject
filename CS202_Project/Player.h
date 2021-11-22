#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "MovingObject.h"
#include <vector>

const Vector2f PLAYER_STARTING_POSITION(960 / 2, 2880 - 32);
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

		currentAnim = backAnim;
	}

	void updateAnimation()
	{
		if (timeFromLastSwitchAnim < animSwitchTime)
			return;

		timeFromLastSwitchAnim = 0;
		model.setTexture(currentAnim[currentAnimIndex]);
		currentAnimIndex = currentAnimIndex >= currentAnim.size() - 1 ? 0 : currentAnimIndex + 1;
	}

	void move(float deltaTime)
	{
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			body.move(Vector2f(-speed, 0) * deltaTime);
			currentAnim = leftAnim;
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			body.move(Vector2f(speed, 0) * deltaTime);
			currentAnim = rightAnim;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			body.move(Vector2f(0, speed) * deltaTime);
			currentAnim = frontAnim;
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			body.move(Vector2f(0, -speed) * deltaTime);
			currentAnim = backAnim;
		}

		model.setPosition(body.getPosition());
	}

public:
	Player() : MovingObject("Player", PLAYER_STARTING_POSITION)
	{
		loadAnimations();
	}

	void update(float deltaTime)
	{
		move(deltaTime);
		timeFromLastSwitchAnim += deltaTime;
		updateAnimation();
	}
};
#endif

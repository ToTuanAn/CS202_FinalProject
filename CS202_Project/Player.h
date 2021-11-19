#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "MovingObject.h"
#include <vector>

const Vector2f PLAYER_STARTING_POSITION(0, 0);
const int FRAME_PER_ANIM = 4;

class Player : public MovingObject
{
private:
	vector<Texture> leftAnim, rightAnim, frontAnim, backAnim;

	void loadAnimations()
	{
		vector<Texture> anim;
		for (int i = 1; i < 16; ++i)
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

public:
	Player() : MovingObject("Player", PLAYER_STARTING_POSITION)
	{
		loadAnimations();
	}

	void move()
	{
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			model.move(Vector2f(-speed, 0));
			return;
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			model.move(Vector2f(speed, 0));
			return;
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			model.move(Vector2f(0, -speed));
			return;
		}

		if (Keyboard::isKeyPressed(Keyboard::W))
			model.move(Vector2f(0, speed));
	}
};
#endif // !_PLAYER_H_

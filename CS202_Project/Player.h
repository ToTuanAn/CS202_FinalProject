#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "MovingObject.h"

const Vector2f PLAYER_STARTING_POSITION(0, 0);

class Player : public MovingObject
{
public:
	Player() : MovingObject("Player", PLAYER_STARTING_POSITION) {}

	void move() override
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

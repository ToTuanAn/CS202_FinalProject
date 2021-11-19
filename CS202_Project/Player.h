#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "MovingObject.h"

class Player : public MovingObject
{
public:
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

		// Vector2f moveDirection(0, 0);
		// if(Keyboard::isKeyPressed(Keyboard::A))
		// 	moveDirection.x--;
		// if (Keyboard::isKeyPressed(Keyboard::D))
		// 	moveDirection.x++;
		// if (Keyboard::isKeyPressed(Keyboard::S))
		// 	moveDirection.y--;
		// if (Keyboard::isKeyPressed(Keyboard::W))
		// 	moveDirection.y++;
		// model.move(moveDirection * speed);
	}
};
#endif // !_PLAYER_H_

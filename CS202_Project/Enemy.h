#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "MovingObject.h"

class Enemy : public MovingObject
{
private:
	bool moveToLeft;

public:
	Enemy(string type, Vector2f position, bool moveToLeft) : MovingObject(type, position), moveToLeft(moveToLeft) {}

	void move() override
	{
		Vector2f moveDirection(moveToLeft ? 1 : -1, 0);
		model.move(moveDirection * speed);
	}
};
#endif // !_ENEMY_H_

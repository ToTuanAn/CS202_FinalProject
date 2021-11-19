#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "MovingObject.h"
#include <vector>

class Enemy : public MovingObject
{
private:
	bool moveToLeft;
	string type;
	vector<Texture> anim;

	void loadAnimations()
	{
		string path = DATA_PATH + "/" + type + "/texture (";
		for (int i = 1; i <= animCount; ++i)
		{
			Texture texture;
			texture.loadFromFile(path + to_string(i) + ").png");
			anim.push_back(texture);
		}
	}

public:
	Enemy(string type, Vector2f position, bool moveToLeft) : MovingObject(type, position), moveToLeft(moveToLeft)
	{
		this->type = type;
		loadAnimations();
	}

	void move()
	{
		Vector2f moveDirection(moveToLeft ? 1 : -1, 0);
		model.move(moveDirection * speed);
	}
};
#endif // !_ENEMY_H_

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

	void updateAnimation()
	{
		if (timeFromLastSwitchAnim < animSwitchTime)
			return;

		timeFromLastSwitchAnim = 0;
		currentAnimIndex = currentAnimIndex >= anim.size() - 1 ? 0 : currentAnimIndex + 1;

		Texture texture = anim[currentAnimIndex];
		model.setTexture(&texture);
	}

	void move()
	{
		Vector2f moveDirection(moveToLeft ? 1 : -1, 0);
		model.move(moveDirection * speed);
	}

public:
	Enemy(string type, Vector2f position, bool moveToLeft) : MovingObject(type, position), moveToLeft(moveToLeft)
	{
		this->type = type;
		loadAnimations();
	}

	void update(float deltaTime)
	{
		move();
		timeFromLastSwitchAnim += deltaTime;
		updateAnimation();
	}
};
#endif // !_ENEMY_H_

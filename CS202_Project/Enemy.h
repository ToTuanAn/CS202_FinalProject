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
		vector<Texture> tmpAnim;
		for (int i = 1; i <= FRAME_PER_ANIM*2; ++i)
		{
			string path = DATA_PATH + type + "/texture (" + to_string(i) + ").png";
			Texture texture;
			texture.loadFromFile(path);
			tmpAnim.push_back(texture);
		}

		if (moveToLeft)
			anim.assign(tmpAnim.begin(), tmpAnim.begin() + 4);
		else
			anim.assign(tmpAnim.begin() + 4, tmpAnim.begin() + 8);
	}

	void updateAnimation()
	{
		if (timeFromLastSwitchAnim < ANIM_SWITCH_TIME)
			return;

		timeFromLastSwitchAnim = 0;
		model.setTexture(anim[currentAnimIndex]);
		currentAnimIndex = currentAnimIndex >= anim.size() - 1 ? 0 : currentAnimIndex + 1;
	}

	void move(float deltaTime)
	{
		Vector2f moveDirection(moveToLeft ? -1 : 1, 0);
		body.move(moveDirection * speed * deltaTime);
		model.setPosition(body.getPosition());
	}

public:
	Enemy(string type, Vector2f position, bool moveToLeft) : MovingObject(type, position), moveToLeft(moveToLeft)
	{
		this->type = type;
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

#ifndef _ENEMY_
#define _ENEMY_

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
		int startLoad = 0, endLoad = 0;
		if (moveToLeft)
		{
			startLoad = 1;
			endLoad = FRAME_PER_ANIM;
		}
		else
		{
			startLoad = FRAME_PER_ANIM + 1;
			endLoad = FRAME_PER_ANIM * 2;
		}

		for (int i = startLoad; i <= endLoad; ++i)
		{
			string path = DATA_PATH + type + "/texture (" + to_string(i) + ").png";
			Texture texture;
			texture.loadFromFile(path);
			anim.push_back(texture);
		}
	}

	void updateAnimation()
	{
		if (timeFromLastSwitchAnim < ANIM_SWITCH_TIME)
			return;

		timeFromLastSwitchAnim = 0;
		model.setTexture(anim[currentAnimIndex]);
		currentAnimIndex = currentAnimIndex >= (int)anim.size() - 1 ? 0 : currentAnimIndex + 1;
	}

	void move(float deltaTime)
	{
		Vector2f moveDirection(moveToLeft ? -1 : 1, 0);
		body.move(moveDirection * speed * deltaTime);
		model.setPosition(body.getPosition());
	}

public:
	Enemy(string type, Vector2f position, bool moveToLeft) :
		MovingObject(type, position),
		moveToLeft(moveToLeft)
	{
		this->type = type;
		loadAnimations();
	}

	~Enemy()
	{
	}

	void update(float deltaTime)
	{
		move(deltaTime);
		timeFromLastSwitchAnim += deltaTime;
		updateAnimation();
	}

	string getType()
	{
		return type;
	}

	void save(ostream& out)
	{
		out << body.getPosition().x << endl
			<< body.getPosition().y << endl
			<< type << endl
			<< moveToLeft << endl;
	}

	void load(istream& in)
	{
		int x, y;
		in >> x >> y >> type >> moveToLeft;

		body.setPosition(x, y);
	}
};
#endif
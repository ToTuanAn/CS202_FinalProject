#ifndef _PLAYER_
#define _PLAYER_

#include "GameWorld.h"
#include "ISaveable.h"
#include "GameObject.h"

#include <vector>

const Vector2f PLAYER_STARTING_POSITION(960 / 2, 2880 - 32);
const float SCORE_WIDTH = 145;

class Player : public GameObject, public ISaveable
{
private:
	vector<Texture> leftAnim, rightAnim, frontAnim, backAnim;
	vector<Texture> currentAnim;
	bool isIdle;
	bool boundEast, boundWest, boundNorth, boundSouth;
	int score;

	void loadAnimations()
	{
		vector<Texture> anim;
		for (int i = 1; i <= FRAME_PER_ANIM * 4; ++i)
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
		model.setTexture(currentAnim[0]);
	}

	void updateAnimation()
	{
		if (timeFromLastSwitchAnim < ANIM_SWITCH_TIME)
			return;

		timeFromLastSwitchAnim = 0;
		model.setTexture(currentAnim[currentAnimIndex]);

		if (!isIdle)
			currentAnimIndex = currentAnimIndex >= (int)currentAnim.size() - 1 ? 0 : currentAnimIndex + 1;
	}

	void move(float deltaTime)
	{
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			if (!boundWest)
				body.move(Vector2f(-speed, 0) * deltaTime);
			currentAnim = leftAnim;
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			if (!boundEast)
				body.move(Vector2f(speed, 0) * deltaTime);
			currentAnim = rightAnim;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			if (!boundSouth)
				body.move(Vector2f(0, speed) * deltaTime);
			currentAnim = frontAnim;
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			if (!boundNorth)
				body.move(Vector2f(0, -speed) * deltaTime);
			currentAnim = backAnim;
		}
		else
		{
			isIdle = true;
			currentAnimIndex = 0;
		}

		isIdle = false;
		model.setPosition(body.getPosition());
	}

public:
	Player() :
		GameObject("Player", PLAYER_STARTING_POSITION)
	{
		loadAnimations();
		isIdle = true;
		score = 0;

		cout << "Player is set up.\n";
	}

	~Player()
	{
		cout << "Delete Player!\n";
	}

	float update(float deltaTime)
	{
		move(deltaTime);
		timeFromLastSwitchAnim += deltaTime;
		updateAnimation();

		return deltaTime;
	}

	int getScore()
	{
		int currentScore = -(body.getPosition().y - PLAYER_STARTING_POSITION.y) / SCORE_WIDTH;
		score = currentScore > score ? currentScore : score;
		return score;
	}

	string getType()
	{
		return "Player";
	}

	void setBound(Vector2f cameraPosition)
	{
		boundEast = body.getPosition().x >= cameraPosition.x + SCREEN_WIDTH / 2;
		boundWest = body.getPosition().x <= cameraPosition.x - SCREEN_WIDTH / 2;
		boundNorth = body.getPosition().y <= cameraPosition.y - SCREEN_HEIGHT / 2;
		boundSouth = body.getPosition().y >= cameraPosition.y + SCREEN_HEIGHT / 2 - 100;
	}

	void save(ostream& out)
	{
		out.write((char*)&body.getPosition(), sizeof(body.getPosition()));
		out.write((char*)&score, sizeof(score));
	}

	void load(istream& in)
	{
		in.read((char*)&body.getPosition(), sizeof(body.getPosition()));
		in.read((char*)&score, sizeof(score));
		currentAnim = backAnim;
	}
};
#endif

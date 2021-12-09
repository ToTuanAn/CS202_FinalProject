#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "ListSpawner.h"
#include "Player.h"

#include <iostream>
#include <vector>

using namespace std;

class Collision
{
public:
	void UpdateCollision(Player mainPlayer, ListSpawner listSpawner)
	{
		bool check = listSpawner.updateCollsion(mainPlayer);

		if (check)
			cout << "In theory, player dead!\n";
	}
};
#endif
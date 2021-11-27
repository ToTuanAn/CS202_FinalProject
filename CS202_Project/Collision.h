#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "ListSpawner.h"
#include "Player.h"
#include <vector>

using namespace std;

class Collision
{
private:
public:
	void UpdateCollision(Player mainPlayer, ListSpawner listSpawner)
	{
		bool check = listSpawner.UpdateCollsion(mainPlayer);

		if (check)
		{
			
		}
	}
};

#endif

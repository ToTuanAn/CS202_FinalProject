#ifndef _GAMEWORLD_H_
#define _GAMEWORLD_H_

#include <iostream>
#include "SFML/Graphics.hpp"
#include "GameTile.h"

using namespace std;
using namespace sf;

const int GAME_HEIGHT = 2880;
const int GAME_WIDTH = 960;

class GameWorld
{
private:
	Vector2i exitPos;

	void setUpInitialState()
	{
		setUpTiles();
		setUpUnPassible();
	}

	void setUpTiles()
	{
		map.clear();

		for (int i = 0; i < this->gridHeight;)
		{

			int choice = rand() % 3 + 1;
			int num = rand() % 4 + 6;
			string start, mid, end;

			switch (choice)
			{
			case 1:
				start = grassStart();
				mid = grassMid();
				end = grassEnd();
				break;
			case 2:
				start = roadStart();
				mid = roadMid();
				end = roadEnd();
				break;
			case 3:
				start = rockStart();
				mid = rockMid();
				end = rockEnd();
				break;
			default:
				break;
			}

			string terrain;
			for (int k = 0; k < num; k++)
			{
				vector<GameTile *> row;
				int j = 0;

				if (k == 0)
				{
					terrain = start;
				}
				else if (k == num - 1)
				{
					terrain = end;
				}
				else
				{
					terrain = mid;
				}
				if (i >= this->gridHeight)
					break;
				while (j < GAME_WIDTH)
				{
					row.push_back(new GameTile(terrain, j, i * 16, false, false));
					j += 16;
				}
				terrainSpawn.push_back(make_pair(choice, i * 16));
				map.push_back(row);
				i++;
			}
		}
	}

	void setUpUnPassible()
	{
		string terrain = "Tiles/tile_0198.png";
		for (int i = this->gridHeight; i < offset; i++)
		{
			int j = 0;
			vector<GameTile *> row;
			while (j < GAME_WIDTH)
			{
				row.push_back(new GameTile(terrain, j, i * 16, false, false));
				j += 16;
			}
			map.push_back(row);
		}
	}

public:
	vector<vector<GameTile *>> map;
	vector<pair<int, int>> terrainSpawn;
	int gridWidth = GAME_WIDTH / 16;
	int gridHeight = GAME_HEIGHT / 16;
	int offset = gridHeight + 30;

	GameWorld()
	{
		setUpInitialState();
	}
};

string grassMid()
{
	return "Tiles/tile_0028.png";
}

string grassStart()
{
	return "Tiles/tile_0001.png";
}

string grassEnd()
{
	return "Tiles/tile_0055.png";
}

string roadStart()
{
	return "Tiles/tile_0406.png";
}

string roadMid()
{
	return "Tiles/tile_0468.png";
}

string roadEnd()
{
	return "Tiles/tile_0460.png";
}

string rockStart()
{
	return "Tiles/tile_0009.png";
}

string rockMid()
{
	return "Tiles/tile_0036.png";
}

string rockEnd()
{
	return "Tiles/tile_0063.png";
}
#endif
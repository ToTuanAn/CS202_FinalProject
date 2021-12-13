#ifndef _GAMEWORLD_
#define _GAMEWORLD_

#include "GameTile.h"
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;

const int GAME_HEIGHT = 2880;
const int GAME_WIDTH = 960;

const int HEIGHT = 992;
const int WIDTH = 960;

const float CAMERA_SPEED = 1;

const int TILES_PER_LANE = 7;
const int SPAWNER_LANE_WIDTH = 28;
const int SPAWNER_LANE_WIDTH_OFFSET = -24;

const int GRID_WIDTH = GAME_WIDTH / 16;
const int GRID_HEIGHT = GAME_HEIGHT / 16;
const int OFFSET = GRID_HEIGHT + 30;

class GameWorld
{
private:
	vector<vector<GameTile*>> tiles;
	vector<pair<string, int>> lanes;
	Vector2i exitPos;

	string randomLane()
	{
		int laneRandom = rand() % 3;

		if (laneRandom == 0)
			return "Grass";

		if (laneRandom == 1)
			return "Road";

		return "Rock";
	}

	string getRowTile(int& row, string& startTile, string& middleTile, string& endTile)
	{
		if (row == 0)
			return startTile;

		if (row == TILES_PER_LANE - 1)
			return endTile;

		return middleTile;
	}

	void setUpTiles()
	{
		tiles.clear();

		for (int lane = 0; lane < GRID_HEIGHT;)
		{
			string laneRandom = randomLane();
			string lanePath = "Tiles/" + laneRandom + "/";
			string startTile = lanePath + "start.png", middleTile = lanePath + "middle.png", endTile = lanePath + "end.png";

			for (int row = 0; row < TILES_PER_LANE; ++row)
			{
				if (lane >= GRID_HEIGHT)
					break;

				vector<GameTile*> rowTiles;
				string terrain = getRowTile(row, startTile, middleTile, endTile);

				for (int rowTile = 0; rowTile < GAME_WIDTH; rowTile += 16)
					rowTiles.push_back(new GameTile(terrain, rowTile, lane * 16, false, false));

				lanes.push_back(make_pair(laneRandom, lane * SPAWNER_LANE_WIDTH + SPAWNER_LANE_WIDTH_OFFSET));
				tiles.push_back(rowTiles);

				++lane;
			}
		}
	}

	void setUpUnPassible()
	{
		string terrain = "Tiles/StartGameTile.png";

		for (int row = GRID_HEIGHT; row < OFFSET; ++row)
		{
			vector<GameTile*> rowTiles;

			for (int rowTile = 0; rowTile < GAME_WIDTH; rowTile += 16)
				rowTiles.push_back(new GameTile(terrain, rowTile, row * 16, false, false));

			tiles.push_back(rowTiles);
		}
	}

public:
	GameWorld()
	{
		setUpTiles();
		setUpUnPassible();
	}

	vector<vector<GameTile*>> getTiles()
	{
		return tiles;
	}

	vector<pair<string, int>> getLanes()
	{
		return lanes;
	}
};
#endif
#include<iostream>
#include"GameWorld.h"

GameWorld::GameWorld() {
	gridWidth = 30;
	gridHeight = 38;
	setUpInitialState();
}

void GameWorld::setUpInitialState() {
	setUpTiles();
}

void GameWorld::setUpTiles() {
	map.clear();
	for (int i = 0; i < this->gridHeight; i++) {
		std::vector<GameTile*> firstRow;
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 0, i*16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 16, i*16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 32, i*16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 48, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 64, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 80, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 96, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 112, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 128, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 144, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 160, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 176, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 192, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 208, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 224, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 240, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 256, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 272, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 288, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 304, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 320, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 336, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 352, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 368, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 384, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 400, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 416, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 432, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 448, i * 16, false, false));
		firstRow.push_back(new GameTile("Tiles/tile_0028.png", 464, i * 16, false, false));
		map.push_back(firstRow);
	}
}
#ifndef _C_PLAYER_H_
#define _C_PLAYER_H_

#include<iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"

using namespace sf;
using namespace std;

struct Position {
	int x;
	int y;
};

class Player{
public:
	Player(int w = 60 , int h = 80);
	RectangleShape playerBoxDisplay();
private:
	int width;
	int height;
	Position position;
	RectangleShape playerBox;
};

#endif // !_C_PLAYER_H_

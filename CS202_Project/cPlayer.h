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

struct Size {
	int w; 
	int h;
};

class Player{
public:
	Player();
	RectangleShape playerBoxDisplay();
private:
	Size size;
	Position position;
	RectangleShape playerBox; 
};

#endif // !_C_PLAYER_H_

#ifndef _VICTORY_H_
#define _VICTORY_H_

#include "SFML/Graphics.hpp"
#include "UIScreen.h"
#include <iostream>

using namespace std;
using namespace sf;

class Victory : public UIScreen {
public:
	Victory()
	{
		if (!font.loadFromFile("Fonts/" + MENU_FONT_NAME))
			cout << "Can't load " + MENU_FONT_NAME << endl;
		else
			cout << MENU_FONT_NAME + " is loaded!\n";
		this->texts[0] = "Back to game";
		this->texts[1] = "Exit Game";
		this->texts[2] = "";
		this->MAX_NUMBER_OF_ITEMS = 2;
		this->titleStr = "VICTORY";
	}

	~Victory()
	{}

	void eventMethod(RenderWindow& MENU, bool& isMenu, bool& isSelect) {
		Event event;

		while (MENU.pollEvent(event)) {
			if (event.type == Event::Closed)
			{
				MENU.close();
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Up)
				{
					this->MoveUp();
					break;
				}
				if (event.key.code == Keyboard::Down)
				{
					this->MoveDown();
					break;
				}
				if (event.key.code == Keyboard::Return)
				{
					switch (this->GetPressedItem())
					{
					case 0:
						std::cout << "Back to menu has been pressed" << std::endl;
						isMenu = true;
						isSelect = false;
						break;
					case 1:
						std::cout << "Exit has been pressed" << std::endl;
						isSelect = false;
						MENU.close();
						break;
					default:
						break;
					}
				}
			}
		}
	}
};


#endif

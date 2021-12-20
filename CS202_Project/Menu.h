#ifndef _MENU_
#define _MENU_

#include "Load.h"
#include "SFML/Graphics.hpp"
#include "SaveLoadSystem.h"
#include "UIScreen.h"
#include <iostream>

using namespace std;
using namespace sf;

class Menu : public UIScreen
{
public:
	Menu()
	{
		if (!font.loadFromFile("Fonts/" + MENU_FONT_NAME))
			cout << "Can't load " + MENU_FONT_NAME << endl;
		else
			cout << MENU_FONT_NAME + " is loaded!\n";
		this->texts[0] = "New Game";
		this->texts[1] = "Load Game";
		this->texts[2] = "Exit Game";
	}

	~Menu()
	{}

	/*void changeLoad(SaveLoadSystem sys) {
		vector<string> allFile = sys.getAllFiles();
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
			if (allFile[i] != "") {
				this->list[i].setString(allFile[i]);
			}
			else {
				this->list[i].setString("Empty");
			}
		}
		this->selectedItemIndex = 0;
	}*/

	void eventMethod(RenderWindow& MENU, bool& isMenu, SaveLoadSystem sys)
	{
		Event event;

		while (MENU.pollEvent(event))
		{
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
							std::cout << "New game button has been pressed" << std::endl;
							isMenu = false;
							break;
						case 1:
							std::cout << "Load game button has been pressed" << std::endl;
							while (true)
							{
								LoadScreen loadScreen(sys);
								loadScreen.eventMethod(MENU, sys);
								loadScreen.show(MENU);
							}
							isMenu = false;
							break;
						case 2:
							MENU.close();
							break;
						default:
							break;
					}
				}
			}
		}
	}

private:
};
#endif
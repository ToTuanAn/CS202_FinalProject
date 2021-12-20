#ifndef LOAD_H
#define LOAD_H

#include "SFML/Graphics.hpp"
#include "SaveLoadSystem.h"
#include "UIScreen.h"
#include <iostream>

using namespace std;
using namespace sf;

class LoadScreen : public UIScreen
{
public:
	LoadScreen(SaveLoadSystem sys)
	{
		if (!font.loadFromFile("Fonts/" + MENU_FONT_NAME))
			cout << "Can't load " + MENU_FONT_NAME << endl;
		else
			cout << MENU_FONT_NAME + " is loaded!\n";

		vector<string> allLoadFile = sys.getAllFiles();
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			if (allLoadFile[i] != "")
			{
				this->list[i].setString(allLoadFile[i]);
			}
			else
			{
				this->list[i].setString("Empty");
			}
		}
		this->selectedItemIndex = 0;
	}

	void eventMethod(RenderWindow& MENU, SaveLoadSystem sys)
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
							sys.setCurrentFile(this->list[0].getString());
							break;
						case 1:
							sys.setCurrentFile(this->list[1].getString());
							break;
						case 2:
							sys.setCurrentFile(this->list[2].getString());
							break;
						default:
							break;
					}
				}
			}
		}
	}
};

#endif // !LOAD_H

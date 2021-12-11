#ifndef _MENU_H_
#define _MENU_H_

#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3

using namespace std;
using namespace sf;

const string MENU_FONT_NAME = "UIFont.ttf";

class Menu
{
public:
	Menu(float width, float height)
	{
		if (!font.loadFromFile("Fonts/" + MENU_FONT_NAME))
			cout << "Can't load " + MENU_FONT_NAME << endl;
		else
			cout << MENU_FONT_NAME + " is loaded\n";

		menu[0].setFont(font);
		menu[0].setFillColor(sf::Color::Red);
		menu[0].setString("New Game");
		menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

		menu[1].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[1].setString("Load Game");
		menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

		menu[2].setFont(font);
		menu[2].setFillColor(sf::Color::White);
		menu[2].setString("Exit");
		menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

		selectedItemIndex = 0;
	}

	~Menu() {}

	void draw(sf::RenderWindow &window)
	{
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			window.draw(menu[i]);
		}
	}

	void moveUp()
	{
		if (selectedItemIndex - 1 >= 0)
		{
			menu[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex--;
			menu[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}

	void moveDown()
	{
		if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
		{
			menu[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex++;
			menu[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}

	int getPressedItem()
	{
		return selectedItemIndex;
	}

	void show(RenderWindow &MENU)
	{
		while (MENU.isOpen())
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
						this->moveUp();
						break;
					}
					if (event.key.code == Keyboard::Down)
					{
						this->moveDown();
						break;
					}
					if (event.key.code == Keyboard::Return)
					{
						switch (this->getPressedItem())
						{
						case 0:
							std::cout << "Play button has been pressed" << std::endl;
							break;
						case 1:
							std::cout << "Option button has been pressed" << std::endl;
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
			MENU.clear();
			this->draw(MENU);
			MENU.display();
		}
	}

private:
	int selectedItemIndex;
	Font font;
	Text menu[MAX_NUMBER_OF_ITEMS];
};
#endif
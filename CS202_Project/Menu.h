#ifndef _MENU_H_
#define _MENU_H_

#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3

using namespace std;
using namespace sf;

class Menu
{
public:
	Menu(float width, float height) {
		if (!font.loadFromFile("arial.ttf"))
		{
			// handle error
			cout << "huhu";
		}

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

	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			window.draw(menu[i]);
		}
	}

	void MoveUp() {
		if (selectedItemIndex - 1 >= 0)
		{
			menu[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex--;
			menu[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}

	void MoveDown() {
		if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
		{
			menu[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex++;
			menu[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}

	int GetPressedItem() { return selectedItemIndex; }

	void show(RenderWindow& MENU) {
		while (MENU.isOpen()) {
			Event event;

			while (MENU.pollEvent(event)) {

				if (event.type == Event::Closed) {
					MENU.close();
				}

				if (event.type == Event::KeyPressed) {
					if (event.key.code == Keyboard::Up) {
						this->MoveUp();
						break;
					}
					if (event.key.code == Keyboard::Down) {
						this->MoveDown();
						break;
					}
					if (event.key.code == Keyboard::Return) {
						switch (this->GetPressedItem())
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



#endif // !_MENU_H_


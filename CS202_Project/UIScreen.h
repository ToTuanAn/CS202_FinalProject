#ifndef _UIScreen_
#define _UIScreen_

#include "SFML/Graphics.hpp"
#include<iostream>

using namespace std;
using namespace sf;

const string MENU_FONT_NAME = "UIFont.ttf";

class UIScreen
{
public:
	UIScreen()
	{
	}

	void create(float width, float height) {
		list[0].setFont(font);
		list[0].setFillColor(sf::Color::Red);
		list[0].setString(this->texts[0]);
		list[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

		list[1].setFont(font);
		list[1].setFillColor(sf::Color::White);
		list[1].setString(this->texts[1]);
		list[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

		list[2].setFont(font);
		list[2].setFillColor(sf::Color::White);
		list[2].setString(this->texts[2]);
		list[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

		selectedItemIndex = 0;
	}

	~UIScreen()
	{
		delete[] this->list;
		delete[] this->texts;
	}

	void draw(sf::RenderWindow& window)
	{
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			window.draw(list[i]);
		}
	}

	void MoveUp()
	{
		if (selectedItemIndex - 1 >= 0)
		{
			list[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex--;
			list[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}

	void MoveDown()
	{
		if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
		{
			list[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex++;
			list[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}

	int GetPressedItem()
	{
		return selectedItemIndex;
	}

	void show(RenderWindow& MENU)
	{
		MENU.clear();
		this->draw(MENU);
		MENU.display();
	}

protected:
	int selectedItemIndex;
	Font font;
	int MAX_NUMBER_OF_ITEMS = 3;
	Text* list = new Text[MAX_NUMBER_OF_ITEMS];
	string* texts = new string[MAX_NUMBER_OF_ITEMS];
};
#endif

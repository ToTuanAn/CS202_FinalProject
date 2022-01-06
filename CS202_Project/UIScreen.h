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
		title.setFont(font);
		title.setFillColor(sf::Color::White);
		title.setString(titleStr);
		title.setPosition(sf::Vector2f(width / 2 - 400, 10));
		title.setOutlineColor(sf::Color::Black);
		title.setOutlineThickness(5);
		title.setScale(5, 5);

		list[0].setFont(font);
		list[0].setFillColor(sf::Color::Red);
		list[0].setString(this->texts[0]);
		list[0].setPosition(sf::Vector2f(width / 2, height/5 +  height / (MAX_NUMBER_OF_ITEMS + 2) * 1));
		list[0].setOutlineColor(sf::Color::Black);
		list[0].setOutlineThickness(1);
		list[0].setScale(2, 2);

		list[1].setFont(font);
		list[1].setFillColor(sf::Color::White);
		list[1].setString(this->texts[1]);
		list[1].setPosition(sf::Vector2f(width / 2, height/5 + height / (MAX_NUMBER_OF_ITEMS + 2) * 2));
		list[1].setOutlineColor(sf::Color::Black);
		list[1].setOutlineThickness(1);
		list[1].setScale(2, 2);

		list[2].setFont(font);
		list[2].setFillColor(sf::Color::White);
		list[2].setString(this->texts[2]);
		list[2].setPosition(sf::Vector2f(width / 2, height/5 + height / (MAX_NUMBER_OF_ITEMS + 2) * 3));
		list[2].setOutlineColor(sf::Color::Black);
		list[2].setOutlineThickness(1);
		list[2].setScale(2, 2);

		selectedItemIndex = 0;

		bg.loadFromFile(bgPath);
		background.setTexture(bg);
		background.setOrigin(0, 0);

		ic.loadFromFile(icPath);
		icons[0].setTexture(ic);
		icons[0].setScale(0.1, 0.1);
		icons[0].setPosition(sf::Vector2f(width / 3, height / 5 + height / (MAX_NUMBER_OF_ITEMS + 2) * 1));

		icons[1].setTexture(ic);
		icons[1].setScale(0.1, 0.1);
		icons[1].setPosition(sf::Vector2f(width / 3, height / 5 + height / (MAX_NUMBER_OF_ITEMS + 2) * 2));

		icons[2].setTexture(ic);
		icons[2].setScale(0.1, 0.1);
		icons[2].setPosition(sf::Vector2f(width / 3, height / 5 + height / (MAX_NUMBER_OF_ITEMS + 2) * 3));
	}

	~UIScreen()
	{
		delete[] this->list;
		delete[] this->texts;
		delete[] this->icons;
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(background);
		window.draw(title);
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			window.draw(list[i]);
			window.draw(icons[i]);
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

	//background
	Texture bg;
	Sprite background;
	string bgPath = "Background/Menu1.png";

	//icon
	Texture ic;
	Sprite* icons = new Sprite[MAX_NUMBER_OF_ITEMS];
	string icPath = "Background/icon.png";
	
	Text title;
	string titleStr = "POKEMON \nCROSSY ROAD";

	Text* list = new Text[MAX_NUMBER_OF_ITEMS];
	string* texts = new string[MAX_NUMBER_OF_ITEMS];
};
#endif

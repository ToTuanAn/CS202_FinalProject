#ifndef _UI_TEXT_H_
#define _UI_TEXT_H_

#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;
using namespace std;

class UIText
{
private:
	Text text;

public:
	UIText(string fontName, unsigned int fontSize, Color color, float outlineThickness = 0, Color outlineColor = Color::White, Uint32 style = Text::Regular)
	{
		Font font;
		if (!font.loadFromFile("Fonts/" + fontName))
			cout << "Can't load " + fontName << endl;
		else
			cout << fontName + " is loaded!\n";
		text.setFont(font);

		text.setCharacterSize(fontSize);
		text.setFillColor(color);

		text.setOutlineThickness(outlineThickness);
		text.setOutlineColor(outlineColor);

		text.setStyle(style);
	}

	Text getText()
	{
		return text;
	}

	void setText(string text)
	{
		this->text.setString(text);
	}
};
#endif
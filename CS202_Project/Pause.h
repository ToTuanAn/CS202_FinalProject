#ifndef _PAUSE_H_
#define _PAUSE_H_

class PauseScreen : public UIScreen
{
public:
	PauseScreen()
	{
		if (!font.loadFromFile("Fonts/" + MENU_FONT_NAME))
			cout << "Can't load " + MENU_FONT_NAME << endl;
		else
			cout << MENU_FONT_NAME + " is loaded!\n";
		this->texts[0] = "Save Game";
		this->texts[1] = "Resume Game";
		this->texts[2] = "Back to menu";
	}

	void eventMethod(RenderWindow& MENU, bool& isMenu, bool& isPause)
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
							std::cout << "Save button has been pressed" << std::endl;
							break;
						case 1:
							std::cout << "Resume button has been pressed" << std::endl;
							break;
						case 2:
							isMenu = true;
							break;
						default:
							break;
					}
					isPause = false;
				}
			}
		}
	}

private:
};

#endif

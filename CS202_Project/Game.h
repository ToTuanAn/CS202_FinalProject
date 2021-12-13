#ifndef _GAME_
#define _GAME_

#include "GameWorld.h"
#include "IObject.h"
#include "ListSpawner.h"
#include "Player.h"
#include "SaveLoadSystem.h"

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include <vector>

using namespace std;
using namespace sf;

const string SCORE_FONT_NAME = "PixelFont.ttf";
const string GAME_MUSIC_NAME = "GameMusic.wav";

class Game : public IObject
{
private:
	vector<IObject*> objects;
	Player player;
	Text scoreText;
	Sound gameMusic;
	ListSpawner listSpawner;

	bool createScoreText()
	{
		Font scoreTextFont;
		if (!scoreTextFont.loadFromFile("Fonts/" + SCORE_FONT_NAME))
		{
			cout << "Can't load " + SCORE_FONT_NAME << endl;
			return false;
		}

		cout << SCORE_FONT_NAME + " is loaded!\n";

		scoreText.setCharacterSize(50);
		scoreText.setFont(scoreTextFont);
		scoreText.setFillColor(Color::Red);
		scoreText.setOutlineColor(Color::Blue);
		scoreText.setOutlineThickness(2);
		scoreText.setStyle(Text::Bold);
		scoreText.setOrigin(scoreText.getGlobalBounds().width - (WIDTH / 2 - 75), scoreText.getGlobalBounds().height / 2);

		return true;
	}

	bool createGameMusic()
	{
		SoundBuffer buffer;
		if (!buffer.loadFromFile("Sounds/" + GAME_MUSIC_NAME))
		{
			cout << "Can't load " + GAME_MUSIC_NAME << endl;
			return false;
		}

		cout << GAME_MUSIC_NAME + " is loaded!\n";

		gameMusic.setBuffer(buffer);
		gameMusic.setLoop(true);
		gameMusic.play();

		return true;
	}

public:
};
#endif
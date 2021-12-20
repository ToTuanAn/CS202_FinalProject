#ifndef _GAME_
#define _GAME_

#include "GameWorld.h"
#include "ListSpawner.h"
#include "Menu.h"
#include "Pause.h"
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
const unsigned int GAME_FPS = 60;

class Game
{
private:
	float deltaTime;
	Clock clock;

	RenderWindow window;
	View view;

	Player player;

	Font scoreTextFont;
	Text scoreText;

	SoundBuffer gameMusicBuffer;
	Sound gameMusic;

	GameWorld gameWorld;
	ListSpawner listSpawner;

	Menu menu;
	PauseScreen pauseScreen;
	LoadScreen loadScreen;

	SaveLoadSystem saveLoadSystem;
	bool isMenu = true;
	bool isPause = false;

	void setupWindow(string title)
	{
		window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), title);
		window.setFramerateLimit(GAME_FPS);
	}

	void setupView()
	{
		view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		view.setCenter(player.getBody().getPosition() - Vector2f(0, 368));
	}

	void setupSaveLoadSystem()
	{
		saveLoadSystem.setViewToSaveLoadPosition(&view);
		saveLoadSystem.addSaveableObject(&player);
		saveLoadSystem.addSaveableObject(&listSpawner);
	}

	void setupListSpawner()
	{
		listSpawner.setupFromNewGame(gameWorld.getLanePositionYs());
	}

	bool createScoreText()
	{
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

		scoreText.setOrigin(scoreText.getGlobalBounds().width / 2 - (SCREEN_WIDTH / 2 - 75), scoreText.getGlobalBounds().height / 2);

		return true;
	}

	bool createGameMusic()
	{
		if (!gameMusicBuffer.loadFromFile("Sounds/" + GAME_MUSIC_NAME))
		{
			cout << "Can't load " + GAME_MUSIC_NAME << endl;
			return false;
		}

		cout << GAME_MUSIC_NAME + " is loaded!\n";

		gameMusic.setBuffer(gameMusicBuffer);
		gameMusic.setLoop(true);
		gameMusic.play();

		return true;
	}

	void update()
	{
		saveLoadSystem.update(deltaTime);

		view.move(Vector2f(0, -CAMERA_SPEED));

		player.setBound(view.getCenter());
		player.update(deltaTime);
		scoreText.setString("Score: " + to_string(player.getScore()));
		listSpawner.update(deltaTime, player, view.getCenter().y);
	}

	void draw()
	{
		window.clear();
		window.setView(view);

		gameWorld.draw(window);
		listSpawner.draw(window, player, view.getCenter().y);
		window.draw(player.getModel());
		window.setView(window.getDefaultView());
		window.draw(scoreText);

		window.display();
	}

	void eventMethod()
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::P)
				{
					isPause = true;
					while (isPause)
					{
						pauseScreen.eventMethod(window, isMenu, isPause, &saveLoadSystem);
						pauseScreen.show(window);
					}
				}
			}
		}
	}

	void setupUI()
	{
		menu.create(SCREEN_WIDTH, SCREEN_HEIGHT);
		pauseScreen.create(SCREEN_WIDTH, SCREEN_HEIGHT);
		loadScreen.connect(&saveLoadSystem);
		loadScreen.create(SCREEN_WIDTH, SCREEN_HEIGHT);
	}

public:
	Game(string title)
	{
		setupUI();
		setupWindow(title);
		setupView();
		setupListSpawner();
		createScoreText();
		createGameMusic();
		setupSaveLoadSystem();
	}

	void play()
	{

		while (window.isOpen())
		{
			if (isMenu)
			{
				menu.eventMethod(window, isMenu, &saveLoadSystem, &loadScreen);
				menu.show(window);
			}
			else
			{
				if (listSpawner.isCollidedWithPlayer(player))
				{
					cout << "Player is dead!\n";
					//return;
				}
				deltaTime = clock.restart().asSeconds();
				eventMethod();
				update();
				draw();
			}
		}
	}
};
#endif
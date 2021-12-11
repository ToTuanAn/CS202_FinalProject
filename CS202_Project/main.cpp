#include "Collision.h"
#include "Enemy.h"
#include "GameTile.h"
#include "GameWorld.h"
#include "ListSpawner.h"
#include "Menu.h"
#include "Player.h"
#include "Spawner.h"
#include "UIText.h"

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

#include <iostream>

using namespace sf;
using namespace std;

const int WIDTH = 960;
const int HEIGHT = 992;

int main()
{
	float dt;
	Clock dt_clock;

	// Menu
	RenderWindow MENU(sf::VideoMode(WIDTH, HEIGHT), "CROSSY ROAD GROUP 10");
	Menu menu(MENU.getSize().x, MENU.getSize().y);
	MENU.setFramerateLimit(60);
	menu.show(MENU);

	// Window
	RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "CROSSY ROAD GROUP 10");
	window.setFramerateLimit(30);

	// Map
	GameWorld map = GameWorld();

	// Spawners
	ListSpawner listSpawner(map.terrainSpawn);
	Collision collision;

	// Player
	Player mainPlayer;

	// Main view
	View mainView;
	mainView.setSize(WIDTH, HEIGHT);
	mainView.setCenter(mainPlayer.getBody().getPosition() - Vector2f(0, 368));

	// Score Text
	UIText scoreText("PixelFont.ttf", 50, Color::Red, 2, Color::Red, Text::Bold);
	scoreText.getText().setOrigin(scoreText.getText().getGlobalBounds().width - (WIDTH / 2 - 75), scoreText.getText().getGlobalBounds().height / 2);

	// Sound
	const string GAME_MUSIC_NAME = "GameMusic";
	string GAME_MUSIC_FILE_NAME = GAME_MUSIC_NAME + ".wav";

	SoundBuffer gameMusicBuffer;
	if (!gameMusicBuffer.loadFromFile("Sounds/" + GAME_MUSIC_FILE_NAME))
	{
		cout << "Can't load " + GAME_MUSIC_FILE_NAME << endl;
		return 0;
	}
	else
		cout << GAME_MUSIC_FILE_NAME + " is loaded!\n";

	Sound gameMusic;
	gameMusic.setBuffer(gameMusicBuffer);
	gameMusic.setLoop(true);
	gameMusic.play();

	while (window.isOpen())
	{
		dt = dt_clock.restart().asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		// Update
		mainPlayer.update(dt);
		listSpawner.update(dt, mainPlayer, mainView.getCenter().y);
		mainView.move(Vector2f(0.f, -2.f));

		// Collision
		collision.UpdateCollision(mainPlayer, listSpawner);

		// Draw
		window.clear();
		window.setView(mainView);

		for (int x = 0; x < map.offset; x++)
			for (int y = 0; y < map.gridWidth; y++)
				window.draw(map.map[x][y]->sprite);

		window.draw(mainPlayer.getModel());

		listSpawner.draw(window, mainPlayer, mainView.getCenter().y);

		window.setView(window.getDefaultView());

		// Score Text
		scoreText.setText("Score: " + to_string(mainPlayer.calculateScore()));
		window.draw(scoreText.getText());

		window.display();
	}

	return 0;
}
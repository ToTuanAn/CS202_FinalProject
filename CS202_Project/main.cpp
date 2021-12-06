#include "Collision.h"
#include "Enemy.h"
#include "GameTile.h"
#include "GameWorld.h"
#include "ListSpawner.h"
#include "Menu.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "Spawner.h"
#include <iostream>
using namespace sf;
using namespace std;

const int WIDTH = 960;
const int HEIGHT = 992;

int main()
{
	float dt;
	Clock dt_clock;

	//MENU
	RenderWindow MENU(sf::VideoMode(WIDTH, HEIGHT), "CROSSY ROAD GROUP 10");
	Menu menu(MENU.getSize().x, MENU.getSize().y);
	MENU.setFramerateLimit(60);
	menu.show(MENU);

	//GAME
	RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "CROSSY ROAD GROUP 10");
	window.setFramerateLimit(30);
	Player mainPlayer;
	GameWorld map = GameWorld();
	View mainview;
	mainview.setSize(WIDTH, HEIGHT);
	mainview.setCenter(mainPlayer.getBody().getPosition() - Vector2f(0, 368));
	ListSpawner listSpawner(map.terrainSpawn);
	Collision collision;

	// Score Text
	const string SCORE_TEXT = "Score: ";

	Font scoreTextFont;
	if (!scoreTextFont.loadFromFile("PixelFont.ttf"))
	{
		cout << "Can't load font!\n";
		return 0;
	}
	else
		cout << "PixelFont.ttf is loaded!\n";

	Text scoreText;
	scoreText.setCharacterSize(50);
	scoreText.setFont(scoreTextFont);
	scoreText.setFillColor(Color::Red);
	scoreText.setOutlineColor(Color::Blue);
	scoreText.setOutlineThickness(2);
	scoreText.setStyle(Text::Bold);
	scoreText.setOrigin(scoreText.getGlobalBounds().width - (WIDTH / 2 - 75), scoreText.getGlobalBounds().height / 2);

	while (window.isOpen())
	{
		dt = dt_clock.restart().asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		//Update
		mainPlayer.update(dt);
		listSpawner.update(dt, mainPlayer, mainview.getCenter().y);
		mainview.move(Vector2f(0.f, -2.f));

		// Collision
		collision.UpdateCollision(mainPlayer, listSpawner);

		window.clear();
		//Draw
		window.setView(mainview);
		for (int x = 0; x < map.offset; x++)
		{
			for (int y = 0; y < map.gridWidth; y++)
			{
				window.draw(map.map[x][y]->sprite);
			}
		}

		window.draw(mainPlayer.getModel());
		listSpawner.draw(window, mainPlayer, mainview.getCenter().y);
		//Draw UI

		window.setView(window.getDefaultView());

		// Score Text
		scoreText.setString(SCORE_TEXT + to_string(mainPlayer.calculateScore()));
		window.draw(scoreText);

		window.display();
	}

	return 0;
}
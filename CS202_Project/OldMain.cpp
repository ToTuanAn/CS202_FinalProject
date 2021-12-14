// #include "Enemy.h"
// #include "GameTile.h"
// #include "GameWorld.h"
// #include "ListSpawner.h"
// #include "Menu.h"
// #include "Player.h"
// #include "Spawner.h"

// #include "SFML/Audio.hpp"
// #include "SFML/Graphics.hpp"
// #include "SFML/System.hpp"
// #include "SFML/Window.hpp"

// #include <iostream>

// using namespace sf;
// using namespace std;

// int main()
// {
// 	float dt;
// 	Clock dt_clock;

// 	// Menu
// 	RenderWindow MENU(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "CROSSY ROAD GROUP 10");
// 	Menu menu(MENU.getSize().x, MENU.getSize().y);
// 	MENU.setFramerateLimit(60);
// 	menu.show(MENU);

// 	// Window
// 	RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "CROSSY ROAD GROUP 10");
// 	window.setFramerateLimit(30);

// 	// Map
// 	GameWorld map = GameWorld();

// 	// Spawners
// 	ListSpawner listSpawner;
// 	listSpawner.setup(map.getLanes());

// 	// Player
// 	Player mainPlayer;

// 	// Main view
// 	View mainView;
// 	mainView.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
// 	mainView.setCenter(mainPlayer.getBody().getPosition() - Vector2f(0, 368));

// 	// Score Text
// 	const string SCORE_TEXT = "Score: ";
// 	const string FONT_NAME = "PixelFont";
// 	string FONT_FILE_NAME = FONT_NAME + ".ttf";

// 	Font scoreTextFont;
// 	if (!scoreTextFont.loadFromFile("Fonts/" + FONT_FILE_NAME))
// 	{
// 		cout << "Can't load " + FONT_FILE_NAME << endl;
// 		return 0;
// 	}
// 	else
// 		cout << FONT_FILE_NAME + " is loaded!\n";

// 	Text scoreText;
// 	scoreText.setCharacterSize(50);
// 	scoreText.setFont(scoreTextFont);
// 	scoreText.setFillColor(Color::Red);
// 	scoreText.setOutlineColor(Color::Blue);
// 	scoreText.setOutlineThickness(2);
// 	scoreText.setStyle(Text::Bold);
// 	scoreText.setOrigin(scoreText.getGlobalBounds().width - (SCREEN_WIDTH / 2 - 75), scoreText.getGlobalBounds().height / 2);

// 	// Sound
// 	const string GAME_MUSIC_NAME = "GameMusic";
// 	string GAME_MUSIC_FILE_NAME = GAME_MUSIC_NAME + ".wav";

// 	SoundBuffer gameMusicBuffer;
// 	if (!gameMusicBuffer.loadFromFile("Sounds/" + GAME_MUSIC_FILE_NAME))
// 	{
// 		cout << "Can't load " + GAME_MUSIC_FILE_NAME << endl;
// 		return 0;
// 	}
// 	else
// 		cout << GAME_MUSIC_FILE_NAME + " is loaded!\n";

// 	Sound gameMusic;
// 	gameMusic.setBuffer(gameMusicBuffer);
// 	gameMusic.setLoop(true);
// 	gameMusic.play();

// 	while (window.isOpen())
// 	{
// 		dt = dt_clock.restart().asSeconds();
// 		Event event;
// 		while (window.pollEvent(event))
// 		{
// 			if (event.type == Event::Closed)
// 				window.close();
// 		}

// 		// Update
// 		listSpawner.update(dt, mainPlayer, mainView.getCenter().y);
// 		mainView.move(Vector2f(0.f, -CAMERA_SPEED));
// 		mainPlayer.setBound(mainView.getCenter());
// 		mainPlayer.update(dt);

// 		if (listSpawner.isCollidedWithPlayer(mainPlayer))
// 		{
// 			cout << "Player is dead!\n";
// 		}

// 		// Draw
// 		window.clear();
// 		window.setView(mainView);

// 		for (int x = 0; x < OFFSET; x++)
// 			for (int y = 0; y < GRID_WIDTH; y++)

// 				window.draw(map.tiles[x][y]->getSprite());

// 		window.draw(mainPlayer.getModel());

// 		listSpawner.draw(window, mainPlayer, mainView.getCenter().y);

// 		window.setView(window.getDefaultView());

// 		// Score Text
// 		scoreText.setString(SCORE_TEXT + to_string(mainPlayer.getScore()));
// 		window.draw(scoreText);
// 		cout << scoreText.getGlobalBounds().width << " " << scoreText.getGlobalBounds().height << endl;
// 		cout << scoreText.getPosition().x << " " << scoreText.getPosition().y << endl
// 			 << endl;
// 		window.display();
// 	}

// 	return 0;
// }
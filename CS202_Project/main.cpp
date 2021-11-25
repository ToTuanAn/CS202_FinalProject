#include "Enemy.h"
#include "GameTile.h"
#include "GameWorld.h"
#include "ListSpawner.h"
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
    RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "CROSSY ROAD GROUP 10");
    window.setFramerateLimit(60);

    Player mainPlayer;
    GameWorld map = GameWorld();
    View mainview;
    mainview.setSize(WIDTH, HEIGHT);
    mainview.setCenter(mainPlayer.getBody().getPosition());
    ListSpawner listSpawner;

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
        listSpawner.update(dt, mainPlayer);
        mainview.move(Vector2f(0.f, -1.f));

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
        //window.draw(mainPlayer.getBody());
        window.draw(mainPlayer.getModel());
        listSpawner.draw(window, mainPlayer);
        //Draw UI
        window.setView(window.getDefaultView());

        window.display();
    }

    return 0;
}
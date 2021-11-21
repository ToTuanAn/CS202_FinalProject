#include<iostream>
#include"Player.h"
#include"GameTile.h"
#include"GameWorld.h"
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"


using namespace sf;
using namespace std;

int main() {
    float dt; Clock dt_clock;
    RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "CROSSY ROAD GROUP 10");
    window.setFramerateLimit(60);
    Player mainPlayer;
    GameWorld map = GameWorld();
    View mainview;
    mainview.setSize(WIDTH, HEIGHT);


    
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
        //mainview.setCenter(mainPlayer.playerBoxDisplay());

        window.clear();
        //Draw UI
        window.setView(window.getDefaultView());
        for (int x = 0; x < map.gridHeight; x++) {
            for (int y = 0; y < map.gridWidth; y++) {
                window.draw(map.map[x][y]->sprite);
            }
        }
        
        //Draw
        window.setView(mainview);
        
        window.draw(mainPlayer.playerBoxDisplay());

        window.display();
    }

    return 0;
}
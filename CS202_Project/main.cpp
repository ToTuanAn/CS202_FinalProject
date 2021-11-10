#include<iostream>
#include"cPlayer.h"
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"

const int WIDTH = 960;
const int HEIGHT = 1000;

using namespace sf;
using namespace std;

int main() {
    float dt; Clock dt_clock;
    RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "CROSSY ROAD GROUP 10");
    window.setFramerateLimit(60);

    Player mainPlayer;
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
        mainPlayer.movement(dt);

        //Draw
        window.clear();
        window.draw(mainPlayer.playerBoxDisplay());

        window.display();
    }

    return 0;
}
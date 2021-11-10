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
    RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "CROSSY ROAD GROUP 10");
    window.setFramerateLimit(60);

    Player mainPlayer;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        //Update


        //Draw
        window.clear();
        window.draw(mainPlayer.playerBoxDisplay());

        window.display();
    }

    return 0;
}
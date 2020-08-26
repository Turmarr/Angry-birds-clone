#include <SFML/Graphics.hpp>
#include "Box2D/box2d/box2d.h"
#include <iostream>
#include "Normal.hpp"
#include "Bomb.hpp"
#include "Speed.hpp"
#include "Highscores.hpp"

int scale = 30;

int main()
{

	Highscores h1(800, 600);

    h1.updateHighscores("/Users/henrivalimaki/Desktop/Yliopisto/C++/angry-birds-2020-3/build/Highscores.txt", 300);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Testi");
	window.setFramerateLimit(60);


    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }

            h1.updateEvent(event);
        }

        window.clear();
        
		h1.drawInputBox(window);

        window.display();
    }

    return 0;
}

#include <SFML/Graphics.hpp>
#include "Box2D/box2d/box2d.h"
#include <iostream>
#include "Normal.hpp"
#include "Bomb.hpp"
#include "Speed.hpp"
#include "Highscores.hpp"
#include "Scoreboard.hpp"

int scale = 30;

int main()
{

    Scoreboard s1(800, 600);
    s1.setScoreTexts();

    sf::RenderWindow window(sf::VideoMode(800, 600), "Testi");
	window.setFramerateLimit(60);


    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }

        }

        window.clear();
        
		s1.Draw(window);

        window.display();
    }

	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.

	return 0;
}
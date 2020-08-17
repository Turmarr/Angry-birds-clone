#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "level.hpp"

int main(){


    Level test("LeveLs/test.txt");

    sf::RenderWindow window(sf::VideoMode(800, 600), "Testing for enemies");
    
    window.setFramerateLimit(60);
    //Bird bird = Bird(100.f, 100.f);
    

    //Game loop
    while (window.isOpen()){
        sf::Event ev;
        while(window.pollEvent(ev))
        {
            switch (ev.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                
            }
        }
        
        /*
        window.clear(sf::Color::White);
        sf::RectangleShape ground { { 800, 16 } };
        ground.setOrigin(400.0f, 8.0f);
        ground.setPosition(200, 400);
        ground.setRotation(0);
        ground.setFillColor(sf::Color::Red);
        window.draw(ground);
        */
        test.Update(window);
        //window.display();

    }

    return 0;
}
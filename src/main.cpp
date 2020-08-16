#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "level.hpp"

int main(){

    Level test("test.txt");

    sf::RenderWindow window(sf::VideoMode(800, 600), "Testing for enemies", sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev;
    window.setFramerateLimit(60);
    //Bird bird = Bird(100.f, 100.f);
    

    //Game loop
    while (window.isOpen()){

        while(window.pollEvent(ev))
        {
            switch (ev.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                
            }
        }

    //Update
    test.Update(window);


    }

    return 0;
}
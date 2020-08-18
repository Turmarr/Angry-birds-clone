#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "MainMenu.hpp"
#include <iostream>

int main(){

    sf::RenderWindow window(sf::VideoMode(800, 600), "Vengeful Pigs", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Event ev;
    Menu menu(window.getSize().x, window.getSize().y);

    int options;

    while(window.isOpen()){

        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            
            case sf::Keyboard::Escape:
                window.close();
                break;
            
            case sf::Event::KeyReleased:
                switch (ev.key.code)
                {
                    case sf::Keyboard::Down:
                        menu.moveDown();
                        break;
                    
                    case sf::Keyboard::Up:
                        menu.moveUp();
                        break;

                    case sf::Keyboard::Return:
                        options = menu.returnSelectedItem();
                        switch (options)
                        {
                            case 0:
                                std::cout<< "Possible gameplay here" << std::endl;
                                break;
                            
                            case 1:
                                std::cout<< "Possible highscores here" << std::endl;
                                break;

                            case 2:
                                window.close();
                                break;
                            
                            default:
                                break;
                        }
                 
                    default:
                        break;
                    }

            default:
                break;
            }
        }
    
    window.clear();

    menu.Draw(window);

    window.display();

    }

    

    return 0;
}
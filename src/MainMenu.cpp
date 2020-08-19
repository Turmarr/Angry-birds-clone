#include "MainMenu.hpp"
#include <iostream>

Menu::Menu(float width, float height)
{
    initFonts();
    initTexture();
    initBackground();

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Blue);
    menu[0].setOutlineColor(sf::Color::Black);
    menu[0].setOutlineThickness(1.f);
    menu[0].setString("Play");
    menu[0].setCharacterSize(40);
    menu[0].setOrigin(menu[0].getLocalBounds().width/2, menu[0].getLocalBounds().height/2);
   
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setOutlineColor(sf::Color::Black);
    menu[1].setOutlineThickness(1.f);
    menu[1].setString("Highscores");
    menu[1].setCharacterSize(40);
    menu[1].setOrigin(menu[1].getLocalBounds().width/2, menu[1].getLocalBounds().height/2);
   
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setOutlineColor(sf::Color::Black);
    menu[2].setOutlineThickness(1.f);
    menu[2].setString("Exit");
    menu[2].setCharacterSize(40);
    menu[2].setOrigin(menu[2].getLocalBounds().width/2, menu[2].getLocalBounds().height/2);
    
    menu[0].setPosition((int) width/2, 200);
    menu[1].setPosition((int) width/2, 300);
    menu[2].setPosition((int) width/2, 400);

    selectedItemIndex = 0;

}

Menu::~Menu()
{

}

void Menu::initFonts(){

    if(!font.loadFromFile("Fonts/test2.ttf")){
        std::cout<< "Error while loading menu font."<<std::endl;
    }
}

void Menu::initTexture(){

    if(!this->background.loadFromFile("Textures/sky.jpg")){
        std::cout<< "Failed to load menu background." << std::endl;
    }
}

void Menu::initBackground(){

    rect.setTexture(&this->background);
    rect.setSize(sf::Vector2f(800, 600));

}

void Menu::Draw(sf::RenderWindow& window){

    window.draw(rect);

    for (int i = 0; i< 3; i++){
        window.draw(menu[i]);
    }

}

void Menu::moveUp(){

    if (selectedItemIndex -1 >= 0){
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Blue);
    }
}

void Menu::moveDown(){
    
    if (selectedItemIndex +1 < 3){
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Blue);
    }
}

int Menu::updateMenuEvent(sf::Event& ev, sf::RenderWindow& window){

    switch (ev.type){

        case sf::Event::Closed:
            return 3;
            break;

        case sf::Keyboard::Escape:
            return 3;
            break;

        case sf::Event::KeyReleased:
            switch (ev.key.code){

                case sf::Keyboard::Down:
                    this->moveDown();
                    break;
                
                case sf::Keyboard::Up:
                    this->moveUp();
                    break;

                case sf::Keyboard::Return:
                    
                    options_ = this->returnSelectedItem();

                    switch (options_){

                        case 0:
                            std::cout<< "Possible gameplay here" << std::endl;
                            break;
                        
                        case 1:
                            std::cout<< "Possible highscores here" << std::endl;
                            break;

                        case 2:
                            return 3;
                            break;
                        
                        default:
                            break;
                    }

                default:
                    break;
            }
        case sf::Event::MouseButtonPressed:

            if (ev.mouseButton.button == sf::Mouse::Left){

                if (mouseHeld == false){

                    mouseHeld = true;
                    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePosWindow);
                
                    for (int i = 0; i <3; i++){
                        
                        if(menu[i].getGlobalBounds().contains(mousePosView)){
                            
                            return (i+1);
                            }
                        }
                }
            }
            break;
    
    }

    mouseHeld = false;

    return 0;
}
#include "MainMenu.hpp"
#include <iostream>

Menu::Menu(float width, float height)
{
    width_ = width;
    height_ = height;

    initFonts();
    initTexture();
    initBackground();

    menu[0].setString("Play");
    menu[1].setString("Highscores");
    menu[2].setString("Exit");

    for (int i = 0; i < 3; i++){

        menu[i].setFont(font);
        menu[i].setFillColor(sf::Color::White);
        menu[i].setOutlineColor(sf::Color::Black);
        menu[i].setOutlineThickness(2.f);
        menu[i].setCharacterSize(60);
        menu[i].setOrigin(menu[i].getLocalBounds().width/2, menu[i].getLocalBounds().height/2);
        
    }

    int x = width_/2;
    int y = height_/2;

    //Play button attributes
    menu[0].setFillColor(sf::Color::Blue);
    menu[0].setCharacterSize(70);
    menu[0].setPosition(x, y - 150);

    //Highscore button position
    menu[1].setPosition(x+10, y);

    //Exit button position
    menu[2].setPosition(x-5, y + 150);


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

    if(!this->background.loadFromFile("Textures/sky.png")){
        std::cout<< "Failed to load menu background." << std::endl;
    }
}

void Menu::initBackground(){

    rect.setTexture(&this->background);
    rect.setSize(sf::Vector2f(width_, height_));

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
        menu[selectedItemIndex].setCharacterSize(55);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Blue);
        menu[selectedItemIndex].setCharacterSize(65);
    }
}

void Menu::moveDown(){
    
    if (selectedItemIndex +1 < 3){
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        menu[selectedItemIndex].setCharacterSize(55);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Blue);
        menu[selectedItemIndex].setCharacterSize(65);
    }
}
//movement in the Main Menu screen
int Menu::updateMenuEvent(sf::Event& ev, sf::RenderWindow& window){

    switch (ev.type){

        case sf::Event::Closed:
            return 3;
            break;
            
        case sf::Event::KeyReleased:

            switch (ev.key.code){
                
                case sf::Keyboard::Escape:
                    return 3;
                    break;

                case sf::Keyboard::Down:
                    this->moveDown();
                    break;
                
                case sf::Keyboard::Up:
                    this->moveUp();
                    break;

                case sf::Keyboard::Return:
                    
                    options_ = this->returnSelectedItem();
                    return (options_ +1);
                    break;

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

        default:
            break;
    }

    mouseHeld = false;

    return 0;
}
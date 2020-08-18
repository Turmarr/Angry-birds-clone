#include "MainMenu.hpp"
#include <iostream>

Menu::Menu(float width, float height)
{
    initFonts();

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Blue);
    menu[0].setString("Play");
    menu[0].setCharacterSize(35);
    menu[0].setOrigin(menu[0].getLocalBounds().width/2, menu[0].getLocalBounds().height/2);
   
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Highscores");
    menu[1].setCharacterSize(35);
    menu[1].setOrigin(menu[1].getLocalBounds().width/2, menu[1].getLocalBounds().height/2);
   
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Exit");
    menu[2].setCharacterSize(35);
    menu[2].setOrigin(menu[2].getLocalBounds().width/2, menu[2].getLocalBounds().height/2);
    
    menu[0].setPosition((int) width/2, height/(3+1)*1);
    menu[1].setPosition((int) width/2, height/(3+1)*2);
    menu[2].setPosition((int) width/2, height/(3+1)*3);

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

void Menu::Draw(sf::RenderWindow& window){

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

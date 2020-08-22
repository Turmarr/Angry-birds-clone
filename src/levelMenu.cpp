#include "levelMenu.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

levelMenu::levelMenu(float width, float height)
{
    height_ = height;
    width_ = width;

    initFonts();
    initTexture();
    initBackground();
    initTexts();
    initStars();
    updateStars();

    menu[0].setString("1");
    menu[1].setString("2");
    menu[2].setString("3");
    
    for (int i = 0; i < 3; i++){

        menu[i].setFont(font);
        menu[i].setFillColor(sf::Color::White);
        menu[i].setOutlineColor(sf::Color::Black);
        menu[i].setOutlineThickness(2.f);
        menu[i].setCharacterSize(50);
        menu[i].setOrigin(menu[i].getLocalBounds().width/2, menu[i].getLocalBounds().height/2);
    }
    int x = width_/2;
    int y = height_/2 - 50;

    //Level 1 button
   
    menu[0].setPosition(x - 250, y);
    menu[0].setCharacterSize(60);
    menu[0].setFillColor(sf::Color::Blue);

    //Level 2 button
    menu[1].setPosition(x, y);
   
    //Level 3 button
    
    menu[2].setPosition(x + 250, y);

    selectedItemIndex = 0;

}

levelMenu::~levelMenu()
{

}

void levelMenu::initFonts(){

    if(!font.loadFromFile("Fonts/test2.ttf")){
        std::cout<< "Error while loading menu font."<<std::endl;
    }

}

void levelMenu::initTexture(){

    if(!this->background.loadFromFile("Textures/sky.jpg")){
        std::cout<< "Failed to load menu background." << std::endl;
    }
    if(!this->imag.loadFromFile("Textures/star.png")){
        std::cout<< "Failed to load escape button image." << std::endl;
    }

}

void levelMenu::initBackground(){

    rect.setTexture(&this->background);
    rect.setSize(sf::Vector2f(width_, height_));

}
//Settings for texts
void levelMenu::initTexts(){

    toMenu.setFont(font);
    toMenu.setString("press ESC ro return");
    toMenu.setFillColor(sf::Color::White);
    toMenu.setCharacterSize(20);
    toMenu.setOrigin(toMenu.getLocalBounds().width/2, toMenu.getLocalBounds().height/2);
    toMenu.setPosition(120.f, 20.f);

    levels.setFont(font);
    levels.setString("Levels");
    levels.setFillColor(sf::Color::White);
    levels.setOutlineColor(sf::Color::Black);
    levels.setOutlineThickness(1.f);
    levels.setCharacterSize(60);
    levels.setOrigin(levels.getLocalBounds().width/2, levels.getLocalBounds().height/2);
    levels.setPosition((int) width_/2, 50.f);


}
//Settings for star-sprites
void levelMenu::initStars(){

    int y = 400;
    int x = 180;
    int count = 0;

    for (int i = 0; i <9; i++){

        if (count == 3){
            x += 40;
            count = 0;
        }

        star.setTexture(imag);
        star.setScale(sf::Vector2f(0.3f, 0.3f));
        star.setColor(sf::Color(0,0,0, 60));
        star.setOrigin(star.getLocalBounds().width/2, star.getLocalBounds().height/2);
        star.setPosition(x, y);
        x += 70;
        count++;
        stars.push_back(star);
    }

}

void levelMenu::Draw(sf::RenderWindow& window){

    window.draw(rect);
    window.draw(toMenu);
    window.draw(levels);

    for (int i = 0; i< 3; i++){
        window.draw(menu[i]);
    }
    for (auto i : stars){
        window.draw(i);
    }

}

void levelMenu::moveLeft(){

    if (selectedItemIndex -1 >= 0){
        menu[selectedItemIndex].setCharacterSize(50);
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setCharacterSize(60);
        menu[selectedItemIndex].setFillColor(sf::Color::Blue);
    }
}

void levelMenu::moveRight(){
    
    if (selectedItemIndex +1 < 3){
        menu[selectedItemIndex].setCharacterSize(50);
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setCharacterSize(60);
        menu[selectedItemIndex].setFillColor(sf::Color::Blue);
    }
}
//level chooser input
int levelMenu::updateMenuEvent(sf::Event& ev, sf::RenderWindow& window){

    switch (ev.type){

        case sf::Event::Closed:
            return 3;
            break;

        case sf::Event::KeyReleased:

            switch (ev.key.code){

                case sf::Keyboard::Escape:
                    return 0;
                    break;

                case sf::Keyboard::Left:
                    this->moveLeft();
                    break;
                
                case sf::Keyboard::Right:
                    this->moveRight();
                    break;

                case sf::Keyboard::Return:
                    
                    options_ = this->returnSelectedItem();
                    return (options_ + 4);
                    break;
                    /*switch (options_){

                        case 0:
                            std::cout<< "Level 1" << std::endl;
                            return 4;
                            break;
                        
                        case 1:
                            std::cout<< "Level 2" << std::endl;
                            return 5;
                            break;

                        case 2:
                            std::cout<< "Level 3" << std::endl;
                            return 6;
                            break;
                        
                        default:
                            break;*/
                    
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

    return 1;
}
//Setting stars to non-transparent
void levelMenu::updateStars(){
    
    std::ifstream is("stars.txt");
    int level, no;

    if(is.rdstate() & (is.failbit | is.badbit)){
        std::cerr << "Failed to load file stars.txt" << std::endl;
    }
    for (int i = 0; i<3; i++){

        std::string line;
        std::getline(is, line);

        std::stringstream ss;
        ss.str(line);
        ss >> level >> no;

        for (int j = 0; j < no; j++){
            if (level == 2){
                stars[j+3].setColor(sf::Color::White);
            }
            if (level == 3){
                stars[j+6].setColor(sf::Color::White);
            }
            else
            {
                stars[j].setColor(sf::Color::White);
            }
        } 
    }

}
#include "Highscores.hpp"
#include <iostream>

//Function that defines sorting criteria
bool higherScore(std::pair<std::string, int> a, std::pair<std::string, int> b){
    return a.second > b.second;
}

Highscores::Highscores(float width, float height){
    width_ = width;
    height_ = height;

    initFonts();
    initTexture();
    initBackground();

    for(int i = 0; i < 4; i++){
        texts[i].setFont(font);
        texts[i].setFillColor(sf::Color::White);
        texts[i].setOutlineColor(sf::Color::Black);
        texts[i].setOutlineThickness(2.f);
    }

    box.setSize(sf::Vector2f(300, 300));
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2.f);
    box.setOrigin(box.getLocalBounds().width / 2, box.getLocalBounds().height / 2);
    box.setPosition(width_ / 2, height_ / 2);

    texts[0].setString("New highscore!");
    texts[0].setCharacterSize(20);
    texts[0].setOrigin(texts[0].getLocalBounds().width/2, texts[0].getLocalBounds().height/2);
    texts[0].setPosition(box.getPosition().x, box.getGlobalBounds().top + 50);

    texts[1].setString("Enter your name");
    texts[1].setCharacterSize(15);
    texts[1].setOrigin(texts[1].getLocalBounds().width/2, texts[1].getLocalBounds().height/2);
    texts[1].setPosition(box.getPosition().x, box.getGlobalBounds().top + 125);

    texts[2].setString("Max 10 characters");
    texts[2].setCharacterSize(10);
    texts[2].setOrigin(texts[2].getLocalBounds().width/2, texts[2].getLocalBounds().height/2);
    texts[2].setPosition(box.getPosition().x, box.getGlobalBounds().top + 150);

    inputBox.setSize(sf::Vector2f(box.getLocalBounds().width - 50, 50));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2.f);
    inputBox.setOrigin(inputBox.getLocalBounds().width / 2, inputBox.getLocalBounds().height / 2);
    inputBox.setPosition(box.getPosition().x, box.getGlobalBounds().top + 225);


}

void Highscores::initFonts(){

    if(!font.loadFromFile("/Users/henrivalimaki/Desktop/Yliopisto/C++/angry-birds-2020-3/build/Fonts/test2.ttf")){
        std::cout<< "Error while loading menu font."<<std::endl;
    }
}

void Highscores::initTexture(){

    if(!this->background.loadFromFile("/Users/henrivalimaki/Desktop/Yliopisto/C++/angry-birds-2020-3/build/Textures/sky.png")){
        std::cout<< "Failed to load menu background." << std::endl;
    }
}

void Highscores::initBackground(){

    rect.setTexture(&this->background);
    rect.setSize(sf::Vector2f(width_, height_));
}

bool Highscores::Read(std::string filename){

    currentHighscores.clear();

    std::ifstream file(filename);

    if(!file.is_open()){
        std::cout << "Failed to open highscores file." << std::endl;
        return false;
    }

    std::string name;
    int points;

    while(file >> name >> points){
        currentHighscores.emplace_back(name, points);
    }

    //Sort the list
    std::sort(currentHighscores.begin(), currentHighscores.end(), higherScore);

    //Make sure it's not longer than max size
    while(currentHighscores.size() > maxSize){
        currentHighscores.pop_back();
    }

    file.close();
    return true;
}

bool Highscores::Write(std::string filename){

    std::sort(currentHighscores.begin(), currentHighscores.end(), higherScore);

    std::ofstream file(filename);

    if(!file.is_open()){
        std::cout << "Failed to open highscores file." << std::endl;
        return false;
    }

    for(auto i : currentHighscores){
        file << i.first << " " << i.second << std::endl;
    }

    file.close();
    return true;
}

bool Highscores::updateHighscores(std::string filename, int points){

    //Check if reading was unsuccesful
    if(!Read(filename)){
        return false;
    }

    std::sort(currentHighscores.begin(), currentHighscores.end(), higherScore);

    currentPoints = points;
    currentFileName = filename;

    //Returns true if points > last member of highscores
    if (points > currentHighscores.back().second){
        draw = true;
        return true;
    }
    else{
        return false;
    }
}

state Highscores::updateEvent(sf::Event& event){

    options_.i = 2;

    switch (event.type)
    {
    case sf::Event::Closed:
        options_.i = 3;
        return options_;
        break;

    case sf::Event::KeyReleased:
        if(event.key.code == sf::Keyboard::Escape){
            options_.i = 0;
        }
        return options_;
        break;
    
    default:
        return options_;
        break;
    }
}

bool Highscores::updateUserInput(sf::Event& event){

    if(event.type == sf::Event::TextEntered){
        if(event.text.unicode == 10){   //Return key
            currentHighscores.emplace_back(userInput, currentPoints);
            std::sort(currentHighscores.begin(), currentHighscores.end(), higherScore);
            currentHighscores.pop_back();
            this->Write(currentFileName);
            return false;
        }

        else if(event.text.unicode == 8){   //Backspace key
            userInput.pop_back();
        }

        else if(event.text.unicode < 128){
            if(userInput.length() <= maxInputSize){
                userInput += event.text.unicode;
            }
        }
    }
    return true;
}

void Highscores::drawInputBox(sf::RenderWindow& window){

    if(!draw){
        return;
    }

    texts[3].setString(userInput);
    texts[3].setCharacterSize(30);
    texts[3].setOrigin(texts[3].getLocalBounds().width/2, texts[3].getLocalBounds().height/2);
    texts[3].setPosition(inputBox.getPosition().x, inputBox.getGlobalBounds().top + 20);


    window.draw(rect);
    window.draw(box);
    window.draw(texts[0]);
    window.draw(texts[1]);
    window.draw(texts[2]);
    window.draw(inputBox);
    window.draw(texts[3]);
}
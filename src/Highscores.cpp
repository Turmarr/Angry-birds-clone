#include "Highscores.hpp"
#include <iostream>

//Function that defines sorting criteria
bool higherScore(std::pair<std::string, int>& a, std::pair<std::string, int>& b){
    return a.second > b.second;
}

Highscores::Highscores(float width, float height){
    width_ = width;
    height_ = height;
    enter = false;
    backtrack = false;

    initFonts();
    initTexture();
    initBackground();
    initInputBox();

    texts[0].setString("New highscore!");
    texts[1].setString("Enter your name");
    texts[2].setString("Max 10 characters");
    texts[4].setString("Press Enter to save");


    for(int i = 0; i < 5; i++){
        texts[i].setFont(font);
        texts[i].setFillColor(sf::Color::White);
        texts[i].setOutlineColor(sf::Color::Black);
        texts[i].setOrigin(texts[i].getLocalBounds().width/2, texts[i].getLocalBounds().height/2);
        texts[i].setOutlineThickness(2.f);
    }
    
    texts[0].setCharacterSize(30);
    texts[0].setPosition(box.getPosition().x, box.getGlobalBounds().top + 50);
    
    texts[1].setCharacterSize(20);
    texts[1].setPosition(box.getPosition().x+30, box.getGlobalBounds().top + 130);

    texts[2].setCharacterSize(20);
    texts[2].setPosition(box.getPosition().x+30, box.getGlobalBounds().top + 165);

    texts[4].setCharacterSize(20);
    texts[4].setPosition(box.getPosition().x+30, inputBox.getGlobalBounds().top + 70);


}

void Highscores::initFonts(){

    if(!font.loadFromFile("../src/Fonts/test2.ttf")){
        std::cout<< "Error while loading menu font."<<std::endl;
    }
}

void Highscores::initTexture(){

    if(!this->background.loadFromFile("../src/Textures/sky.png")){
        std::cout<< "Failed to load menu background." << std::endl;
    }
}

void Highscores::initBackground(){

    rect.setTexture(&this->background);
    rect.setSize(sf::Vector2f(width_, height_));
}
void Highscores::initInputBox(){

    box.setSize(sf::Vector2f(300, 300));
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2.f);
    box.setOrigin(box.getLocalBounds().width / 2, box.getLocalBounds().height / 2);
    box.setPosition(width_ / 2, height_ / 2);

    inputBox.setSize(sf::Vector2f(box.getLocalBounds().width - 50, 50));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2.f);
    inputBox.setOrigin(inputBox.getLocalBounds().width / 2, inputBox.getLocalBounds().height / 2);
    inputBox.setPosition(box.getPosition().x, box.getGlobalBounds().top + 225);

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

    //Check if unsuccesful
    if(!file){
        return false;
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

    userInput.clear();
    
    
    //Returns true if points > last member of highscores
    if (points > currentHighscores[maxSize - 1].second){
        return true;
    }
    else{
        return false;
    }
}

state Highscores::updateEvent(sf::Event& event){    

    switch (event.type)
    {
    case sf::Event::KeyPressed:
        switch (event.key.code)
        {
        case sf::Keyboard::Return:
            if (enter == false){
                currentHighscores.emplace_back(userInput, currentPoints);
                std::sort(currentHighscores.begin(), currentHighscores.end(), higherScore);
                currentHighscores.pop_back();
                this->Write(currentFileName);
                enter = true;
            }
            break;

        default:
            break;
        }
        break;
    case sf::Event::TextEntered:

        //If enter key actually worked
        /*if(event.text.unicode == '\n'){
            std::cout << "Enter pressed" << std::endl;
            currentHighscores.emplace_back(userInput, currentPoints);
            std::sort(currentHighscores.begin(), currentHighscores.end(), higherScore);
            currentHighscores.pop_back();
            this->Write(currentFileName);
            options_.i = 1;
            return options_;
        }*/

        if(event.text.unicode == '\b'){
            if(userInput.size() > 0){
                userInput.pop_back();
            }
        }

        else if(event.text.unicode < 128){
            if(userInput.length() <= maxInputSize && isalpha(event.text.unicode)){
                //std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
                userInput += event.text.unicode;
                
            }
        }

        break;
    
    case sf::Event::Closed:
        options_.i = 3;
        return options_;
        break;

    case sf::Event::KeyReleased:
        
        switch (event.key.code)
        {    
            case sf::Keyboard::Escape:
                options_.i = 0;
                return options_;
                break;

            case sf::Keyboard::Return:
                options_.i = 1;
                enter = false;
                return options_;
                break;
        
            default:
                break;
        
        }
        
    default:
        break;
    }
    options_.i = 6;
    return options_;
}
void Highscores::updateInputBox(){
    
    texts[3].setString(userInput);
    texts[3].setCharacterSize(30);
    texts[3].setOrigin(texts[3].getLocalBounds().width/2, texts[3].getLocalBounds().height/2);
    texts[3].setPosition(inputBox.getPosition().x, inputBox.getGlobalBounds().top + 20);

}
void Highscores::drawInputBox(sf::RenderWindow& window){

    window.draw(rect);
    window.draw(box);
    window.draw(inputBox);
    updateInputBox();
    
    for (int i = 0; i < 5; i++){
        window.draw(texts[i]);
    }
}
#include "Scoreboard.hpp"
#include <iostream>

Scoreboard::Scoreboard(float width, float height){
    width_ = width;
    height_ = height;

    initFonts();
    initTexture();
    initBackground();

    for(int i = 0; i < 4; i++){
        headers[i].setFont(font);
        headers[i].setFillColor(sf::Color::White);
        headers[i].setOutlineColor(sf::Color::Black);
        headers[i].setOutlineThickness(2.f);
    }

    button.setFont(font);
    button.setFillColor(sf::Color::Blue);
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(2.f);
    button.setString("Return to main menu");
    button.setCharacterSize(25);
    button.setOrigin(button.getLocalBounds().width/2, button.getLocalBounds().height/2);
    button.setPosition(width_ / 2, height_ - button.getLocalBounds().height - 30);


    for(int i = 0; i < 3; i++){
        box[i].setSize(sf::Vector2f((width_ - 100) / 3, height_ - 200));
        box[i].setFillColor(sf::Color::White);
        box[i].setOutlineColor(sf::Color::Black);
        box[i].setOutlineThickness(2.f);
        box[i].setOrigin(box[i].getLocalBounds().width / 2, box[i].getLocalBounds().height / 2);
        box[i].setPosition(25 * (i + 1) + (i * box[i].getLocalBounds().width) + (box[i].getLocalBounds().width / 2), height_ / 2);
    }


    headers[0].setString("Highscores");
    headers[0].setCharacterSize(30);
    headers[0].setOrigin(headers[0].getLocalBounds().width/2, headers[0].getLocalBounds().height/2);
    headers[0].setPosition(width_ / 2, 30);

    headers[1].setString("Level 1");
    headers[1].setCharacterSize(20);
    headers[1].setOrigin(headers[1].getLocalBounds().width/2, headers[1].getLocalBounds().height/2);
    headers[1].setPosition(box[0].getPosition().x, box[0].getGlobalBounds().top + 20);

    headers[2].setString("Level 2");
    headers[2].setCharacterSize(20);
    headers[2].setOrigin(headers[2].getLocalBounds().width/2, headers[2].getLocalBounds().height/2);
    headers[2].setPosition(box[1].getPosition().x, box[1].getGlobalBounds().top + 20);

    headers[3].setString("Level 3");
    headers[3].setCharacterSize(20);
    headers[3].setOrigin(headers[3].getLocalBounds().width/2, headers[3].getLocalBounds().height/2);
    headers[3].setPosition(box[2].getPosition().x, box[2].getGlobalBounds().top + 20);

}

void Scoreboard::setScoreTexts(){
    for(int i = 1; i <= 3; i++){
        std::string filename = "/Users/henrivalimaki/Desktop/Yliopisto/C++/angry-birds-2020-3/build/Highscores" + std::to_string(i) + ".txt";
        if(this->Read(filename)){
            for(int j = 0; j < currentHighscores.size(); j++){
                sf::Text name;
                sf::Text score;

                int y = ((box[i - 1].getLocalBounds().height) / (currentHighscores.size() + 1)) * (j + 1) + 100;

                name.setFont(font);
                name.setFillColor(sf::Color::White);
                name.setOutlineColor(sf::Color::Black);
                name.setOutlineThickness(2.f);
                name.setString(currentHighscores[j].first);
                name.setCharacterSize(15);
                name.setOrigin(0, name.getLocalBounds().height / 2);
                name.setPosition(box[i - 1].getGlobalBounds().left + 20, y);

                score.setFont(font);
                score.setFillColor(sf::Color::White);
                score.setOutlineColor(sf::Color::Black);
                score.setOutlineThickness(2.f);
                score.setString(std::to_string(currentHighscores[j].second));
                score.setCharacterSize(15);
                score.setOrigin(score.getLocalBounds().width, score.getLocalBounds().height / 2);
                score.setPosition(box[i - 1].getGlobalBounds().left + box[i - 1].getLocalBounds().width - 20, y);

                scores_.push_back(name);
                scores_.push_back(score);
            }
        }
    }
}

void Scoreboard::Draw(sf::RenderWindow& window){


    window.draw(rect);

    for(int i = 0; i < 3; i++){
        window.draw(box[i]);
    }

    for(int i = 0; i < 4; i++){
        window.draw(headers[i]);
    }

    window.draw(button);

    for(auto i : scores_){
        window.draw(i);
    }
}
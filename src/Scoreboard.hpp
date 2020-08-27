#pragma once
#include "Highscores.hpp"

class Scoreboard: public Highscores{

protected:
    
    //Texts needed
    sf::Text headers[4];
    sf::Text button;

    std::vector<sf::Text> scores_;

    //Boxes for highscorelists
    sf::RectangleShape box[3];

public:
    Scoreboard(float width, float height);
    ~Scoreboard(){}

    void Draw(sf::RenderWindow& window);

    void setScoreTexts();
};
#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "state.hpp"
#include "Highscores.hpp"

class Scoreboard {
private:

    state options_;

    int maxSize = 5;
    
    sf::Font font;

    //Texts needed
    sf::Text headers[4];
    sf::Text button;

    //Boxes for highscorelists
    sf::RectangleShape box[3];

    //Background
    sf::Texture background;
    sf::RectangleShape rect;

    //Size of the window
    float width_, height_;

    std::vector<sf::Text> scores_;

    //Temporary storage for highscores
    std::vector<std::pair<std::string, int>> currentHighscores;

    //Temporary storage for points to be added
    int currentPoints;

    //Temporary storage for current filename
    std::string currentFileName;

    //Storage for user input
    std::string userInput;

    int maxInputSize = 10;

    //Initializers
    void initFonts();
    void initTexture();
    void initBackground();

    //Reads highscores from file. Returns true if successful
    bool Read(std::string filename);

    //Writes highscores to file. Returns true if succesful
    bool Write(std::string filename);


public:

    //Constructor and destructor
   Scoreboard(float width, float height);
    ~Scoreboard(){}

    void Draw(sf::RenderWindow& window);

    void setScoreTexts();

    state updateEvent(sf::Event& event);

    friend bool higher(std::pair<std::string, int>& a, std::pair<std::string, int>& b);
};
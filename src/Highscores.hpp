#pragma once
#include "SFML/Graphics.hpp"
#include <fstream>
#include <string>
#include <vector>
#include "state.hpp"

class Highscores {
protected:

    state options_;

    bool draw = false;

    static const int maxSize = 5;
    
    sf::Font font;

    //Boxes where texts are displayed
    sf::RectangleShape box;
    sf::RectangleShape inputBox;

    //Highscores texts
    sf::Text texts[4];

    //Background
    sf::Texture background;
    sf::RectangleShape rect;

    //Size of the window
    float width_, height_;

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

    Highscores(){}

public:

    //Constructor and destructor
    Highscores(float width, float height);
    ~Highscores() {}

    //Gets events from Game class and changes state accordingly
    state updateEvent(sf::Event& event);

    //Checks if points get you onto highscore list. DON'T use in a loop!
    bool updateHighscores(std::string filename, int points);

    /*
    Gets user input. Only called when updateHighscores returns true.
    Returns false when input is finished
    */
    bool updateUserInput(sf::Event& event);

    //Draws user input window
    void drawInputBox(sf::RenderWindow& window);

    friend bool higherScore(std::pair<std::string, int> a, std::pair<std::string, int> b);
};
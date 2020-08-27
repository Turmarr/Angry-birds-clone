#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "state.hpp"

class Highscores {
private:

    state options_;

    int maxSize = 5;
    
    sf::Font font;

    //Highscores texts
    sf::Text texts[5];

    //Input box
    sf::RectangleShape box;
    sf::RectangleShape inputBox;
    bool backtrack;
    bool enter;

    //Background
    sf::Texture background;
    sf::RectangleShape rect;

    //Size of the window
    float width_, height_;

    //Is mouse held down
    bool mouseHeld;

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
    void initInputBox();

    //Reads highscores from file. Returns true if successful
    bool Read(std::string filename);

    //Writes highscores to file. Returns true if succesful
    bool Write(std::string filename);

public:

    //Constructor and destructor
    Highscores(float width, float height);
    ~Highscores() {}

    //Checks if points get you onto highscore list
    bool updateHighscores(std::string filename, int points);

    /*
    Gets user input. Only called when updateHighscores returns true.
    Returns false when input is finished
    */
    state updateEvent(sf::Event& event);
    void updateInputBox();

    //Draws user input window
    void drawInputBox(sf::RenderWindow& window);

    friend bool higherScore(std::pair<std::string, int> a, std::pair<std::string, int> b);
};
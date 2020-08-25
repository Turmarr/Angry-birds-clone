#pragma once
#include <SFML/Graphics.hpp>
#include "state.hpp"

class levelMenu
{
private:

    //Size of the window
    float width_, height_;

    //Which option is selected right now
    int selectedItemIndex;
    state options_;
    int maxLevelIndex;

    //Level options
    sf::Font font;
    sf::Text menu[3];

    //Background 
    sf::Texture background;
    sf::RectangleShape rect;

    //Other texts on screen
    sf::Text toMenu;
    sf::Text levels;

    //Is the mouse held down
    bool mouseHeld;

    //Stars
    sf::Texture imag;
    std::vector<sf::Sprite> stars;
    sf::Sprite star;


    //Initializers
    void initFonts();
    void initTexture();
    void initTexts();
    void initStars();
    void initBackground();

public:

    //Constructor and destructor
    levelMenu(float width, float height);
    ~levelMenu();

    //Loads the information about levels' star rating
    void updateStars();
    void updateLevel();

    //Called from outside the class
    state updateMenuEvent(sf::Event& ev, sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);

    //Used to "move" in the menu
    void moveLeft();
    void moveRight();
    int returnSelectedItem() {return selectedItemIndex;}

};
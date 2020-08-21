#pragma once
#include <SFML/Graphics.hpp>

class levelMenu
{
private:

    //Size of the window
    float width_, height_;

    //Which option is selected right now
    int selectedItemIndex;
    int options_;

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


    //Initializors
    void initFonts();
    void initTexture();
    void initTexts();
    void initStars();
    void initBackground();

public:

    levelMenu(float width, float height);
    ~levelMenu();

    void updateStars(int no, int level);
    int updateMenuEvent(sf::Event& ev, sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    void moveLeft();
    void moveRight();
    int returnSelectedItem() {return selectedItemIndex;}

};
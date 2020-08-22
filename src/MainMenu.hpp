#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
private:

    //Which button is selected
    int selectedItemIndex;
    int options_;

    //Menu buttons
    sf::Font font;
    sf::Text menu[3];

    //Background
    sf::Texture background;
    sf::RectangleShape rect;

    //Size of the window
    float width_, height_;

    //Is mouse held down
    bool mouseHeld;

    //Initializers
    void initFonts();
    void initTexture();
    void initBackground();

public:

    //Constructor and destructor
    Menu(float width, float height);
    ~Menu();

    //Called from outside the class
    int updateMenuEvent(sf::Event& ev, sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);

    //Used to "move" in the menu
    void moveUp();
    void moveDown();
    int returnSelectedItem() {return selectedItemIndex;}

};


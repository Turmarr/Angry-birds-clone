#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
private:

    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[3];

    void initFonts();
    void initTexture();

public:

    Menu(float width, float height);
    ~Menu();

    void Draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int returnSelectedItem() {return selectedItemIndex;}

};


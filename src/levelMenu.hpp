#pragma once
#include <SFML/Graphics.hpp>

class levelMenu
{
private:

    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[3];
    int options_;
    sf::Texture background;
    sf::RectangleShape rect;

    bool mouseHeld;

    void initFonts();
    void initTexture();
    void initBackground();

public:

    levelMenu(float width, float height);
    ~levelMenu();

    int updateMenuEvent(sf::Event& ev, sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    void moveLeft();
    void moveRight();
    int returnSelectedItem() {return selectedItemIndex;}

};
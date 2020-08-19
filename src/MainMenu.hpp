#pragma once
#include <SFML/Graphics.hpp>

class Menu
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

    Menu(float width, float height);
    ~Menu();

    int updateMenuEvent(sf::Event& ev, sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int returnSelectedItem() {return selectedItemIndex;}

};


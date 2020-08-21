#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "MainMenu.hpp"
#include "levelMenu.hpp"
#include "Game.hpp"

int main(){

    float width = 1000;
    float height = 700;
    sf::RenderWindow window(sf::VideoMode(width, height), "Vengeful Pigs", sf::Style::Close | sf::Style::Titlebar);
    Game game(window, width, height);
    game.run();
    return 0;
}

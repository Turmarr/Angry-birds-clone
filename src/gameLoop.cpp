#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "MainMenu.hpp"
#include "Game.hpp"

int main(){

    sf::RenderWindow window(sf::VideoMode(800, 600), "Vengeful Pigs", sf::Style::Close | sf::Style::Titlebar);
    Game game(window);
    game.run();
    return 0;
}

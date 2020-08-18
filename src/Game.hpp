#pragma once
#include <SFML/Graphics.hpp>
#include "MainMenu.hpp"
#include <iostream>

class Game{
    public:

        Game(sf::RenderWindow& window);
        ~Game();


        void updatePollEvents();
        void updateMenuEvent(sf::Event& ev);
        void updateGameInput();
        void update();
        void render();
        void run();

    private:

        sf::RenderWindow& window_;
        int state_;
        Menu* menu_;
        int options;

        void initWindow();
        void initMenu();
        
};
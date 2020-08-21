#pragma once
#include <SFML/Graphics.hpp>
#include "MainMenu.hpp"
#include "levelMenu.hpp"
#include <iostream>

class Game{
    public:

        Game(sf::RenderWindow& window, float width, float height);
        ~Game();


        void updatePollEvents();
        void updateGameInput();
        void update();
        void render();
        void run();

    private:

        sf::RenderWindow& window_;
        int state_;
        Menu* menu_;
        levelMenu* lMenu_;
        float width_, height_;

        void initWindow();
        void initMenus();
        
};
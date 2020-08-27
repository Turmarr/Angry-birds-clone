#pragma once
#include <SFML/Graphics.hpp>
#include "MainMenu.hpp"
#include "levelMenu.hpp"
#include "state.hpp"
#include "level.hpp"
#include "Highscores.hpp"
#include "Scoreboard.hpp"
#include <iostream>
#include <memory>

class Game{
    public:

        //Constructor and destructor
        Game(sf::RenderWindow& window, float width, float height);
        ~Game();

        //Functions
        void updatePollEvents();
        void update();
        void render();
        
        //Game loop
        void run();

        //used when a level is chosen from level menu
        void createLevel();
        void deleteLevel();

    private:

        //Window information
        sf::RenderWindow& window_;
        float width_, height_;
        
        //Pointer to different menus
        std::unique_ptr<Menu> menu_;
        std::unique_ptr<levelMenu> lMenu_;
        std::unique_ptr<Level> level_;
        std::unique_ptr<Scoreboard> board_;
        bool constructed_;

        //For highscore updates
        std::unique_ptr<Highscores> highscore_;
        bool newHighscore_;
        bool enterPressed;

        /* Defines the state of the screen - which class is running
            state.i =
            0 - main menu
            1 - level menu
            2 - highscores
            3 - exit
            4 - when playing the game itself
            5 - called when a level has ended (either closed or finished and saved)
            6 - highscore input window
            Also passes a string which is used to hold filename.
        */
        state state_;

        //Initializers
        void initWindow();
        void initMenus();
        
};
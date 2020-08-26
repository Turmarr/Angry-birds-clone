#include "Game.hpp"

Game::Game(sf::RenderWindow& window, float width, float height): window_(window){

    width_ = width;
    height_ = height;

    initWindow();
    initMenus();
    state_.i = 0;
    constructed_ = false;
    newHighscore_ = false;


}

Game::~Game(){

    delete lMenu_;
    delete menu_;
    if (level_ == nullptr){
        std::cout<< "Level deleted twice" << std::endl;
        delete level_;
    }
    delete highscore_;
}
//Settings for the window
void Game::initWindow(){

    window_.setFramerateLimit(60);

}
//Creates the objects for different screens (except level)
void Game::initMenus(){
    
    menu_ = new Menu(width_, height_);
    lMenu_ = new levelMenu(width_, height_);
    highscore_ = new Highscores(width_, height_);
}


void Game::createLevel(){
    
    level_ = new Level(state_.file);
    constructed_ = true;
    
}

//Called when level has finished running
void Game::deleteLevel(){
    
    /* For checking how many stars have been achieved. 
    Checked in levelMenu::updateStars().
    First is the level and then the amount of stars.
    */
    std::cout<< "do twice?" << std::endl;
    lMenu_->updateStars();
    lMenu_->updateLevel();
    delete level_;
    constructed_ = false;
    sf::View view = window_.getDefaultView();
    window_.setView(view);
    if(state_.points == -1){
        state_.i = 1;
        std::cout<< "set to level" << std::endl;
    }
    //state_.i = 1;
    std::cout<< state_.i << std::endl;
    
}
//Game loop
void Game::run(){

    while(window_.isOpen()){
        
        updatePollEvents();
        update();
        render();
    }

}
//User input loop
void Game::updatePollEvents(){
    
    sf::Event ev;
    while(window_.pollEvent(ev)){

        if (state_.i == 0){
            state_= menu_->updateMenuEvent(ev, window_);
        }

        else if (state_.i == 1){
            state_ = lMenu_->updateMenuEvent(ev, window_);
        }
        
        /*else if (state_.i == 2){        
            state_ = highscores_->updateEvent(ev);
        } 
        */
        else if (state_.i == 4){
            state_ = level_->Update(window_, ev);
        }
        else if (state_.i == 6){
            std::cout<< "Highscore evet" << std::endl;
            state_ = highscore_->updateEvent(ev);
        }

        if (state_.i == 3){
            window_.close();
        }
    }
    
}

//Updates state objects
void Game::update(){
    //std::cout<< "update" << std::endl;
   if (state_.i == 4){
       
        if (constructed_ == true){
            level_->Simulate();
        }   

        else if (constructed_ == false){
            createLevel();
        }

   }

   else if (state_.i == 5){
       std::cout<< "state is 5" << std::endl;
        deleteLevel();

        if (state_.i == 5){
            std::cout<< "state is still 5" << std::endl;
            newHighscore_ = highscore_->updateHighscores(state_.file, state_.points);
            if (newHighscore_ = true){
                state_.i == 6;
                std::cout<< "Highscore inputbox called" << std::endl;
            }
            else
            {
                state_.i == 1;
            }
            
        }
    }

    else if (state_.i == 6){
    std::cout<< "inputbox" << std::endl;
       highscore_->updateInputBox();
    }
   
}

//Draws the screen for each state
void Game::render(){
    //std::cout<< "draw" << std::endl;
    window_.clear();

    if (state_.i == 0){
            menu_->Draw(window_);
    }
        
    else if (state_.i == 1){
        std::cout<< "leveldraw" << std::endl;
        lMenu_->Draw(window_);
    }
    
    /*else if (state_.i == 2){        
        highscore_->Draw(window_);
    } */
    else if (state_.i == 4){
        level_->DrawLevel(window_);
    }
    
    else if (state_.i == 6){
        std::cout<< "Drawing" << std::endl;
        highscore_->drawInputBox(window_);
        std::cout<< "Drawing box" << std::endl;
    }

    window_.display();

}
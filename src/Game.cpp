#include "Game.hpp"

Game::Game(sf::RenderWindow& window, float width, float height): window_(window){

    width_ = width;
    height_ = height;

    initWindow();
    initMenus();
    state_.i = 0;
    constructed_ = false;
    newHighscore_ = false;
    level_ = nullptr;


}

Game::~Game(){

    if (level_ != nullptr){
        std::cout<< "Level deleted twice" << std::endl;
        level_ = nullptr;
    }
}
//Settings for the window
void Game::initWindow(){

    window_.setFramerateLimit(60);

}
//Creates the objects for different screens (except level)
void Game::initMenus(){
    
    menu_ = std::make_unique<Menu>(width_, height_);
    lMenu_ = std::make_unique<levelMenu>(width_, height_);
    highscore_ = std::make_unique<Highscores>(width_, height_);
}


void Game::createLevel(){
    
    level_ = std::make_unique<Level>(state_.file);
    constructed_ = true;
    
}

//Called when level has finished running
void Game::deleteLevel(){
    
    /* For checking how many stars have been achieved. 
    Checked in levelMenu::updateStars().
    First is the level and then the amount of stars.
    */
    lMenu_->updateStars();
    lMenu_->updateLevel();
    level_ = nullptr;
    constructed_ = false;
    sf::View view = window_.getDefaultView();
    window_.setView(view);
    if(state_.points == -1){
        state_.i = 1;
        std::cout<< "back to level state is " << state_.i << std::endl;
    }
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
        deleteLevel();

        if (state_.i == 5){
            newHighscore_ = highscore_->updateHighscores(state_.file, state_.points);
            if (newHighscore_ = true){
                state_.i = 6;
            }
            else
            {
                state_.i == 1;
            }
            
        }
    }
   
}

//Draws the screen for each state
void Game::render(){
    
    window_.clear();

    if (state_.i == 0){
        menu_->Draw(window_);
    }
        
    else if (state_.i == 1){
        lMenu_->Draw(window_);
    }
    
    /*else if (state_.i == 2){        
        highscore_->Draw(window_);
    } */
    else if (state_.i == 4){
        level_->DrawLevel(window_);
    }
    
    else if (state_.i == 6){
        highscore_->drawInputBox(window_);
    }

    window_.display();

}
#include "Game.hpp"

Game::Game(sf::RenderWindow& window, float width, float height): window_(window){

    width_ = width;
    height_ = height;

    initWindow();
    initMenus();
    state_.i = 0;
    constructed_ = false;


}

Game::~Game(){

    delete lMenu_;
    delete menu_;
    if (level_ == nullptr){
        std::cout<< "Level deleted twice" << std::endl;
        delete level_;
    }
    //delete highscore_;
}
//Settings for the window
void Game::initWindow(){

    window_.setFramerateLimit(60);

}
//Creates the objects for different screens (except level)
void Game::initMenus(){
    
    menu_ = new Menu(width_, height_);
    lMenu_ = new levelMenu(width_, height_);
    //highscore_ = new Highscore(width_, height_);
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
    lMenu_->updateStars();
    lMenu_->updateLevel();
    delete level_;
    constructed_ = false;
    sf::View view = window_.getDefaultView();
    window_.setView(view);
    if(state_.points = -1){
        state_.i = 1;
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

        if (state_.i == 3){
            window_.close();
        }
    }
    
}

//Updates state objects
void Game::update(){

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
       /*if (state_.i == 5){
          newHighscore = highscore_->updateHighscores(state_.file, state_.points);

       }*/
   }
   /*else if (state_.i == 6){
       input = highscore_->updateInput();

       if (input == false){
           state_.i = 1;
       }
   }
    */
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
        } 
        */
        else if (state_.i == 4){
            level_->DrawLevel(window_);
        }
        /*
        else if (state_.i == 6 && input = true){
            highscore_->drawInputBox(window_);
        }*/

    window_.display();

}
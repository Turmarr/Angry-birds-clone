#include "Game.hpp"

Game::Game(sf::RenderWindow& window, float width, float height): window_(window){

    width_ = width;
    height_ = height;

    initWindow();
    initMenus();
    state_ = 0;

}

Game::~Game(){

    delete lMenu_;
    delete menu_;
}

void Game::initWindow(){

    window_.setFramerateLimit(60);

}

void Game::initMenus(){
    
    menu_ = new Menu(width_, height_);
    lMenu_ = new levelMenu(width_, height_);
}

//Chooses which file is downloaded
void Game::createLevel(){
    
    /*switch (state_)
    {
    case 4:
        level = Level("")
        break;
    
    case 5:
        level = Level("")
        break;

    case 6:
        level = Level("")
        break;

    default:
        break;
    }*/
}

void Game::deleteLevel(){
    
    lMenu_->updateStars();
    //delete level_;
    state_ = 1;
}

void Game::run(){

    while(window_.isOpen()){
        
        updatePollEvents();
        update();
        render();
    }

}

void Game::updatePollEvents(){
    
    sf::Event ev;

    while(window_.pollEvent(ev)){

        if (state_ == 0){
            state_ = menu_->updateMenuEvent(ev, window_);
        }

        else if (state_ == 1){
            state_ = lMenu_->updateMenuEvent(ev, window_);
        }
        
        /*else if (state_ == 2){        
            state_ = lMenu_->updateMenuEvent(ev, window_);
        } 

        else if (state_ == 4 || state_ == 5 || state_ == 6){
            level_->updateEvent();
        }*/

        if (state_ == 3){
            window_.close();
        }
    }
    
}

//Updates game forward
void Game::update(){

   /*if (state_ == 4 || state_ == 5 || state_ == 6){
       level_->update();
   }*/
   if (state_ == 7){
       deleteLevel();
   }
    
}

void Game::render(){

    window_.clear();

   if (state_ == 0){
            menu_->Draw(window_);
        }
        
        else if (state_ == 1){
            lMenu_->Draw(window_);
        }
        
        /*else if (state_ == 2){        
            highscore->Draw(window_);
        } 

        else if (state_ == 4 || state_ == 5 || state_ == 6){
            level_->Draw(window_);
        }*/

    window_.display();

}
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
    /*if (level_ != nullptr){
        delete level_;
    }*/
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
    
    //level_ = new level(state_.file);
    //constructed_ = true;
    
}

void Game::deleteLevel(){
    
    lMenu_->updateStars();
    lMenu_->updateLevel();
    //delete level_;
    //constructed_ = false;
    state_.i = 1;
    
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

        if (state_.i == 0){
            state_= menu_->updateMenuEvent(ev, window_);
        }

        else if (state_.i == 1){
            state_ = lMenu_->updateMenuEvent(ev, window_);
        }
        
        /*else if (state_.i == 2){        
            state_ = lMenu_->updateMenuEvent(ev, window_);
        } 

        else if (state_.i == 4){
            if (constucted_ == false){
                createlevel();
            }
            level_->Update(window_, ev);
        }*/

        if (state_.i == 3){
            window_.close();
        }
    }
    
}

//Updates game forward
void Game::update(){

   /*if (state_ == 4){
       level_->Simulate();
   }*/
   if (state_.i == 7){
       deleteLevel();
   }
    
}

void Game::render(){

    window_.clear();

   if (state_.i == 0){
            menu_->Draw(window_);
        }
        
        else if (state_.i == 1){
            lMenu_->Draw(window_);
        }
        
        /*else if (state_.i == 2){        
            highscore->Draw(window_);
        } 

        else if (state_.i == 4){
            level_->DrawLevel(window_);
        }*/

    window_.display();

}
#include "Game.hpp"

Game::Game(sf::RenderWindow& window): window_(window){

    initWindow();
    initMenu();
    state_ = 0;

}

Game::~Game(){

    delete menu_;
}

void Game::initWindow(){

    window_.setFramerateLimit(60);

}
void Game::initMenu(){
    menu_ = new Menu(800, 600);
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
        else if(state_ == 1){
        
        }
        if (state_ == 3){
            window_.close();
        }
    }
    
}

void Game::update(){

}

void Game::render(){

    window_.clear();

    if (state_ == 0){
        menu_->Draw(window_);
    }

    window_.display();

}
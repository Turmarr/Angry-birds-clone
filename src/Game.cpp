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

        switch (state_)
        {
        case 0:
            state_ = menu_->updateMenuEvent(ev, window_);
            break;

        case 1:
            state_ = lMenu_->updateMenuEvent(ev, window_);
            break;

        default:
            break;
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

    switch (state_)
        {
        case 0:
            menu_->Draw(window_);
            break;

        case 1:
            lMenu_->Draw(window_);
            break;
            
        default:
            break;
        }

    window_.display();

}
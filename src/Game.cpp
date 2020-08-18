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
            updateMenuEvent(ev);
            
        }
        else if(state_ == 1){
        
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

void Game::updateMenuEvent(sf::Event& ev){

    switch (ev.type){

        case sf::Event::Closed:
            window_.close();
            state_ = 3;
            break;
        case sf::Keyboard::Escape:
            window_.close();
            state_ = 3;
            break;

        case sf::Event::KeyReleased:
            switch (ev.key.code){

                case sf::Keyboard::Down:
                    menu_->moveDown();
                    break;
                
                case sf::Keyboard::Up:
                    menu_->moveUp();
                    break;

                case sf::Keyboard::Return:
                    options = menu_->returnSelectedItem();
                    switch (options){

                        case 0:
                            std::cout<< "Possible gameplay here" << std::endl;
                            break;
                        
                        case 1:
                            std::cout<< "Possible highscores here" << std::endl;
                            break;

                        case 2:
                            window_.close();
                            state_ = 4;
                            break;
                        
                        default:
                            break;
                    }

                default:
                    break;
            }
    }
}
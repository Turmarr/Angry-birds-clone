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

    /*delete menu_;
    delete lMenu_;
    delete board_;
    delete highscore_;
    if (level_ != nullptr){
        delete level_;
    }*/

}
//Settings for the window
void Game::initWindow(){

    window_.setFramerateLimit(60);

}
//Creates the objects for different screens (except level)
void Game::initMenus(){

    //with C++14 compiler
    menu_ = std::make_unique<Menu>(width_, height_);
    lMenu_ = std::make_unique<levelMenu>(width_, height_);
    highscore_ = std::make_unique<Highscores>(width_, height_);
    board_ = std::make_unique<Scoreboard>(width_, height_);
    /*
    //With C++11
    menu_ = new Menu(width_, height_);
    lMenu_ = new levelMenu(width_, height_);
    highscore_ = new Highscores(width_, height_);
    board_ = new Scoreboard(width_, height_);
    */
}


void Game::createLevel(){
    
    level_ = std::make_unique<Level>(state_.file);
    //level_ = new Level(state_.file);
    constructed_ = true;
    
}

//Called when level has finished running
void Game::deleteLevel(){
    
    lMenu_->updateStars();
    lMenu_->updateLevel();
    level_ = nullptr;
    //delete level_;
    constructed_ = false;
    sf::View view = window_.getDefaultView();
    window_.setView(view);
    if(state_.points == -1){
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
        
        else if (state_.i == 2){        
            state_ = board_->updateEvent(ev);
        }

        else if (state_.i == 4){
            state_ = level_->Update(window_, ev);
        }
        else if (state_.i == 6){
            state_ = highscore_->updateEvent(ev);
            if (state_.i == 1){
                board_->setScoreTexts();
            }

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

        if (state_.i == 5){
            //std::cout<< "end level 3" << std::endl;
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
    
    else if (state_.i == 2){        
        board_->Draw(window_);
    }
    else if (state_.i == 4){
        level_->DrawLevel(window_);
    }
    
    else if (state_.i == 6){
        highscore_->drawInputBox(window_);
    }

    window_.display();

}
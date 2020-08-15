#include "Bird.hpp"
#include <iostream>

Bird::Bird(float x, float y, const std::string& type){
    x_ = x;
    y_ = y;
    
    initTexture();
    initSprite();

}

Bird::~Bird(){

}

//Initializes the bird
void Bird::initSprite(){

    sprite.setPosition(x_, y_);
    this->sprite.setTexture(this->pic_);
    sprite.scale(sf::Vector2f(0.3f, 0.3f));
    
}
//Load texture from file
void Bird::initTexture(){

    if(!this->pic_.loadFromFile("Textures/bird.png")){
        std::cout<< "Error when loading the image from textures." <<std::endl;
    }
}
//Checks the collisions?
void Bird::Update(){


}

void Bird::Render(sf::RenderTarget& target){

    target.draw(sprite);

}
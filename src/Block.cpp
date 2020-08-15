#include "Block.hpp"
#include <iostream>

Block::Block(float x, float y, const std::string& type, float angle){
    x_ = x;
    y_ = y;
    type_ = type;
    angle_ = angle;
    initTexture();
    initSprite();

}

Block::~Block(){

}

//Initializes the bird
void Block::initSprite(){

    sprite.setPosition(x_, y_);
    this->sprite.setTexture(this->pic_);
    sprite.scale(sf::Vector2f(0.3f, 0.3f));
    sprite.rotate(angle_);
    
}
//Load texture from file
void Block::initTexture(){

    if(!this->pic_.loadFromFile("Textures/bird.png")){
        std::cout<< "Error when loading the image from textures." <<std::endl;
    }
}
//Checks the collisions?
void Block::Update(){


}

void Block::Render(sf::RenderTarget& target){

    target.draw(sprite);

}
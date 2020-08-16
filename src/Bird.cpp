
#include "Bird.hpp"
#include <iostream>

Bird::Bird(float x, float y, b2World& world, const float scale){
    x_ = x;
    y_ = y;
    scale_ = scale;
    
    initTexture();
    initSprite();
    initPhysics(world);

}

Bird::~Bird(){

}

//Initializes the bird
void Bird::initSprite(){

    sprite.setPosition(x_, y_);
    this->sprite.setTexture(this->pic_);
    sprite.scale(sf::Vector2f(0.3f, 0.3f));
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
    
}
//Load texture from file
void Bird::initTexture(){

    if(!this->pic_.loadFromFile("Textures/bird.png")){
        std::cout<< "Error when loading the image from textures." <<std::endl;
    }
}
void Bird::initPhysics(b2World& world){

    b2BodyDef BodyDef;
    BodyDef.type = b2_dynamicBody;
    BodyDef.position.Set(x_/scale_, y_/scale_);

    body = world.CreateBody(&BodyDef);

    b2CircleShape circle;
    circle.m_radius = radius_/scale_;

    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.8f;
    FixtureDef.friction = 0.3f;

    FixtureDef.shape = &circle;
    body->CreateFixture(&FixtureDef);
}


void Bird::Draw(sf::RenderTarget& target){

    sprite.setPosition(body->GetPosition().x*scale_,body->GetPosition().y*scale_);
    sprite.setRotation(body->GetAngle()*180/b2_pi);
    target.draw(sprite);

}
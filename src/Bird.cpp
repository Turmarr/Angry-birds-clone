
#include "Bird.hpp"
#include <iostream>

Bird::Bird(float x, float y, b2World& world, const float scale, float radius, Points* points){
    x_ = x;
    y_ = y;
    scale_ = scale;
    radius_ = radius;

    world_ = &world;
    
    initTexture();
    initSprite();
    initPhysics(world);

    points_ = points;

}

Bird::~Bird(){
    points_->AddPoints(1000);
    world_->DestroyBody(body);
}

//Initializes the bird
void Bird::initSprite(){

    sprite.setPosition(x_, y_);
    sprite.setTexture(&this->pic_);
    sprite.setRadius(radius_);
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


void Bird::Draw(sf::RenderWindow& target){

    sprite.setPosition(body->GetPosition().x*scale_,body->GetPosition().y*scale_);
    sprite.setRotation(body->GetAngle()*180/b2_pi);
    target.draw(sprite);

}
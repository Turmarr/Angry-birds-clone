#include "Ball.hpp"
#include <iostream>

Ball::Ball(float x, float y, const std::string& type, float radius, b2World& world, const float scale){
    x_ = x;
    y_ = y;
    type_ = type;
    radius_ = radius;
    scale_ = scale;

    initTexture();
    initSprite();
    initPhysics(world);
}

Ball::~Ball(){

}

//Initializes the bird
void Ball::initSprite(){

    shape.setPosition(x_, y_);
    shape.setTexture(&this->pic_);
    shape.setRadius(radius_);
    shape.setOrigin(shape.getLocalBounds().width/2, shape.getLocalBounds().height/2);

}
//Load texture from file
void Ball::initTexture(){
    
    std::string file;

    if (type_ == "wood"){
        file= "Textures/wood.jpg";
    }
    else if (type_ == "Stone"){
        file = "Textures/stone.jpg";
    }
    
    if(!this->pic_.loadFromFile(file)){
        std::cout<< "Error when loading the image from textures." <<std::endl;
    }
}

void Ball::initPhysics(b2World& world){
    b2BodyDef BallDef;
    BallDef.type = b2_dynamicBody;
    BallDef.position.Set(x_/scale_, y_/scale_);

    body = world.CreateBody(&BallDef);

    b2CircleShape circle;
    circle.m_radius = radius_/scale_;

    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.0f;
    FixtureDef.friction = 0.3f;

    FixtureDef.shape = &circle;
    body->CreateFixture(&FixtureDef);

}

void Ball::Draw(sf::RenderWindow& target){
    shape.setPosition(body->GetPosition().x*scale_,body->GetPosition().y*scale_);
    shape.setRotation(body->GetAngle()*180/b2_pi);
    target.draw(shape);
}
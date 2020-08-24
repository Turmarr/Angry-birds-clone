#include "Ball.hpp"
#include <iostream>

Ball::Ball(float x, float y, const std::string& type, float radius, b2World& world, const float scale, Points* points){
    x_ = x;
    y_ = y;

    mat = Material(type);
    
    radius_ = radius;
    scale_ = scale;

    points_ = points;

    POINTS_ = mat.points;
    hp_ = mat.hp;

    world_ = &world;

    initTexture();
    initSprite();
    initPhysics(world);
}

Ball::~Ball(){
    points_->AddPoints(POINTS_);
    world_->DestroyBody(body);
}

//Initializes the bird
void Ball::initSprite(){

    shape.setPosition(x_, y_);
    shape.setTexture(&this->pic_);
    shape.setRadius(radius_);
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOrigin(shape.getLocalBounds().width/2, shape.getLocalBounds().height/2);

}
//Load texture from file
void Ball::initTexture(){
    
    std::string file = mat.texture;
    
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
    FixtureDef.density = mat.density;
    FixtureDef.friction = 0.3f;

    FixtureDef.shape = &circle;
    body->CreateFixture(&FixtureDef);
    body->SetUserData(this);
}

void Ball::Draw(sf::RenderWindow& target){
    shape.setPosition(body->GetPosition().x*scale_,body->GetPosition().y*scale_);
    shape.setRotation(body->GetAngle()*180/b2_pi);
    target.draw(shape);
}
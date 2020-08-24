#include <SFML/Graphics.hpp>
#include "Box2D/box2d/box2d.h"
#include "Speed.hpp"
#include <iostream>

Speed::Speed(float x, float y, b2World* world) {
    initTexture();
    initCircle();

    world_ = world;

    body_ = NULL;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x, y);
    body_ = world_->CreateBody(&bodyDef);

    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = radius_;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body_->CreateFixture(&fixtureDef);
}

Speed::~Speed() {
    world_->DestroyBody(body_);
}

void Speed::Draw(sf::RenderWindow& window) {
    circle_.setOrigin(radius_ * SCALE, radius_ * SCALE);
    circle_.setPosition(body_->GetPosition().x * SCALE, body_->GetPosition().y * SCALE);
    circle_.setRotation(body_->GetAngle() * 180/b2_pi);
    window.draw(circle_);
}

void Speed::Special() {
    if(specialityUsed){
        return;
    }

    float impulse = 3;
    b2Vec2 vel = body_->GetLinearVelocity();
    body_->SetLinearVelocity(b2Vec2(vel.x * impulse, vel.y * impulse));
    
    
    //body_->ApplyLinearImpulseToCenter(b2Vec2(cos(body_->GetAngle()) * impulse, sin(body_->GetAngle()) * impulse), true);
    
    specialityUsed = true;
}

void Speed::initTexture(){
    if(!texture_.loadFromFile("../Textures/speed_pig.png", sf::IntRect(0, 0, 60, 60))){
        std::cout<< "Error when loading the image from textures." <<std::endl;
    }
}

void Speed::initCircle(){
    circle_.setRadius(radius_ * SCALE);
    circle_.setTexture(&texture_);
}

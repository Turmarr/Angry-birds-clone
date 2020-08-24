#include <SFML/Graphics.hpp>
#include "Box2D/box2d/box2d.h"
#include "Normal.hpp"
#include <iostream>

Normal::Normal(float x, float y, b2World* world) {
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

Normal::~Normal() {
    world_->DestroyBody(body_);
}

void Normal::Draw(sf::RenderWindow& window) {
    circle_.setOrigin(radius_ * SCALE, radius_ * SCALE);
    circle_.setPosition(body_->GetPosition().x * SCALE, body_->GetPosition().y * SCALE);
    circle_.setRotation(body_->GetAngle() * 180/b2_pi);
    window.draw(circle_);
}

void Normal::initTexture(){
    if(!texture_.loadFromFile("../Textures/normal_pig.png", sf::IntRect(0, 0, 60, 60))){
        std::cout<< "Error when loading the image from textures." <<std::endl;
    }
}

void Normal::initCircle(){
    circle_.setRadius(radius_ * SCALE);
    circle_.setTexture(&texture_);
}

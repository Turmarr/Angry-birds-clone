#include <SFML/Graphics.hpp>
#include "Box2D/box2d/box2d.h"
#include "Normal.hpp"
#include <iostream>

Normal::Normal(float x, float y, b2World* world) {
    initTexture();
    initSprite();

    body_ = NULL;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x, y);
    body_ = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox((width_/2), (heigth_/2));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body_->CreateFixture(&fixtureDef);
}

Normal::~Normal() {

}

void Normal::Draw(sf::RenderWindow& window) {
    //std::cout << body_->GetPosition().x << std::endl;
    sprite_.setOrigin(width_ / 2 * SCALE, width_ / 2 * SCALE);
    sprite_.setPosition(body_->GetPosition().x * SCALE, body_->GetPosition().y * SCALE);
    sprite_.setRotation(body_->GetAngle() * 180/b2_pi);
    window.draw(sprite_);
}

void Normal::initTexture(){
    if(!texture_.loadFromFile("Textures/normal_pig.png", sf::IntRect(0, 0, 60, 60))){
        std::cout<< "Error when loading the image from textures." <<std::endl;
    }
}

void Normal::initSprite(){
    this->sprite_.setTexture(this->texture_);
}
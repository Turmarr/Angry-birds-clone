#include <SFML/Graphics.hpp>
#include "Box2D/box2d/box2d.h"
#include "Bomb.hpp"
#include <iostream>

Bomb::Bomb(float x, float y, b2World* world) {
    initTexture();
    initSprite();

    world_ = world;

    body_ = NULL;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    body_ = world_->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox((width_/2), (heigth_/2));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body_->CreateFixture(&fixtureDef);
}

Bomb::~Bomb() {
    //Destroy all the particles created in an explosion
    for(auto i : blastParticleBodies_){
        world_->DestroyBody(i);
        i = NULL;
    }

    //Destroy the bird
    world_->DestroyBody(body_);
}

void Bomb::Draw(sf::RenderWindow& window) {
    sprite_.setOrigin(width_ / 2 * SCALE, width_ / 2 * SCALE);
    sprite_.setPosition(body_->GetPosition().x * SCALE, body_->GetPosition().y * SCALE);
    sprite_.setRotation(body_->GetAngle() * 180/b2_pi);
    window.draw(sprite_);
}

void Bomb::Special() {

    //Check if already used the speciality
    if(specialityUsed){
        return;
    }

    //Get explosion center
    b2Vec2 center = body_->GetPosition();

    //Set explosion power
    float blastPower = 1000;

    //Set number of different directions. Higher number mean more CPU usage
    int numRays = 100;

    for(int i = 0; i < numRays; i++){
        //Get the direction in which we launch the particle
        float angle = (i / (float)numRays) * 360 * (b2_pi / 180);
        b2Vec2 rayDir( sinf(angle), cosf(angle) );

        //Create small particle
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.fixedRotation = true;
        bd.bullet = true;
        bd.linearDamping = 10;
        bd.gravityScale = 0;
        bd.position = center;
        bd.linearVelocity = 0.125f * blastPower * rayDir;
        b2Body* particle = world_->CreateBody(&bd);

        b2CircleShape circleShape;
        circleShape.m_radius = 0.05;

        b2FixtureDef fd;
        fd.shape = &circleShape;
        fd.density = 60 / (float) numRays;
        fd.friction = 0;
        fd.restitution = 0.99f;
        fd.filter.groupIndex = -1; // particles won't collide with each other
        particle->CreateFixture(&fd);

        //Save all particles to a list so we can delete them when objects destructor is called
        blastParticleBodies_.push_back(particle);
    }
}

void Bomb::initTexture(){
    if(!texture_.loadFromFile("Textures/normal_pig.png", sf::IntRect(0, 0, 60, 60))){
        std::cout<< "Error when loading the image from textures." <<std::endl;
    }
}

void Bomb::initSprite(){
    this->sprite_.setTexture(this->texture_);
}
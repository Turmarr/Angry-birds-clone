#include <SFML/Graphics.hpp>
#include "Box2D/box2d/box2d.h"
#include "Bomb.hpp"
#include <iostream>

Bomb::Bomb(float x, float y, b2World* world) {
    initTexture();
    initCircle();

    world_ = world;

    body_ = NULL;
    type_ = "Bomb";

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

Bomb::~Bomb() {
    //Destroy all the particles created in an explosion
    for(auto i : blastParticleBodies_){
        world_->DestroyBody(i);
        i = NULL;
    }

    //Destroy the pig
    world_->DestroyBody(body_);
}

void Bomb::Draw(sf::RenderWindow& window) {
    //std::cout << body_->GetPosition().x << " " << body_->GetPosition().y << std::endl;
    circle_.setOrigin(radius_ * SCALE, radius_ * SCALE);
    circle_.setPosition(body_->GetPosition().x * SCALE, body_->GetPosition().y * SCALE);
    circle_.setRotation(body_->GetAngle() * 180/b2_pi);
    
    window.draw(circle_);

    for (auto i : blastParticleBodies_) {
        float vel = sqrt(pow(i->GetLinearVelocity().x, 2) + pow(i->GetLinearVelocity().y, 2));
        if (vel > 0.01) {
            sf::CircleShape shape;
            shape.setPosition(i->GetPosition().x * SCALE, i->GetPosition().y * SCALE);
            shape.setRadius(1);
            shape.setOrigin(1, 1);
            shape.setFillColor(sf::Color::Black);
            window.draw(shape);
        }
        
    }
}

void Bomb::Special() {

    //Check if already used the speciality
    if(specialityUsed){
        return;
    }
    
    //Set birds groupIndex to -1 to avoid colliding with the particles created in the explosion
    b2Fixture* f = body_->GetFixtureList();
    b2Filter filter = f->GetFilterData();
    filter.groupIndex = -1;
    f->SetFilterData(filter);

    //Get explosion center
    b2Vec2 center = body_->GetPosition();

    //Set explosion power
    float blastPower = 1000;

    //Set number of different directions. Higher number mean more CPU usage
    int numRays = 300;

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

    specialityUsed = true;
}



void Bomb::initTexture(){
    if(!texture_.loadFromFile("../src/Textures/bombpig.png")){
        std::cout<< "Error when loading the image from textures." <<std::endl;
    }
}

void Bomb::initCircle(){
    circle_.setRadius(radius_ * SCALE);
    circle_.setTexture(&texture_);
    circle_.setOutlineThickness(1);
    circle_.setOutlineColor(sf::Color::Black);
}

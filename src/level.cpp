#include <algorithm>
#include "Box2D/box2d/box2d.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include "level.hpp"



Level::Level(std::string filename) {

    //std::cout << "pig" << std::endl;
    b2Vec2 gravity (0.0f, 10.0f);
    //b2World *world(gravity);
    world_ = new b2World(gravity);

    //std::cout << "pig" << std::endl;

    Filereader info(filename);

    //std::cout << "file" << std::endl;

    ground_ = info.GetGround();
    CreateGround();

    auto temp_pigs = info.GetPigs();
    sort(temp_pigs.begin(), temp_pigs.end(), [](Pigc a, Pigc b) {return a.pos < b.pos;});
    for (auto i : info.GetPigs()) {
        pigs_.push_back(i);
    }

    //std::cout << "pig" << std::endl;
    
    for (auto i : info.GetBirds()) {
        Bird *bird = new Bird(i.x, i.y, *world_, SCALE_, bird_radius_);
        birds_.push_back(bird);
    }

    //std::cout << birds_.size() << std::endl;
    
    for (auto i : info.GetObjects()) {
        if (i.type == "box") {
            Box *object = new Box(i.x, i.y, i.material, box_angle_, *world_, SCALE_);
            box_.push_back(object);
        }
        if (i.type == "ball") {
            Ball *object = new Ball(i.x, i.y, i.material, ball_radius_, *world_, SCALE_);
            ball_.push_back(object);
        }
    }

    //std::cout << "object" << std::endl;
    //std::cout << box_.size() << std::endl;
    //std::cout << ball_.size() << std::endl;

    for (auto i : info.GetGround()) {
        ground_.push_back(i);
    }

    cannon_ = info.GetCannon();

    NextPig();
    //std::cout << "all" << std::endl;
    //std::cout << birds_.size() << std::endl;
    //std::cout << box_.size() << std::endl;
    //std::cout << world_->GetBodyCount() << std::endl;
    
}

void Level::NextPig() {
    
    if (pigs_.size() != 0) {
        Pigc current = pigs_.back();
        pigs_.pop_back();
        if (current.type == "normal") {
            Normal *pig = new Normal(cannon_.x / SCALE_, cannon_.y / SCALE_, world_);
            current_pig_ = pig;
        }
        else if (current.type == "bomb") {
            Bomb *pig = new Bomb(cannon_.x / SCALE_, cannon_.y / SCALE_, world_);
            current_pig_ = pig;
        }
        else {
            current_pig_ = nullptr;
        }
    }
    else {
        current_pig_ = nullptr;
    }
}

void Level::CreateGround() {
    for (auto i : ground_) {
        b2BodyDef groundBodyDef;
        groundBodyDef.type = b2_staticBody;
        groundBodyDef.position.Set(i.x/SCALE_, i.y/SCALE_);
        
        b2Body* body = world_->CreateBody(&groundBodyDef);
        
        b2PolygonShape groundBox;
        groundBox.SetAsBox((i.width/2) / SCALE_, (i.height/2) / SCALE_);

        body->CreateFixture(&groundBox, 0.0f);
    }
}

void Level::DrawGround(sf::RenderWindow& window) {
    for (auto i : ground_) {
        sf::RectangleShape ground { { i.width, i.height } };
        ground.setOrigin(i.width/2, i.height/2);
        ground.setPosition(i.x, i.y);
        //ground.setRotation(groundBody->GetAngle() * 180/b2_pi);
        ground.setFillColor(sf::Color::Black);
        window.draw(ground);
    }
}

void Level::Update(sf::RenderWindow& window) {

    world_->Step(timeStep_, velocityIterations_, positionIterations_);
    window.clear(sf::Color::White);
    DrawGround(window);
    

    if (current_pig_ != nullptr) {
        current_pig_->Draw(window);
    }

    for (auto i : birds_) {
        i->Draw(window);
    }
    for (auto i : box_) {
        i->Draw(window);
    }
    for (auto i : ball_) {
        i->Draw(window);
    }

    window.display();
}
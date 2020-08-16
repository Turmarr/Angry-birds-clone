#include <algorithm>
#include "Box2D/box2d/box2d.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "level.hpp"



Level::Level(std::string filename) {

    b2Vec2 gravity (0.0f, 10.0f);
    world_->SetGravity(gravity);

    Filereader info(filename);

    ground_ = info.GetGround();
    CreateGround();

    auto temp_pigs = info.GetPigs();
    sort(temp_pigs.begin(), temp_pigs.end(), [](Pigc a, Pigc b) {return a.pos < b.pos;});
    for (auto i : info.GetPigs()) {
        //check which pig
        pigs_.push_back(i);
    }

    for (auto i : info.GetBirds()) {
        Bird bird(i.x, i.y, *world_, SCALE_);
        birds_.push_back(bird);
    }
    
    for (auto i : info.GetObjects()) {
        if (i.type == "box") {
            Box object(i.x, i.y, i.material, 0, *world_, SCALE_);
            box_.push_back(object);
        }
        if (i.type == "ball") {
            Ball object(i.x, i.y, i.material, 30.0f, *world_, SCALE_);
            ball_.push_back(object);
        }
    }

    for (auto i : info.GetGround()) {
        ground_.push_back(i);
    }

    cannon_ = info.GetCannon();
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

void Level::DrawGround(sf::RenderTarget& target) {
    for (auto i : ground_) {
        sf::RectangleShape ground { { i.width, i.height } };
        ground.setOrigin(i.width/2, i.height/2);
        ground.setPosition(i.x, i.y);
        //ground.setRotation(groundBody->GetAngle() * 180/b2_pi);
        ground.setFillColor(sf::Color::Red);
        target.draw(ground);
    }
}

void Level::Update(sf::RenderWindow& window) {

    world_->Step(timeStep_, velocityIterations_, positionIterations_);

    window.clear();

    DrawGround(window);

    //add pigs when ready

    for (auto i : birds_) {
        i.Draw(window);
    }
    for (auto i : box_) {
        i.Draw(window);
    }
    for (auto i : ball_) {
        i.Draw(window);
    }

    window.display();
}
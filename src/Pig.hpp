#include <SFML/Graphics.hpp>
#include "Box2D/box2d/box2d.h"
#include <iostream>
#pragma once

class Pig {
public:
    Pig() {}
    virtual ~Pig() {}
    
    virtual void Draw(sf::RenderWindow& window) { }

    virtual void Special() {}

    float GetSpeed() const{
        b2Vec2 vel = body_->GetLinearVelocity();
        float sp = sqrt(pow(vel.x, 2) + pow(vel.y, 2));
        return sp;
    }

    void SetDynamic() {
        body_->SetType(b2_dynamicBody);
    }

    void SetVelocity(b2Vec2 vel) {
        body_->SetLinearVelocity(vel);
    }

    void SetAngle(float ang) {
        body_->SetTransform(body_->GetPosition(), ang);
    }

    bool GetSpecialityUsed() {
        return specialityUsed;
    }

    b2Vec2 GetPosition() {
        return body_->GetPosition();
    }

    
protected:
    //Pointer to the Box2d world
    b2World* world_;

    //Pointer to Box2D object
    b2Body* body_;

    //Objects radius. Set at 1m so circle should be 60 pixels
    float radius_ = 1.0f;

    sf::Texture texture_;

    //Loads texture from file
    virtual void initTexture() = 0;

    sf::CircleShape circle_;

    //Sets sprites texture
    virtual void initCircle() = 0;

    int SCALE = 30;

    bool specialityUsed = false;
};
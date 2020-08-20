#include <SFML/Graphics.hpp>
#include "Box2D/box2d/box2d.h"
#include <iostream>
#pragma once

class Pig {
public:
    Pig() {}
    ~Pig() {}
    
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
    b2Body* body_;
    bool specialityUsed = false;
};
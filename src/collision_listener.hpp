#include "Box2D/box2d/box2d.h"
#include "Destructables.hpp"
#include "iostream"

#pragma once

class collision_listener : public b2ContactListener {
    void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) {
        //std::cout << "1" << std::endl;
        float imp = impulse->normalImpulses[0];
        //std::cout << imp << std::endl;
        void* body_a = contact->GetFixtureA()->GetBody()->GetUserData();
        if (body_a) {
            static_cast<Destructables*>(body_a) -> ReduceHp(imp);
        }
        void* body_b = contact->GetFixtureA()->GetBody()->GetUserData();
        if (body_b) {
            static_cast<Destructables*>(body_b) -> ReduceHp(imp);
        }
        //std::cout << "d" << std::endl;
    }
};
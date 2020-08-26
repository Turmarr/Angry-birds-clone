#include "Box2D/box2d/box2d.h"
#include "Destructables.hpp"
#include "iostream"

#pragma once


//Could add a minimum impulse thereshold to the imp variable it would just be a 
//if (i > x) / if (i < x) depending on direction of impulse
//Also could use only the first implements of impulse

/*
Class based on the contactlistener class,
Only the postsolve method is in use:
-It first adds the eigenvalue all of the impulses together
-Secondly it removes health from the bodies which have health implemented
*/

class collision_listener : public b2ContactListener {
    void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) {
        
        float imp = 0;
        for (auto i : impulse->normalImpulses) {
            if (i > 1) {
                imp += i;
            }
            else if (i < -1){
                imp -= i;
            }
        }
        for (auto i : impulse->tangentImpulses) {
            if (i > 1) {
                imp += i;
            }
            else if (i < -1){
                imp -= i;
            }
        }
        //std::cout << imp << std::endl;
        void* body_a = contact->GetFixtureA()->GetBody()->GetUserData();
        if (body_a) {
            static_cast<Destructables*>(body_a) -> ReduceHp(imp);
        }
        void* body_b = contact->GetFixtureA()->GetBody()->GetUserData();
        if (body_b) {
            static_cast<Destructables*>(body_b) -> ReduceHp(imp);
        }
        
    }
};
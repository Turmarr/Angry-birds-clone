#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Box2D/box2d/box2d.h"
#include "Points.hpp"



class Destructables
{
    protected:
        Points* points_;
        b2World* world_;
        int POINTS_;
        float hp_ = 0;

    public:
        Destructables(){}
        ~Destructables(){}
        virtual void Draw(sf::RenderWindow& target) {}
        float GetHp() const {
            return hp_;
        }
        void ReduceHp(float red) {
            hp_ -= red;
        }
};
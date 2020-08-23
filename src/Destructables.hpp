#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Box2D/box2d/box2d.h"
#include "Points.hpp"

class Material {
    public:
        Material() {}

        Material(std::string type) {
            if (type == "wood") {
                points = 100;
                hp = 100;
                texture = "Textures/wood.jpg";
                density = 1;
            }
            else if (type == "stone") {
                points = 200;
                hp = 200;
                texture = "Textures/stone.jpg";
                density = 2;
            }
            else if (type == "bird") {
                points = 1000;
                hp = 10;
                texture = "Textures/bird.png";
                density = 1;
            }
        }
    int points;
    int hp;
    std::string texture;
    float density;
};

class Destructables
{
    protected:
        Points* points_;
        b2World* world_;
        int POINTS_;
        float hp_ = 0;
        Material mat;

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
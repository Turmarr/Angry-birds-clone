#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Box2D/box2d/box2d.h"


class Destructables
{
    private:
        
    public:
        Destructables(){}
        ~Destructables(){}
        virtual void Draw(sf::RenderWindow& target) = 0;

};
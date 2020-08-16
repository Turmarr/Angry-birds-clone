#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "include/box2d/box2d.h"


class Destructables
{
    private:
        
    public:
        Destructables(){}
        ~Destructables(){}
        virtual void Update() = 0;
        virtual void Draw(sf::RenderTarget& target) = 0;

};
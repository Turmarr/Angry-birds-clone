#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


class Destructables
{
    private:
        
    public:
        Destructables(){}
        ~Destructables(){}
        virtual void Update() = 0;
        virtual void Render(sf::RenderTarget& target) = 0;

};
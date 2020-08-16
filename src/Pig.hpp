#include <SFML/Graphics.hpp>
#include "Box2D/box2d/box2d.h"
#pragma once

class Pig {
public:
    Pig() {}
    ~Pig() {}
    
    virtual void Draw(sf::RenderWindow& window) = 0;
private:
};
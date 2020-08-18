#include <SFML/Graphics.hpp>
#include "Box2D/box2d/box2d.h"
#include <iostream>
#pragma once

class Pig {
public:
    Pig() {}
    ~Pig() {}
    
    virtual void Draw(sf::RenderWindow& window) { }

    virtual void Special() { }
private:
};
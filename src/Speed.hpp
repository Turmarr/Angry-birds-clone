#include <SFML/Graphics.hpp>
#include "Box2D/box2d/box2d.h"
#include "Pig.hpp"

#pragma once
class Speed: public Pig {
public:
    //Constructor. Creates a new Box2D object
    Speed(float x, float y, b2World* world);

    //Destructor
    ~Speed();

    /*Draw function
    Gets pigs position from Box2D and draws it using SFML
    */
   void Draw(sf::RenderWindow& window);

    /*
    Special ability
    Speed burst to the direction pig is facing
    */
   void Special();

private:

    //Loads texture from file
    void initTexture();

    //Sets sprites texture
    void initCircle();
};

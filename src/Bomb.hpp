#include <SFML/Graphics.hpp>
#include "Box2D/box2d/box2d.h"
#include "Pig.hpp"
#include <list>

class Bomb: public Pig {
public:
    //Constructor. Creates a new Box2D object
    Bomb(float x, float y, b2World* world);

    //Destructor
    ~Bomb();

    /*Draw function
    Gets pigs position from Box2D and draws it using SFML
    */
   void Draw(sf::RenderWindow& window);

   /*
   Special ability
   Exlodes
   Tutorial from https://www.iforce2d.net/b2dtut/explosions
   */
   void Special();

private:

    //List of particles created in explosion
    std::list<b2Body*> blastParticleBodies_;

    //Loads texture from file
    void initTexture();

    //Sets sprites texture
    void initCircle();
};
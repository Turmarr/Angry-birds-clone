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

    //Pointer to the Box2d world
    b2World* world_;

    //Pointer to Box2D object
    

    //List of particles created in explosion
    std::list<b2Body*> blastParticleBodies_;

    //Objects heigth and width. Set at 2m so when scaled should be 60 pixels
    float heigth_ = 2.0f;
    float width_ = 2.0f;

    sf::Texture texture_;

    //Loads texture from file
    void initTexture();

    sf::Sprite sprite_;

    //Sets sprites texture
    void initSprite();

    int SCALE = 30;

    bool specialityUsed = false;
};
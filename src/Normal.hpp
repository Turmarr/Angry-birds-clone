#include <SFML/Graphics.hpp>
#include "Box2D/box2d/box2d.h"
#include "Pig.hpp"

class Normal: public Pig {
public:
    //Constructor. Creates a new Box2D object
    Normal(float x, float y, b2World* world);

    //Destructor
    ~Normal();

    /*Draw function
    Gets pigs position from Box2D and draws it using SFML
    */
   void Draw(sf::RenderWindow& window);

private:

    //Loads texture from file
    void initTexture();

    //Sets sprites texture
    void initCircle();
};
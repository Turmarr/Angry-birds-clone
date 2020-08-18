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

    //Pointer to Box2D object
    

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
};
#pragma once
#include "Destructables.hpp"

class Ball: public Destructables
{
    private:

        
        sf::CircleShape shape; //Shape of the block
        sf::Texture pic_; //texture used
        std::string type_; //What kind of block type is in question

        b2Body* body;

        //The placement and size
        float x_,y_;
        float radius_;
        float scale_;
        float angle_;

        //Initializors
        void initSprite();
        void initTexture();
        void initPhysics(b2World& world);
    
    public:
        Ball(float x, float y, const std::string& type, float radius, b2World& world, const float scale);
        ~Ball();

        void Draw(sf::RenderWindow& target);
        
};
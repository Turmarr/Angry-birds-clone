#pragma once
#include "Destructables.hpp"

class Bird: public Destructables
{
    private:

        sf::Sprite sprite;
        sf::Texture pic_; //Which texture is used
        std::string type_; //What kind of bird is in question
        
        b2Body* body;

        float x_,y_; //The placement in the window
        float scale_;

        float radius_ = 30.0f;

        void initSprite();
        void initTexture();
        void initPhysics(b2World& world);
    
    public:
        Bird(float x, float y, b2World& world, const float scale);
        ~Bird();

        void Draw(sf::RenderWindow& target);
        
};

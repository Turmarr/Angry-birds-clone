#pragma once
#include "Destructables.hpp"

class Bird: public Destructables
{
    private:

        sf::CircleShape sprite;
        sf::Texture pic_; //Which texture is used
        std::string type_; //What kind of bird is in question
        
        b2Body* body;

        float x_,y_; //The placement in the window
        float radius_;
        float scale_;

        

        void initSprite();
        void initTexture();
        void initPhysics(b2World& world);
    
    public:
        Bird(float x, float y, std::string type, b2World& world, const float scale, float radius, Points* points);
        ~Bird();

        virtual void Draw(sf::RenderWindow& target);
        
};

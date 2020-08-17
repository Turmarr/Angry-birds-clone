#pragma once
#include "Destructables.hpp"

class Box: public Destructables
{
    private:

        sf::RectangleShape shape; //Shape of the block
        sf::Texture pic_; //Which texture is used
        std::string type_; //What kind of block is in question

        b2Body* body;

        float x_,y_; //The placement in the window
        float angle_; //The angle of the rotation of the block
        float scale_;
        float width = 60.f;
        float height = 60.f;

        //Init functions
        void initPhysics(b2World& world);
        void initBlock();
        void initTexture();
    
    public:
        Box(float x, float y, const std::string& type, float angle, b2World& world, const float scale);
        ~Box();

        void Draw(sf::RenderWindow& target);
        
};
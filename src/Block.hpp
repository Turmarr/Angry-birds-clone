#pragma once
#include "Destructables.hpp"

class Block: public Destructables
{
    private:

        sf::Sprite sprite;
        //Which texture is used
        sf::Texture pic_;
        //What kind of bird is in question
        std::string type_;
        //The placement in the window
        float x_,y_;
        //The angle of the block
        float angle_;

        void initSprite();
        void initTexture();
    
    public:
        Block(float x, float y, const std::string& type, float angle);
        ~Block();

        void Update();
        void Render(sf::RenderTarget& target);
        
};
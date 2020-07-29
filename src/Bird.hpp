#pragma once
#include "Destructables.hpp"

class Bird: public Destructables
{
    private:

        sf::Sprite sprite;
        //Which texture is used
        sf::Texture pic_;
        //What kind of bird is in question
        std::string type_;
        //The placement in the window
        float x_,y_;

        void initSprite();
        void initTexture();
    
    public:
        Bird(float x, float y, const std::string& type);
        ~Bird();

        void Update();
        void Render(sf::RenderTarget& target);
        
};

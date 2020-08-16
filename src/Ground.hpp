#include "include/box2d/box2d.h"
#include <SFML/Graphics.hpp>

class Ground{
    public:

        b2Body* body;
        sf::RectangleShape rect;

        float x, y;
        float w, h;

        Ground(float midpoint_x, float midpoint_y, float width, float height, b2World& world, const float scale){
            x = midpoint_x;
            y = midpoint_y;
            w = width;
            h = height;
            scale_ = scale;

            sf::RectangleShape rect;
            rect.setOrigin(w/2, h/2);
            rect.setSize({w, h});
            rect.setFillColor(sf::Color::Black);

            b2BodyDef groundDef;
            groundDef.type = b2_staticBody;
            groundDef.position.Set(x/scale_, y/scale_);
            body = world.CreateBody(&groundDef);

            b2PolygonShape groundBox;
            groundBox.SetAsBox((w/2)/scale_, (h/2)/scale_);

            body->CreateFixture(&groundBox, 0.0f);
        }
        
        void Draw(sf::RenderWindow window){
            rect.setPosition(body->GetPosition.x*scale_, body->GetPosition().y*scale_);
            rect.setRotation(body.GetAngle()*180/b2_pi);
            window.draw(rect);
        }

    private:
        float scale_;
        
};

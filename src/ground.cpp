
#include "ground.hpp"

Ground::Ground(float midpoint_x, float midpoint_y, float width, float height, b2World& world, const float scale) {
    x = midpoint_x;
    y = midpoint_y;
    
    w = width;
    h = height;
    
    scale_ = scale;
    
    sf_rect.setOrigin(w/2, h/2);
    sf_rect.setPosition(x,y);
    sf_rect.setSize({w,h});
    sf_rect.setFillColor(sf::Color::Black);
    
    
    b2BodyDef groundBodyDef;
    groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(x/scale, y/scale);
    
    body = world.CreateBody(&groundBodyDef);
    
    b2PolygonShape groundBox;
    groundBox.SetAsBox((w/2) / scale, (h/2) / scale);
    
    
    body->CreateFixture(&groundBox, 0.0f);
    
}

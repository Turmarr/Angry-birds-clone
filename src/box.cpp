//
//  box.cpp
//  box2d_Hello_World
//
//  Created by Aleksi Sohlman on 29.7.2020.
//  Copyright © 2020 Aleksi Sohlman. All rights reserved.
//

#include "box.hpp"


Box::Box(float init_x, float init_y, b2World& world, const float scale) {
    x = init_x;
    y = init_y;
    
    w = 70;
    h = 100;
    
    scale_ = scale;
    
    sf_box.setPosition(x, y);
    sf_box.setSize({w,h});
    sf_box.setOrigin(w/2, h/2);
    sf_box.setFillColor(sf::Color::White);
    sf_box.setOutlineColor(sf::Color::Black);
    sf_box.setOutlineThickness(-4);
    
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / scale , y / scale);
    
    body = world.CreateBody(&bodyDef);
    
    b2PolygonShape box_shape;
    box_shape.SetAsBox((w/2) / scale, (h/2) / scale);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box_shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    
    body->CreateFixture(&fixtureDef);
    
}

//
//  Ground.hpp
//  box2d_Hello_World
//
//  Created by Aleksi Sohlman on 1.8.2020.
//  Copyright © 2020 Aleksi Sohlman. All rights reserved.
//

#ifndef ground_hpp
#define ground_hpp

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Ground {
  public:
    
    b2Body* body;
    sf::RectangleShape sf_rect;
    
    float x, y;
    float w, h;
    
    Ground(float upper_left_x, float upper_left_y, float width, float height, b2World& world, const float scale);
    
    void Draw(sf::RenderWindow& window) {
        sf_rect.setPosition(body->GetPosition().x * scale_, body->GetPosition().y * scale_);
        sf_rect.setRotation(body->GetAngle() * 180/b2_pi);
        
        window.draw(sf_rect);
    }
    
  private:
    float scale_;
    
};

#endif /* ground_hpp */

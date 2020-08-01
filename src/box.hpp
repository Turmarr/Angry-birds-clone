//
//  box.hpp
//  box2d_Hello_World
//
//  Created by Aleksi Sohlman on 29.7.2020.
//  Copyright © 2020 Aleksi Sohlman. All rights reserved.
//

#ifndef box_hpp
#define box_hpp

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Box {
  public:
    
    b2Body* body;
    sf::RectangleShape sf_box;
    
    float x, y;
    float w, h;
    
    Box(float init_x, float init_y, b2World& world, float scale);
    
    
    void Draw(sf::RenderWindow& window) {
        sf_box.setPosition(body->GetPosition().x * scale_, body->GetPosition().y * scale_);
        sf_box.setRotation(body->GetAngle() * 180/b2_pi);
        
        window.draw(sf_box);
    }
    
  private:
    float scale_;
    
};




#endif /* box_hpp */

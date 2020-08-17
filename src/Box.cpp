#include "Box.hpp"
#include <iostream>

Box::Box(float x, float y, const std::string& type, float angle, b2World& world, const float scale){
    x_ = x;
    y_ = y;
    type_ = type;
    angle_ = angle;
    scale_ = scale;

    initTexture();
    initBlock();
    initPhysics(world);

}

Box::~Box(){

}


//Applies the physics
void Box::initPhysics(b2World& world){
    b2BodyDef blockDef;
    blockDef.type = b2_dynamicBody;
    blockDef.position.Set(x_/scale_, y_/scale_);

    body = world.CreateBody(&blockDef);

    b2PolygonShape box;
    box.SetAsBox((width/2)/scale_, (height/2)/scale_);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}

//Initializes the shape
void Box::initBlock(){

    shape.setPosition(x_, y_);
    shape.setTexture(&this->pic_);
    shape.setSize(sf::Vector2f(width, height));
    shape.setOrigin(width/2, height/2);
    shape.rotate(angle_);

}
//Loads texture from file
void Box::initTexture(){

    std::string file;

    if (type_ == "wood"){
        file = "Textures/wood.jpg";
    }
    else if (type_ == "stone"){
        file = "Textures/stone.jpg";
    }

    if(!this->pic_.loadFromFile(file)){
        std::cout<< "Error when loading the image from textures." <<std::endl;
    }
    
}

void Box::Draw(sf::RenderWindow& target){
    shape.setPosition(body->GetPosition().x*scale_, body->GetPosition().y*scale_);
    shape.setRotation(body->GetAngle()*180/b2_pi);
    target.draw(shape);
}
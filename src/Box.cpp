#include "Box.hpp"
#include <iostream>

Box::Box(float x, float y, const std::string& type, float width, float height, float angle, b2World& world, const float scale, Points* points){
    x_ = x;
    y_ = y;
    mat = Material(type);
    
    //type_ = type;
    angle_ = angle;
    scale_ = scale;
    width_ = width;
    height_ = height;

    world_ = &world;

    points_ = points;

    POINTS_ = mat.points;
    hp_ = mat.hp;

    initTexture();
    initBlock();
    initPhysics(world);

}

Box::~Box(){
    points_->AddPoints(POINTS_);
    world_->DestroyBody(body);
}


//Applies the physics
void Box::initPhysics(b2World& world){
    b2BodyDef blockDef;
    blockDef.type = b2_dynamicBody;
    blockDef.position.Set(x_/scale_, y_/scale_);

    body = world.CreateBody(&blockDef);

    b2PolygonShape box;
    box.SetAsBox((width_/2)/scale_, (height_/2)/scale_);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = mat.density;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
    body->SetUserData(this);
}

//Initializes the shape
void Box::initBlock(){

    shape.setPosition(x_, y_);
    shape.setTexture(&this->pic_);
    shape.setSize(sf::Vector2f(width_, height_));
    shape.setOrigin(width_/2, height_/2);
    shape.rotate(angle_);

}
//Loads texture from file
void Box::initTexture(){

    std::string file = mat.texture;

    if(!this->pic_.loadFromFile(file)){
        std::cout<< "Error when loading the image from textures." <<std::endl;
    }
    
}

void Box::Draw(sf::RenderWindow& target){
    shape.setPosition(body->GetPosition().x*scale_, body->GetPosition().y*scale_);
    shape.setRotation(body->GetAngle()*180/b2_pi);
    target.draw(shape);
}
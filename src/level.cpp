#include <algorithm>
#include "Box2D/box2d/box2d.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <sstream>
#include "level.hpp"





Level::Level(std::string filename) {

    //init pointcounter
    points_ = new Points();
    draw_ = new Vect();

    //std::cout << "pig" << std::endl;
    b2Vec2 gravity (0.0f, 10.0f);
    //b2World *world(gravity);
    world_ = new b2World(gravity);

    //std::cout << "pig" << std::endl;

    Filereader info(filename);

    //std::cout << "file" << std::endl;

    ground_ = info.GetGround();
    CreateGround();

    auto temp_pigs = info.GetPigs();
    sort(temp_pigs.begin(), temp_pigs.end(), [](Pigc a, Pigc b) {return a.pos < b.pos;});
    for (auto i : info.GetPigs()) {
        pigs_.push_back(i);
    }

    //std::cout << "pig" << std::endl;
    
    for (auto i : info.GetBirds()) {
        Bird *bird = new Bird(i.x, i.y, *world_, SCALE_, bird_radius_, points_);
        birds_.push_back(bird);
    }

    //std::cout << birds_.size() << std::endl;
    
    for (auto i : info.GetObjects()) {
        if (i.type == "box") {
            Box *object = new Box(i.x, i.y, i.material, box_angle_, *world_, SCALE_, points_);
            box_.push_back(object);
        }
        if (i.type == "ball") {
            Ball *object = new Ball(i.x, i.y, i.material, ball_radius_, *world_, SCALE_, points_);
            ball_.push_back(object);
        }
    }

    //std::cout << "object" << std::endl;
    //std::cout << box_.size() << std::endl;
    //std::cout << ball_.size() << std::endl;

    for (auto i : info.GetGround()) {
        ground_.push_back(i);
    }

    cannon_ = info.GetCannon();

    NextPig();
    //std::cout << "all" << std::endl;
    //std::cout << birds_.size() << std::endl;
    //std::cout << box_.size() << std::endl;
    //std::cout << world_->GetBodyCount() << std::endl;
    
}

void Level::NextPig() {
    //std::cout << pigs_.size() << std::endl;
    pig_flying_ = false;
    pig_drawn_ = false;
    if (pigs_.size() != 0) {
        //std::cout << "adding" << std::endl;
        Pigc current = pigs_.back();
        pigs_.pop_back();
        if (current.type == "normal") {
            Normal *pig = new Normal(cannon_.x / SCALE_, cannon_.y / SCALE_, world_);
            current_pig_ = pig;
        }
        else if (current.type == "bomb") {
            Bomb *pig = new Bomb(cannon_.x / SCALE_, cannon_.y / SCALE_, world_);
            current_pig_ = pig;
        }
        else {
            current_pig_ = nullptr;
        }
    }
    else {
        current_pig_ = nullptr;
        //std::cout << "null" << std::endl;
    }
}

void Level::CreateGround() {
    for (auto i : ground_) {
        b2BodyDef groundBodyDef;
        groundBodyDef.type = b2_staticBody;
        groundBodyDef.position.Set(i.x/SCALE_, i.y/SCALE_);
        
        b2Body* body = world_->CreateBody(&groundBodyDef);
        
        b2PolygonShape groundBox;
        groundBox.SetAsBox((i.width/2) / SCALE_, (i.height/2) / SCALE_);

        body->CreateFixture(&groundBox, 0.0f);
    }
}

void Level::DrawGround(sf::RenderWindow& window) {
    for (auto i : ground_) {
        sf::RectangleShape ground { { i.width, i.height } };
        ground.setOrigin(i.width/2, i.height/2);
        ground.setPosition(i.x, i.y);
        //ground.setRotation(groundBody->GetAngle() * 180/b2_pi);
        ground.setFillColor(sf::Color::Black);
        window.draw(ground);
    }
}

void Level::DrawScore(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "error getting font"<< std::endl;
    }
    sf::Text text;
    text.setFont(font);
    std::stringstream ss;
    ss << points_->GetPoints();
    text.setString(ss.str());
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Red);
    text.setPosition( {10, 10} );
    window.draw(text);
}

void Level::DrawCannon(sf::RenderWindow& window) {
    sf::CircleShape shape;
    shape.setPosition(cannon_.x, cannon_.y);
    shape.setFillColor(sf::Color::Red);
    shape.setRadius(20);
    shape.setOrigin(shape.getLocalBounds().width/2, shape.getLocalBounds().height/2);
    window.draw(shape);
}

float Level::GetDistance(float x1, float y1, float x2, float y2) {
    float dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return dist;
}

void Level::ReadyCannon(float x, float y) {
    draw_->SetVec(cannon_.x - x, cannon_.y - y);
    if (draw_->GetLength() > max_draw_) {
        draw_->SetLen(max_draw_);
    }
    angle_ = draw_->GetAngle();
    //add the rotating of the cannon and the possible arrow
}

void Level::FirePig() {
    current_pig_->SetDynamic();
    current_pig_->SetAngle(angle_ * b2_pi / 180);
    current_pig_->SetVelocity(b2Vec2(draw_->x_/10, draw_->y_/10));
    pig_flying_ = true;
}

void Level::Update(sf::RenderWindow& window) {
    while (running_) {
        world_->Step(timeStep_, velocityIterations_, positionIterations_);
        window.clear(sf::Color::White);
        
        //add the reseting of the camera once added
        //setup exiting the loop once the last pig dies
        if (current_pig_ != nullptr && pig_flying_) {
            if (current_pig_->GetSpeed() <= 0.1) {
                delete current_pig_;
                NextPig();
            }
        }

        sf::Event ev;
            while(window.pollEvent(ev))
            {
                switch (ev.type)
                {
                    case sf::Event::Closed:
                        running_ = false;
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (pig_flying_ && !current_pig_->GetSpecialityUsed()) {
                            current_pig_->Special();
                        }
                        else if (!pig_flying_) {
                            float x = ev.mouseButton.x;
                            float y = ev.mouseButton.y;
                            if (GetDistance(cannon_.x, cannon_.y, x, y) <= 20 && current_pig_ != nullptr) {
                                pig_drawn_ = true;
                            }
                        }
                        break;
                    case sf::Event::MouseMoved:
                        if (pig_drawn_) {
                            float x = ev.mouseMove.x;
                            float y = ev.mouseMove.y;
                            ReadyCannon(x,y);
                        }
                        break;
                    case sf::Event::MouseButtonReleased:
                        if (pig_drawn_) {
                            float x = ev.mouseButton.x;
                            float y = ev.mouseButton.y;
                            FirePig();
                        }
                        break;
                    
                }
            }

        //Draws the level
        DrawGround(window);
        DrawCannon(window);
        
        if (current_pig_ != nullptr && pig_flying_) {
            current_pig_->Draw(window);
        }

        for (auto i : birds_) {
            i->Draw(window);
        }
        for (auto i : box_) {
            i->Draw(window);
        }
        for (auto i : ball_) {
            i->Draw(window);
        }

        DrawScore(window);

        window.display();
    }
}
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "include/box2d/box2d.h"
#include <list>
#include <iostream>

/*
Read Hello Box2D example from the documentation of Box2d and the not working example 
of SFML and Box2d.
https://box2d.org/documentation/md__d_1__git_hub_box2d_docs_hello.html
https://veendeta.wordpress.com/2012/02/16/tutorial-getting-started-with-box2d/

Differences between this code and the example above:
    - No separate functions for creating objects
    - As the iteration over the world objects didn't work properly dynamic objects are stored
      in a separate list
    - Added variables WIDTH and HEIGHT to define the size of the boxes 

How to run:
The Cmake file should work properly so just run cmake out of the build
folder and then make. The executable will be generated with the name "example"
*/

int main() {
    //scale for conversion
    static const float SCALE = 30.f;

    //box width and hight in pixels
    static const float WIDTH = 32.0f;
    static const float HEIGHT = 32.0f;

    //time step for simulation
    float timeStep = 1.0f / 60.0f;

    //iteration counts
    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    //create world with gravity
    //the gravity vector points upward as the Box2D simulation and the SFML
    //graphics have their y-axis pointing in opposite directions: The Box2D up and
    //SFML down. 
    b2Vec2 gravity (0.0f, 10.0f);
    b2World world(gravity);

    //create window
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Example");
    window.setFramerateLimit(60);

    //static body "ground"
    b2BodyDef groundBodyDef;
    groundBodyDef.type == b2_staticBody;
    groundBodyDef.position.Set(400.0f/SCALE, 500.0f/SCALE);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;

    groundBox.SetAsBox((800.f/2)/SCALE, (16.f/2)/SCALE);

    groundBody->CreateFixture(&groundBox, 0.0f);

    //the list where all of the dynamic bodies will be stored
    std::list<b2Body*> dynamic;
    
    //The game loop for the window
    while (window.isOpen()) {

        //polling for events, otherwise the window will become unresponsive
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    {
                    window.close();
                    break;
                    }

                case sf::Event::MouseButtonPressed:
                    {
                    
                    //builds a dynamic body at the point where was clicked
                    int MouseX = event.mouseButton.x;
                    int MouseY = event.mouseButton.y;

                    b2BodyDef bodyDef;
                    bodyDef.type = b2_dynamicBody;
                    bodyDef.position.Set(MouseX/SCALE, MouseY/SCALE);
                    b2Body* body = world.CreateBody(&bodyDef);

                    b2PolygonShape dynamicBox;
                    dynamicBox.SetAsBox((WIDTH/2)/SCALE, (HEIGHT/2)/SCALE);

                    b2FixtureDef fixtureDef;
                    fixtureDef.shape = &dynamicBox;
                    fixtureDef.density = 1.0f;
                    fixtureDef.friction = 0.3f;

                    body->CreateFixture(&fixtureDef);

                    dynamic.push_back(body);
                    break;
                    }
                
                default:
                    break;
            }
        }

        //moving the world forward
        world.Step(timeStep, velocityIterations, positionIterations);

        window.clear(sf::Color::Black);

        sf::RectangleShape ground { { 800, 16 } };
        
        //setting the origin of the transformation to the center of the rectangle
        // -> the point that we get with box2d
        ground.setOrigin(400.0f, 8.0f);
        ground.setPosition(groundBody->GetPosition().x * SCALE, groundBody->GetPosition().y * SCALE);
        ground.setRotation(groundBody->GetAngle() * 180/b2_pi);
        ground.setFillColor(sf::Color::Red);
        window.draw(ground);

        for (auto body : dynamic) {
            sf::RectangleShape dyn { {WIDTH, HEIGHT} };
            dyn.setOrigin(16.f, 16.f);
            dyn.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
            dyn.setRotation(body->GetAngle() * 180/b2_pi);
            dyn.setFillColor(sf::Color::Green);
            window.draw(dyn);
        }


        window.display();
    }
    

    return 0;
}
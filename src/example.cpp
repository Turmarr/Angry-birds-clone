#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Box2D/box2d/box2d.h"
#include <list>
#include <iostream>

#include "box.hpp"
#include "ground.hpp"


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

const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 1200;




int main() {
    
    const float SCALE = 30.f;

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
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Example");
    window.setFramerateLimit(60);

    
    //static body "ground"
    Ground* ground = new Ground(WINDOW_WIDTH / 2, 0.8 * WINDOW_HEIGHT , WINDOW_WIDTH, 16.f, world, SCALE);
    
    //the list where all of the dynamic bodies will be stored
    std::list<Box*> boxes;
    
    
    //The game loop
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
                    
                    //Adds a box at the point where was clicked
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    Box* box = new Box(mouseX, mouseY, world, SCALE);

                    boxes.push_back(box);
                        
                    break;
                    }
                
                default:
                    break;
            }
        }

        
        
        //moving the world forward
        world.Step(timeStep, velocityIterations, positionIterations);

        window.clear(sf::Color::White);

        
        // Draw the floor
        ground->Draw(window);

        // Draw the boxes
        for (auto box : boxes) {
            box->Draw(window);
        }

        window.display();
    }
    

    return 0;
}

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Destructables.hpp"
//#include "Bird.hpp"
#include "Box.hpp"
//#include "Ball.hpp"
#include "include/box2d/box2d.h"
#include "Ground.hpp"

int main(){

    const float SCALE = 30.f
    float timeStep = 1.0f/60.0f
    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    b2Vec2 gravity (0.0f, 10.0f);
    b2World world(gravity);

    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Testing for enemies", sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev;
    window.setFramerateLimit(60);

    Ground* ground = new Ground(800/2, 0.8*600, 800, 16.f, world, SCALE);


    //Bird bird = Bird(100.f, 100.f, world, SCALE, 60.f);
    Box block = Box(500.f, 300.f, "Wood", 90, world, SCALE);
    //Ball ball = Ball(300.f, 200.f, "wood", 100.f, world, SCALE);

    //Game loop
    while (window.isOpen()){

        while(window.pollEvent(ev))
        {
            switch (ev.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }

    //Update
    world.Step(timeStep, velocityIterations, positionIterators);


    //Render
    window.clear(sf::Color::White); //clears old frame

    
    //Draw here

    ground->Draw(window);
    //bird.Draw(window);
    block.Draw(window);
    //ball.Draw(window);

    window.display();  //displays the window after draw

    }

    return 0;
}
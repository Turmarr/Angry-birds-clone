#include <SFML/Graphics.hpp>
#include "Box2D/box2d/box2d.h"
#include <iostream>
#include "Normal.hpp"
#include "Bomb.hpp"

int scale = 30;

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Testi");
	window.setFramerateLimit(60);

    // Define the gravity vector.
	b2Vec2 gravity(0.0f, 10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(15.0f, 15.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(6.f, 1.f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	Normal pig1(12.f, 3.f, &world);
	Normal pig2(20.f, 0.f, &world);

	Bomb pig3(16.f, 0.f, &world);

	// Define the dynamic body. We set its position and call the body factory.
	/*b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(12.f, 3.f);
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.f, 1.f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	//fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);*/



	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// This is our little game loop.
	/*for (int32 i = 0; i < 60; ++i)
	{
		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world.Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		b2Vec2 position = body->GetPosition();
		float angle = body->GetAngle();

		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}*/

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
			pig3.Special();
		}

        window.clear();
        world.Step(timeStep, velocityIterations, positionIterations);
        
        sf::RectangleShape ground(sf::Vector2f(12.f * scale, 2.f * scale));
        ground.setFillColor(sf::Color::Green);
        ground.setOrigin(6.f * scale, 1.f * scale);
        b2Vec2 position = groundBody->GetPosition();
        ground.setPosition(sf::Vector2f(position.x * scale, position.y * scale));

        /*sf::RectangleShape box(sf::Vector2f(2.f * scale, 2.f * scale));
        box.setFillColor(sf::Color::Blue);
        box.setOrigin(0.f, 0.f);
        b2Vec2 position2 = body->GetPosition();

        std::cout << position2.x * scale << " " << position2.y * scale <<std::endl;

        box.setPosition(sf::Vector2f(position2.x * scale, position2.y * scale));*/

        window.draw(ground);
		pig1.Draw(window);
		pig2.Draw(window);
		pig3.Draw(window);
        //window.draw(box);

        window.display();
    }

	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.

	return 0;
}
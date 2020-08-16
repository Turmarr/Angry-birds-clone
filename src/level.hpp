#include "Box2D/box2d/box2d.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <list>
#include <algorithm>
#include "filereader.hpp"
#include "Bird.hpp"
#include "Box.hpp"
#include "Ball.hpp"

#ifndef LEVEL_CLASS
#define LEVEL_CLASS

/*
To make testing without the real classes possible the level is defined as a template class
*/

//needs the constructors added to the for loops for the different objects


class Level {
    public:
        //initialises the level and puts the first pig into the cannon
        Level(std::string filename);

        std::vector<Pigc> GetPigs() const {
            return pigs_;
        }

        void Update(sf::RenderWindow& window);
        //deconstructs the level, is where the level end screen will be determined
        /*
        ~Level() {


            for (auto i : pigs_) {
                delete i;
            }
            for (auto i : objects_) {
                delete i;
            }
            for (auto i : birds_) {
                delete i;
            }
        }
        */
        
    

    private:
        void CreateGround();
        void DrawGround(sf::RenderTarget& target);

        const float SCALE_ = 30.f;
        float timeStep_ = 1.0f / 60.0f;
        int32 velocityIterations_ = 8;
        int32 positionIterations_ = 3;
        
        b2World* world_;
        
        int points = 0;

        std::vector<Pigc> pigs_;
        std::vector<Pigc>::iterator current_pig_;
        std::vector<Bird> birds_;
        std::vector<Box> box_;
        std::vector<Ball> ball_;
        std::vector<struct Groundc> ground_;
        struct Cannonc cannon_;
        
};

#endif
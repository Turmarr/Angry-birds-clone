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
#include "Destructables.hpp"
#include "Pig.hpp"
#include "Normal.hpp"
#include "Bomb.hpp"
#include "Points.hpp"


#ifndef LEVEL_CLASS
#define LEVEL_CLASS





class Level {
    public:
        //initialises the level and puts the first pig into the cannon
        Level(std::string filename);

        std::vector<Pigc> GetPigs() const {
            return pigs_;
        }

        void Update(sf::RenderWindow& window);
        //deconstructs the level, is where the level end screen will be determined
        
        ~Level() {

            delete current_pig_;
            
            for (auto i : box_) {
                delete i;
            }
            for (auto i : ball_) {
                delete i;
            }
            for (auto i : birds_) {
                delete i;
            }
            //std::cout << points_->GetPoints() << std::endl;
            delete points_;
            delete world_;
        }
        


    private:
        //functions
        void NextPig();
        void CreateGround();
        void DrawGround(sf::RenderWindow& target);

        //general variables
        const float SCALE_ = 30.f;
        b2World* world_;

        //constructor variables maybe added to stuff
        //float box_height;
        //float box_width_;
        float box_angle_ = 0;
        float ball_radius_ = 30;
        float bird_radius_ = 30;


        //box2d variables
        float timeStep_ = 1.0f / 60.0f;
        int32 velocityIterations_ = 8;
        int32 positionIterations_ = 3;

        //update variables
        Points* points_;
        bool Pig_flying_;

        std::vector<Pigc> pigs_;
        Pig* current_pig_;
        std::vector<Pig*> old_pigs_;
        std::vector<Bird*> birds_;
        std::vector<Box*> box_;
        std::vector<Ball*> ball_;
        std::vector<struct Groundc> ground_;
        struct Cannonc cannon_;
        
};

#endif
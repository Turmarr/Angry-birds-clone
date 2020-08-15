#include "Box2D/box2d/box2d.h"

#include <vector>
#include <list>
#include <algorithm>
#include "filereader.hpp"

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

        std::vector<Pig> GetPigs() const {
            return pigs_;
        }

        void Update();
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
        
        

        //returns how many pigs are left
        /*
        int GetPigs() const {
            auto i = pigs_.begin();
            for (; i != current_pig_; i++) { }
            int j = 0;
            for (; i != pigs_.end(); i++, j++) { }
            return j;
        }
        */
        
        //will update all the objects
        //cannot be implemented before the objects themselves are built

    private:
        static const float SCALE_ = 30.f;
        float timeStep_ = 1.0f / 60.0f;
        int32 velocityIterations_ = 8;
        int32 positionIterations_ = 3;
        b2World world_;
        
        int points = 0;

        std::vector<struct Pig> pigs_;
        std::vector<Pig>::iterator current_pig_;
        std::vector<struct Bird> birds_;
        std::vector<struct Object> objects_;
        std::vector<struct Ground> ground_;
        struct Cannon cannon_;
        
};

#endif
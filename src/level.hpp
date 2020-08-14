//#include "include/box2d/box2d.h"

#include <vector>
#include <list>
#include "filereader.hpp"

#ifndef LEVEL_CLASS
#define LEVEL_CLASS

/*
To make testing without the real classes possible the level is defined as a template class
*/

template <typename T, typename D, typename S>
class Level {
    public:
        //initialises the level and puts the first pig into the cannon
        Level(std::vector<T> pigs, std::list<D> objects, std::list<S> birds)
            : pigs_(pigs), objects_(objects), birds_(birds), score_(0) {
                current_pig_ = pigs_.begin();
                birdcount_ = 0;
                for (auto i : birds_) {birdcount_++;}
                
            }

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
        
        //If possible called in the destructor of the bird class but final implementation
        //may require a different approach
        bool ReduceBirdcount() {
            birdcount_--;
            if (birdcount_ == 0) {
                return true;
            }
            return false;
        }

        //to enable the game loop to detect when there are no birds left
        const int GetBirdcount() const {
            return birdcount_;
        }

        bool NextPig() {
            current_pig_++;
            if (current_pig_ != pigs_.end()) {
                return true;
            }
            return false;
        }

        //returns how many pigs are left
        int GetPigs() const {
            auto i = pigs_.begin();
            for (; i != current_pig_; i++) { }
            int j = 0;
            for (; i != pigs_.end(); i++, j++) { }
            return j;
        }

        //will update all the objects
        //cannot be implemented before the objects themselves are built

    private:
        typename std::vector<T>::iterator current_pig_;
        std::vector<T> pigs_;
        std::list<D> objects_;
        std::list<S> birds_;
        int birdcount_;
        int score_;
};

#endif
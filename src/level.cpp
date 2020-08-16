#include <algorithm>
#include "Box2D/box2d/box2d.h"

#include "level.hpp"

Level::Level(std::string filename) {

    Filereader info(filename);

    auto temp_pigs = info.GetPigs();
    sort(temp_pigs.begin(), temp_pigs.end(), [](Pig a, Pig b) {return a.pos < b.pos;});
    for (auto i : info.GetPigs()) {
        //a = b 
        pigs_.push_back(i);
    }

    for (auto i : info.GetBirds()) {
        birds_.push_back(i);
    }
    
    for (auto i : info.GetObjects()) {
        objects_.push_back(i);
    }

    for (auto i : info.GetGround()) {
        ground_.push_back(i);
    }

    cannon_ = info.GetCannon();

    b2Vec2 gravity (0.0f, 10.0f);
    world_->SetGravity(gravity);

    
}
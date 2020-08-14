#include "filereader.hpp"
#include <fstream>

int main() {
    
    Filereader file("test.txt");

    auto cannon = file.GetCannon();
    auto pig = file.GetPigs();
    auto bird = file.GetBirds();
    auto object = file.GetObjects();
    auto ground = file.GetGround();
    
    std::cout << "Amount of pigs: " << pig.size() << std::endl;
    std::cout << "Amount of birds: " << bird.size() << std::endl;
    std::cout << "Amount of objects: " << object.size() << std::endl;
    std::cout << "Amount of groundpoints: " << ground.size() << std::endl;

    std::cout << std::endl;
    std::cout << "Cannon:" << std::endl;
    std::cout << cannon.x << " " << cannon.y << std::endl;

    std::cout << std::endl;
    std::cout << "Pigs:" << std::endl;
    
    for (auto i : pig) {
        std::cout << i.type << " " << i.pos << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Birds:" << std::endl;

    for (auto i : bird) {
        std::cout << i.type << " " << i.x << " " << i.y << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Objects:" << std::endl;

    for (auto i : object) {
        std::cout << i.type << " " << i.x << " " << i.y << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Groundpoints:" << std::endl;
    
    for (auto i: ground) {
        std::cout << i.x << " " << i.y << std::endl;
    }

    return 1;

}
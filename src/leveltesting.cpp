#include "level.hpp"

#include <iostream>
#include <list>
#include <vector>


int main() {
    Level test("test.txt");
    std::cout << test.GetPigs().size() << std::endl;
    for (auto i : test.GetPigs()) {
        std::cout << i.type << std::endl;
    }
}
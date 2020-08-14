#include "level.hpp"

#include <iostream>
#include <list>
#include <vector>


int main() {
    std::vector<int> pig = {1,2,3};
    std::list<int> object = {2,1,4};
    std::list<int> bird = {1,2,3};
    //Level<std::vector<int>, std::list<int>, std::list<int>> 
    auto test = Level<int,int,int>(pig, object, bird);

    std::cout << test.GetBirdcount() << std::endl;
    std::cout << test.GetPigs() << std::endl;

    std::cout << test.NextPig() << std::endl;
    std::cout << test.ReduceBirdcount() << std::endl;

    std::cout << test.GetBirdcount() << std::endl;
    std::cout << test.GetPigs() << std::endl;

    std::cout << test.NextPig() << std::endl;
    std::cout << test.ReduceBirdcount() << std::endl;

    std::cout << test.GetBirdcount() << std::endl;
    std::cout << test.GetPigs() << std::endl;

    std::cout << test.NextPig() << std::endl;
    std::cout << test.ReduceBirdcount() << std::endl;

    std::cout << test.GetBirdcount() << std::endl;
    std::cout << test.GetPigs() << std::endl;
}
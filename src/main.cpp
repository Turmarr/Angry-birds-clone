#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "level.hpp"

int main(){


    Level test("Levels/test.txt");
    

    sf::RenderWindow window(sf::VideoMode(1000, 750), "Testing for enemies");
    
    window.setFramerateLimit(60);
    //Bird bird = Bird(100.f, 100.f);
    
    
    //std::cout << test.world_->GetBodyCount() << std::endl;
    //Game loop
    while (window.isOpen()){
        test.Simulate();
        sf::Event ev;
        while(window.pollEvent(ev))
        {
            
            State result = test.Update(window, ev);
            if (result.i == 1) {
            window.close();
            }
            
            
        }

        test.DrawLevel(window);

    }

    return 0;
}

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "level.hpp"

int main(){


    Level test("../src/Levels/test.txt");
    

    sf::RenderWindow window(sf::VideoMode(1000, 750), "Testing for enemies");
    
    window.setFramerateLimit(60);
    //Bird bird = Bird(100.f, 100.f);
    
    State result;
    //std::cout << test.world_->GetBodyCount() << std::endl;
    //Game loop
    while (window.isOpen()){
        test.Simulate();
        sf::Event ev;
        
        while(window.pollEvent(ev))
        {   
            if(ev.type == sf::Event::Closed) {
                window.close();
            }
            if (result.i != 5) {
                result = test.Update(window, ev);
            }
            if (result.i == 1) {
                window.close();
            }
            if (result.i == 5) {
                if (result.points != -1) {
                    std::string f = result.file;
                    std::cout << result.points << result.file << std::endl;
                }
                else {
                    std::cout << result.points << std::endl;
                }
                
            }
            
            
        }

        test.DrawLevel(window);

    }

    return 0;
}

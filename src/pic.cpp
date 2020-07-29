#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main(){
    sf::Texture texture;
    if(!texture.loadFromFile("Textures/bird.png")){
        std::cout<< "Error when loading image."<<std::endl;
    }
    else
    {
        std::cout <<"Works!" << std::endl;
    }
    
    sf::Sprite shape;
    shape.setPosition(200.f, 200.f);
    shape.setTexture(texture);
    shape.scale(sf::Vector2f(0.5f, 0.5f));


    sf::RenderWindow window(sf::VideoMode(800, 600), "Testing for enemies", sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev;
    window.setFramerateLimit(60);

    //Game loop
    while (window.isOpen()){

        while(window.pollEvent(ev))
        {
            switch (ev.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                
            }
        }

    //Update

    //Render
    window.clear(); //clears old frame

    //Draw here
    window.draw(shape);

    window.display();  //displays the window after draw

    }


    return 0;
}
#include <SFML/Graphics.hpp>
#include "chip8.h"


int main()
{
    Chip8 chip8;
    chip8.decode();
    

    // auto window = sf::RenderWindow(sf::VideoMode({1280, 720u}), "CMake SFML Project");
    // window.setFramerateLimit(60);

    // while (window.isOpen())
    // {
    //     while (const std::optional event = window.pollEvent())
    //     {
    //         if (event->is<sf::Event::Closed>())
    //         {
    //             window.close();
    //         }
    //     }

    //     window.clear();
    //     window.display();
    // }
}

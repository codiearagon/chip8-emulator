#include "chip8.h"
#include <filesystem>
#include <iostream>

int main()
{
    // std::cout << std::filesystem::current_path() << std::endl;
    sf::RenderWindow window;
    Chip8 chip8(window);
    chip8.loadRom("ibmlogo.ch8");
    chip8.run();
    // chip8.decode();
}

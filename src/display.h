#include <SFML/Graphics.hpp>
#include "memory.h"

#ifndef WIDTH
#define WIDTH 64
#endif

#ifndef HEIGHT
#define HEIGHT 32
#endif

class Display {
    
    public:
        Display();
        ~Display();
        sf::Sprite* getScreenSprite();

        void setMemory(Memory& memory_);
        void updateSprite(uint8_t* V, uint16_t& ir, uint8_t x, uint8_t y, uint8_t height);
        void togglePixel(uint8_t x, uint8_t y);
        void clearScreen();
        bool isPixelOn(uint8_t x, uint8_t y);

    private:
        Memory memory;
        sf::Image gameImage;
        sf::Texture gameTexture;
        sf::Sprite* gameSprite;
        sf::RenderWindow window;
};
#include "display.h"
#include <iostream>

Display::Display() {
    gameImage.resize({WIDTH, HEIGHT}, sf::Color::Black);
    gameTexture.loadFromImage(gameImage);
    gameSprite = new sf::Sprite(gameTexture);
}

Display::~Display() {
    delete gameSprite;
}

sf::Sprite* Display::getScreenSprite() {
    return gameSprite;
}

void Display::setMemory(Memory& memory_) {
    memory = memory_;
}

void Display::updateSprite(uint8_t* V, uint16_t& ir, uint8_t x, uint8_t y, uint8_t height) {
    uint8_t vx = V[x] % 64;
    uint8_t vy = V[y] % 32;
    V[0xF] = 0x0;

    std::cout << "Update Sprite... " << std::endl;

    for(int row = 0; row < height; row++) {
        int spriteData = memory.read(ir + row);

        for(int col = 0; col < 8; col++) {
            if((spriteData & (0x80 >> col)) != 0) {
                if(isPixelOn(vx, vy))
                    V[0xF] = 0x1;
                
                togglePixel(vx, vy);
            }

            vx++;

            if(vx >= WIDTH)
                break;
        }

        vx = V[x] % 64;
        vy++;

        if(vy >= HEIGHT)
            break;
    }

    gameTexture.update(gameImage);
    gameSprite->setTexture(gameTexture);
}

void Display::togglePixel(uint8_t x, uint8_t y) {
    if(gameImage.getPixel({x, y}) == sf::Color::White) {
        gameImage.setPixel({x, y}, sf::Color::Black);
    } else if(gameImage.getPixel({x, y}) == sf::Color::Black) {
        gameImage.setPixel({x, y}, sf::Color::White);
    }
}

void Display::clearScreen() {
    gameImage.resize({WIDTH, HEIGHT}, sf::Color::Black);
    gameTexture.update(gameImage);
    gameSprite->setTexture(gameTexture);
}

bool Display::isPixelOn(uint8_t x, uint8_t y) {
    if(gameImage.getPixel({x, y}) == sf::Color::White)
        return true;
    return false;
}
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
    V[0xF] = 0x0;
    int n = memory.read(ir);
    
    for(uint8_t i = 0; i < height; i++) {
        togglePixel(V, x, height - i);
    }

    gameTexture.update(gameImage);
    gameSprite->setTexture(gameTexture);
}

void Display::togglePixel(uint8_t* V, uint8_t x, uint8_t y) {
    if(gameImage.getPixel({x, y}) == sf::Color::White) {
        gameImage.setPixel({x, y}, sf::Color::Black);
        V[0xF] = 0x1;
    } else if(gameImage.getPixel({x, y}) == sf::Color::Black) {
        gameImage.setPixel({x, y}, sf::Color::White);
    }
}

void Display::clearScreen() {
    gameImage.resize({WIDTH, HEIGHT}, sf::Color::Black);
    gameTexture.update(gameImage);
    gameSprite->setTexture(gameTexture);
}
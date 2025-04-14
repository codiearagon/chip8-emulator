#include "chip8.h"
#include <iostream>
#include <fstream>

Chip8::Chip8(sf::RenderWindow& window_) {
    display.setMemory(memory);
    window = &window_;
    gameView = new sf::View(sf::FloatRect({{0, 0}, {WIDTH, HEIGHT}}));
    window->create(sf::VideoMode({WIDTH*5, HEIGHT*5}), "CHIP8 Interpreter", sf::Style::Close | sf::Style::Titlebar);
    window->setView(*gameView);

    pc = 0x0;
}

Chip8::~Chip8() {
    delete gameView;
}

void Chip8::loadRom(std::string fileName) {
    std::ifstream romFile(fileName, std::ios::binary | std::ios::ate);
    if (!romFile) {
        std::cout << "File could not be opened" << std::endl;
    }

    if (romFile.is_open())
	{
		// Get size of file and allocate a buffer to hold the contents
		std::streampos size = romFile.tellg();
		char* buffer = new char[size];

		// Go back to the beginning of the file and fill the buffer
		romFile.seekg(0, std::ios::beg);
		romFile.read(buffer, size);
		romFile.close();

		// Load the ROM contents into the Chip8's memory, starting at 0x200
		for (long i = 0; i < size; ++i)
		{
			memory.write(0x200 + i, buffer[i]);
		}

		// Free the buffer
		delete[] buffer;
	}


    // std::string line;

    // while(std::getline(romFile, line)) {
    //     std::cout << std::hex << line << std::endl;
    // }
}

uint16_t Chip8::fetch() {
    uint8_t inst1 = memory.read(pc);
    uint8_t inst2 = memory.read(pc + 1);
    uint16_t instruction = (inst1 << 8) | inst2; // Combine two bytes into one instruction
    pc += 2; // move to next opcode

    return instruction;
}

void Chip8::decode() {
    uint16_t instruction = fetch();
    uint16_t firstNibble = (instruction & 0xF000) >> 12;
    uint16_t secondNibble = (instruction & 0x0F00) >> 8;
    uint16_t thirdNibble = (instruction & 0x00F0) >> 4;
    uint16_t fourthNibble = (instruction & 0x000F);

    switch (firstNibble) {
        case 0x0:
            if((instruction & 0x0FFF) == 0x00E0)
                display.clearScreen();
            break;
        case 0x1:
            pc = (instruction & 0x0FFF);
            break;
        case 0x2:
            break;
        case 0x3:
            break;
        case 0x4:
            break;
        case 0x5:
            break;
        case 0x6:
            V[secondNibble] = (instruction & 0x00FF);
            break;
        case 0x7:
            V[secondNibble] += (instruction & 0x00FF);
            break;
        case 0x8:
            break;
        case 0x9:
            break;
        case 0xA:
            ir = (instruction & 0x0FFF);
            break;
        case 0xB:
            break;
        case 0xC:
            break;
        case 0xD:
            display.updateSprite(V, ir, V[secondNibble] % 64, V[thirdNibble] % 32, fourthNibble);
            break;
        case 0xE:
            break;
        case 0xF:
            break;
    }
}

void Chip8::run() {
    window->setFramerateLimit(60);

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
        }
        // std::cout << std::hex << pc << std::endl;
        window->clear();
        decode();
        window->draw(*display.getScreenSprite());
        window->display();
    }
}

int Chip8::convertToDecimal(uint8_t byte) {
    int decimalValue = 0;

    for (int i = 0; i < 8; ++i) {
        
        if((byte >> i) & 1)
            decimalValue += (1 << i);
    }

    return decimalValue;
}
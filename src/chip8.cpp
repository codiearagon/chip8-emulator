#include "chip8.h"
#include <iostream>

Chip8::Chip8() {
    pc = 0x000;
    memory.write(0x000, 0x7A);
    memory.write(0x001, 0xE2);
}

Chip8::~Chip8() {}

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

    // std::cout << std::hex << instruction << std::endl;
    // std::cout << std::hex << firstNibble << std::endl;
    // std::cout << std::hex << secondNibble << std::endl;
    // std::cout << std::hex << thirdNibble << std::endl;
    // std::cout << std::hex << fourthNibble << std::endl;

    switch (firstNibble) {
        case 0x0:
            if((instruction & 0x0FFF) == 0x00E0)
                std::cout << "clear screen!" << std::endl;
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
            std::cout << std::hex << +V[secondNibble] << std::endl;
            break;
        case 0x8:
            break;
        case 0x9:
            std::cout << "yerrr!" << std::endl;
            break;
        case 0xA:
            ir = (instruction & 0x0FFF);
            break;
        case 0xB:
            break;
        case 0xC:
            break;
        case 0xD:
            
            break;
        case 0xE:
            break;
        case 0xF:
            break;
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
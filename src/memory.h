#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <array>

class Memory {
    public:
        Memory();
        ~Memory();

        uint8_t read(uint16_t address) const;
        void write(uint16_t address, uint8_t value);

    private:
        std::array<uint8_t, 4096> memory; // 4KB of memory

        void initializeFont();
};
#endif
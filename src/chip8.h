#include <stack>
#include <vector>
#include "memory.h"
// #include "soundtimer.h"
// #include "delaytimer.h"
// #include "display.h"

class Chip8 {
    public:
        Chip8();
        ~Chip8();

        uint16_t fetch();
        void decode();
        void execute();

    private:
        Memory memory;
        // Display display;
        uint16_t pc; // Program Counter
        uint16_t ir; // Instruction Register
        std::stack<uint16_t> stack;

        uint8_t V[16]; // 16 registers (V0 to VF)

        int convertToDecimal(uint8_t byte);
};
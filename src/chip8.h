#include <stack>
#include <vector>
#include <SFML/Graphics.hpp>
#include "memory.h"
#include "display.h"

class Chip8 {
    public:
        Chip8(sf::RenderWindow& window_);
        ~Chip8();

        void loadRom(std::string fileName);
        uint16_t fetch();
        void decode();
        void execute();

        void run();

    private:
        Memory memory;
        Display display;
        uint16_t pc; // Program Counter
        uint16_t ir; // Instruction Register
        std::stack<uint16_t> stack;

        sf::View* gameView;
        sf::RenderWindow* window;

        uint8_t V[16]; // 16 registers (V0 to VF)

        int convertToDecimal(uint8_t byte);
};
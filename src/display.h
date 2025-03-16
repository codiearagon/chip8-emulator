#include <SFML/Graphics.hpp>
#include <cstdint>

class Display {
    public:
        Display();
        ~Display();

        void clear();
        void drawPixel(uint64_t x, uint32_t y, bool color);
    private:
        uint64_t width;
        uint32_t height;
};
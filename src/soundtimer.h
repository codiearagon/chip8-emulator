#include <cstdint>

class SoundTimer {
    public:
        SoundTimer();
        uint8_t getTime() const;
    private:
        uint8_t time;
};
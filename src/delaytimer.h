#include <cstdint>

class DelayTimer {
    public:
        DelayTimer();
        uint8_t getTime() const;
    private:
        uint8_t time;
};
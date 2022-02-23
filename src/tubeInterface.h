#ifndef TUBE_INTERFACE
#define TUBE_INTERFACE

#define PIN_DIN 16
#define PIN_CLK 17
#define PIN_LOA 18
#define PIN_BLK 12

#include <Arduino.h>

class TubeInterface {
    public:
        TubeInterface();

        void Push();
        void Update(uint8_t, int16_t);
    private:
        uint8_t anode;

        enum Characters : int8_t {
            CHAR_0 = 0b1111110,
            CHAR_1 = 0b0110000, // Right-hand
            CHAR_2 = 0b1101101,
            CHAR_3 = 0b1111001,
            CHAR_4 = 0b0110011,
            CHAR_5 = 0b1011011,
            CHAR_6 = 0b0011111,
            CHAR_7 = 0b1110000,
            CHAR_8 = 0b1111111,
            CHAR_9 = 0b1110011
        };
};

#endif
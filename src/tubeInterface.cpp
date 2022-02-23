#include <tubeInterface.h>

TubeInterface::TubeInterface() {
    pinMode(PIN_DIN, OUTPUT);
    pinMode(PIN_CLK, OUTPUT);
    pinMode(PIN_LOA, OUTPUT);
    pinMode(PIN_BLK, OUTPUT);

    digitalWrite(PIN_BLK, LOW);
}

void TubeInterface::Push() {
    digitalWrite(PIN_LOA, HIGH);
    shiftOut(PIN_DIN, PIN_CLK, MSBFIRST, 0b00000000);
    digitalWrite(PIN_LOA, LOW);
}

void TubeInterface::Update(uint8_t Anode, int16_t Segments) {
    this->anode = Anode;
}
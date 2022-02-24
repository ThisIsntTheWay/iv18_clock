#include <tubeInterface.h>

TubeInterface::TubeInterface() {
    pinMode(PIN_DIN, OUTPUT);
    pinMode(PIN_CLK, OUTPUT);
    pinMode(PIN_LOA, OUTPUT);
    pinMode(PIN_BLK, OUTPUT);

    digitalWrite(PIN_BLK, LOW);
}

void TubeInterface::Push(int8_t targetChar) {
    int16_t bytesToPush = this->assemble(static_cast<Characters>(targetChar));

    digitalWrite(PIN_LOA, HIGH);
    shiftOut(PIN_DIN, PIN_CLK, MSBFIRST, bytesToPush);
    digitalWrite(PIN_LOA, LOW);
}

void TubeInterface::Update(uint8_t Anode, int16_t Segments) {
    this->anode = Anode;
}

int16_t TubeInterface::assemble(Characters targetChar) {
    //int16_t fullMask = 0b00000000000000000; // 17 zeroes
    int16_t anodeMask = 1 << (8 + this->anode); // Anodes are OUT8 - OUT16 of SR
    return anodeMask & targetChar;
}
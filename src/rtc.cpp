#include <rtc.h>

Rtc::Rtc(int8_t address) {
    this->i2cAddr = address;
}

void Rtc::Begin() {
    Wire.begin();
}

uint8_t Rtc::GetTime(int8_t which) {
    // 0 -> sec, 1 -> min, 2 -> hour
    if (which > 2) {
        throw "GetTime(): which out of bounds.";
    }
    
    // By using static_cast, we can get the enum val by index
    return this->readByte(static_cast<rtcRegisters>(which));
}

uint8_t Rtc::readByte(rtcRegisters reg) {
    Wire.beginTransmission(this->i2cAddr);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(this->i2cAddr, (uint8_t) 1); // Or just '8'
    return Wire.read();
}

void Rtc::setTimeFlag(bool state) {
    // Toggle between 12hr and 24hr clock
    rtcRegisters reg = REGISTER_CONTROL;
    uint8_t flag = this->readByte(REGISTER_CONTROL);
    
    // Set 5th bit to value of state (either 0 or 1)
    flag ^= (-state ^ flag) & (1UL << 5);

    Wire.beginTransmission(this->i2cAddr);
    Wire.write(reg);
    Wire.write(flag);
    Wire.endTransmission();
}

bool Rtc::getTimeFlag() {
    rtcRegisters reg = REGISTER_CONTROL;

    uint8_t flag = this->readByte(REGISTER_CONTROL);

    // Isolate 5th bit by shifting to right and ANDing it using 0b0
    return (bool) (flag >> 5) & 1U;
}

uint8_t Rtc::bcdToDec(int8_t bcdVal) {
    return ((bcdVal / 0x10) * 10) + (bcdVal % 0x10);
}

uint8_t Rtc::decToBcd(int8_t decVal) {
    return ((decVal / 0x10 * 10) + (decVal % 0x10));
}
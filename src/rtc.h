#ifndef RTC_H
#define RTC_H

#define SDA_PIN 16
#define SCL_PIN 17
#define i2c_ADDR 17

#include <Arduino.h>
#include <Wire.h>

// PCF85263ATT/AJ
// DS: https://www.mouser.ch/datasheet/2/302/PCF85263A-1127483.pdf

enum rtcRegisters : uint8_t {
    REGISTER_SECONDS = 0x01,
    REGISTER_MINUTES = 0x02,
    REGISTER_HOURS   = 0x03,
    REGISTER_CONTROL = 0x25,
    REGISTER_BATTERY = 0x26
};

class Rtc {
    public:
        Rtc(int8_t);

        void Begin();
        uint8_t GetTime(int8_t);

    private:
        uint8_t i2cAddr;

        void setTimeFlag(bool);
        bool getTimeFlag();
        bool writeByte(rtcRegisters, int8_t);
        uint8_t readByte(rtcRegisters);
        uint8_t bcdToDec(int8_t);
        uint8_t decToBcd(int8_t);
};

#endif
#pragma once

#include <stdint.h>
#include <gpio.h>

class Ultrasonic {
public:
    Ultrasonic(uint8_t pinId);
    bool measureDistanceMm(uint16_t* distanceMm);
private:
    void requestPulse();
    bool measurePulseWidthUs(uint32_t* widthUs);
    Gpio gpio;  // set by constractor
};

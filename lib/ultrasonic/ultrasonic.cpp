#include <Arduino.h>
#include <ultrasonic.h>

Ultrasonic::Ultrasonic(uint8_t pinId) : gpio(pinId) {
}

bool Ultrasonic::measureDistanceMm(uint16_t* distanceMm) {
    this->requestPulse();
    uint32_t widthUs;
    if (!this->measurePulseWidthUs(&widthUs)) return false;
    *distanceMm = widthUs / (2 / 340e-3);  // round trip of sound 340 m/s
    return true;
}

void Ultrasonic::requestPulse() {
    gpio.output(false);
    delayMicroseconds(2);
    gpio.output(true);
    delayMicroseconds(5);
    gpio.output(false);
}

bool Ultrasonic::measurePulseWidthUs(uint32_t* widthUs) {
    constexpr uint32_t timeoutUs = 100ul * 1000;
    const uint32_t startedUs = micros();
    while (gpio.input()) {
        if (micros() - startedUs > timeoutUs) return false;
    }
    while (!gpio.input()) {
        if (micros() - startedUs > timeoutUs) return false;
    }
    const uint32_t pulseStartedUs = micros();
    while (gpio.input()) {
        if (micros() - startedUs > timeoutUs) return false;
    }
    *widthUs = micros() - pulseStartedUs;
    return true;
}

#include <Arduino.h>
#include <servomotor.h>

ServoMotor::ServoMotor(uint8_t pinId) {
    constexpr uint16_t SG90_minPulseWidthUs = 600;
    constexpr uint16_t SG90_maxPulseWidthUs = 2350;
    this->servo.attach(pinId, max(MIN_PULSE_WIDTH, SG90_minPulseWidthUs), min(MAX_PULSE_WIDTH, SG90_maxPulseWidthUs));
}

uint8_t ServoMotor::getAngle() {
    return this->servo.read();
}

void ServoMotor::setAngle(uint8_t angle) {
    this->servo.write(angle);
}

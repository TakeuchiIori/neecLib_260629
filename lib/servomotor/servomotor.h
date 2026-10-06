#pragma once

#include <Servo.h>

class ServoMotor {
public:
    ServoMotor(uint8_t pinId);
    uint8_t getAngle();  // 0~180
    void setAngle(uint8_t angle);  // 0~180
private:
    Servo servo;
};

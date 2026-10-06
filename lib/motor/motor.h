#pragma once

#include <i2c.h>

class Motor {
public:
    enum class Address : uint8_t { CH1 = 0x65, CH2 = 0x60 };
    Motor(I2c* i2c, Address address = Address::CH1);
    bool drive(float voltage);
    bool brake();
    float maxVoltage = 3;
private:
    struct Reg {
        struct Control {
            static constexpr uint8_t ADDR = 0x00;
            struct Vset {  // bit[7:2]
                static constexpr uint8_t SHIFT = 2;
                static constexpr uint8_t MIN = 0x06;
                static constexpr uint8_t MAX = 0x3f;
            };
            struct Bridge {  // bit[1:0]
                static constexpr uint8_t COAST = 0x00;
                static constexpr uint8_t FORWARD = 0x01;
                static constexpr uint8_t REVERSE = 0x02;
                static constexpr uint8_t BRAKE = 0x03;
            };
        };
    };
    I2c* i2c;  // set by constructor
    uint8_t address;  // set by constructor
};

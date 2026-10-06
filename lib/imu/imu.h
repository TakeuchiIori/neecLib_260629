#pragma once

#include <i2c.h>
#include <vector3.h>

class Imu {
public:
    enum class Address : uint8_t { OPTION1 = 0x69, OPTION2 = 0x68 };
    Imu(I2c* i2c, Address address = Address::OPTION1);
    bool init();
    bool getAccelG(Vector3* vector);
    bool getGyroDps(Vector3* vector);
    bool getTemperature(float* value);
    bool getAccelGyroRaw(int16_t* values);
    bool getAccelRaw(int16_t* values);
    bool getAccelRawX(int16_t* value);
    bool getAccelRawY(int16_t* value);
    bool getAccelRawZ(int16_t* value);
private:
    struct Reg {
        struct Config {
            static constexpr uint8_t ADDR = 0x1a;
            struct DlpfCfg {  // bit[2:0]
                static constexpr uint8_t GYRO_176HZ = 1;
            };
        };
        struct GyroConfig {
            static constexpr uint8_t ADDR = 0x1b;
            struct FsSel {  // bit[4:3]
                static constexpr uint8_t SHIFT = 3;
                static constexpr uint8_t DPS_2000 = 0b11 << SHIFT;
            };
        };
        struct AccelConfig {
            static constexpr uint8_t ADDR = 0x1c;
            struct AccelFsSel {  // bit[4:3]
                static constexpr uint8_t SHIFT = 3;
                static constexpr uint8_t G_16 = 0b11 << SHIFT;
            };
        };
        struct AccelConfig2 {
            static constexpr uint8_t ADDR = 0x1d;
            struct ADlpfCfg {  // bit[2:0]
                static constexpr uint8_t HZ_420 = 7;
            };
        };
        struct AccelXoutH {
            static constexpr uint8_t ADDR = 0x3b;
        };
        struct AccelYoutH {
            static constexpr uint8_t ADDR = 0x3d;
        };
        struct AccelZoutH {
            static constexpr uint8_t ADDR = 0x3f;
        };
        struct TempOutH {
            static constexpr uint8_t ADDR = 0x41;
        };
        struct GyroXoutH {
            static constexpr uint8_t ADDR = 0x43;
        };
        struct PwrMgmt1 {
            static constexpr uint8_t ADDR = 0x6b;
            struct Clksel {  // bit[2:0]
                static constexpr uint8_t AUTO_FULL_GYRO = 1;
            };
        };
    };
    I2c* i2c;  // set by constructor
    uint8_t address;  // set by constructor
};

#pragma once

#include <stdint.h>
#include <vector3.h>

class I2c {
public:
    I2c(bool isFastMode = false);
    ~I2c();
    void reset();
    bool read(uint8_t address, uint8_t reg, uint8_t* data, uint8_t length = 1);
    bool readValues(uint8_t address, uint8_t reg, int16_t* values, uint8_t length, bool isLittleEndian = true);
    bool readValues(uint8_t address, uint8_t reg, float* values, uint8_t length, bool isLittleEndian = true);
    bool readVector(uint8_t address, uint8_t reg, Vector3* vector, bool isLittleEndian = true);
    bool write(uint8_t address, uint8_t reg);
    bool write(uint8_t address, uint8_t reg, uint8_t data);
    bool setChannel(uint8_t channel);
    bool setChannelMap(uint8_t channelMap);
    static constexpr uint8_t CHANNEL_COUNT = 8;
private:
    static constexpr uint8_t MULTIPLEXER = 0x70;
    bool isFastMode;  // set by constructor
};

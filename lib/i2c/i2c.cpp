#include <Arduino.h>
#include <Wire.h>
#include <i2c.h>

I2c::I2c(bool isFastMode) : isFastMode(isFastMode) {
    this->reset();
}

I2c::~I2c() {
    Wire.end();
}

void I2c::reset() {
    Wire.end();

    // ----- Receive reply -----
    pinMode(SDA, INPUT_PULLUP);
    pinMode(SCL, OUTPUT);
    digitalWrite(SCL, HIGH);
    for (uint8_t i = 0; i < 10; i++) {
        digitalWrite(SCL, LOW);
        delayMicroseconds(5);
        digitalWrite(SCL, HIGH);
        delayMicroseconds(5);
    }

    // ----- Send stop -----
    digitalWrite(SCL, LOW);
    delayMicroseconds(5);
    pinMode(SDA, OUTPUT);
    digitalWrite(SDA, LOW);
    delayMicroseconds(5);
    digitalWrite(SCL, HIGH);
    delayMicroseconds(5);
    digitalWrite(SDA, HIGH);
    delayMicroseconds(5);

    Wire.begin();
    Wire.setClock(this->isFastMode ? 400000 : 100000);
}

bool I2c::read(uint8_t address, uint8_t reg, uint8_t* data, uint8_t length) {
    if (!this->write(address, reg)) return false;
    const uint8_t receivedLength = Wire.requestFrom(address, static_cast<size_t>(length));
    for (uint8_t* p = data; p < data + min(receivedLength, length); p++) {
        *p = Wire.read();
    }
    while (Wire.available()) {
        Wire.read();
    }
    return receivedLength >= length;
}

bool I2c::readValues(uint8_t address, uint8_t reg, int16_t* values, uint8_t length, bool isLittleEndian) {
    uint8_t data[2 * length];
    if (!this->read(address, reg, data, sizeof(data))) return false;
    for (uint8_t i = 0; i < length; i++) {
        if (isLittleEndian) {
            values[i] = static_cast<uint16_t>(data[i * 2 + 1]) << 8 | data[i * 2];
        } else {
            values[i] = static_cast<uint16_t>(data[i * 2]) << 8 | data[i * 2 + 1];
        }
    }
    return true;
}

bool I2c::readValues(uint8_t address, uint8_t reg, float* values, uint8_t length, bool isLittleEndian) {
    int16_t int16_values[length];
    if (!this->readValues(address, reg, int16_values, length, isLittleEndian)) return false;
    for (uint8_t i = 0; i < length; i++) {
        values[i] = int16_values[i];
    }
    return true;
}

bool I2c::readVector(uint8_t address, uint8_t reg, Vector3* vector, bool isLittleEndian) {
    int16_t int16_values[3];
    if (!this->readValues(address, reg, int16_values, 3, isLittleEndian)) return false;
    vector->set(int16_values[0], int16_values[1], int16_values[2]);
    return true;
}

bool I2c::write(uint8_t address, uint8_t reg) {
    Wire.beginTransmission(address);
    bool isOk = Wire.write(reg) == 1;
    isOk &= Wire.endTransmission() == 0;
    return isOk;
}

bool I2c::write(uint8_t address, uint8_t reg, uint8_t data) {
    Wire.beginTransmission(address);
    bool isOk = Wire.write(reg) == 1 && Wire.write(data) == 1;
    isOk &= Wire.endTransmission() == 0;
    return isOk;
}

bool I2c::setChannel(uint8_t channel) {
    if (channel >= I2c::CHANNEL_COUNT) return false;
    return this->write(MULTIPLEXER, 1 << channel);
}

bool I2c::setChannelMap(uint8_t channelMap) {
    return this->write(MULTIPLEXER, channelMap);
}

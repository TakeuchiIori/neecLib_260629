#include <Arduino.h>
#include <imu.h>

Imu::Imu(I2c* i2c, Address address) : i2c(i2c), address(static_cast<uint8_t>(address)) {
}

bool Imu::init() {
    if (!(this->i2c->write(this->address, Reg::Config::ADDR, Reg::Config::DlpfCfg::GYRO_176HZ) &&
        this->i2c->write(this->address, Reg::GyroConfig::ADDR, Reg::GyroConfig::FsSel::DPS_2000) &&
        this->i2c->write(this->address, Reg::AccelConfig::ADDR, Reg::AccelConfig::AccelFsSel::G_16) &&
        this->i2c->write(this->address, Reg::AccelConfig2::ADDR, Reg::AccelConfig2::ADlpfCfg::HZ_420) &&
        this->i2c->write(this->address, Reg::PwrMgmt1::ADDR, Reg::PwrMgmt1::Clksel::AUTO_FULL_GYRO))) return false;
    constexpr uint8_t accelStartupMs = 20;  // icm-20600.pdf, p.10
    delay(accelStartupMs);
    return true;
}

bool Imu::getAccelG(Vector3* vector) {
    if (!this->i2c->readVector(this->address, Reg::AccelXoutH::ADDR, vector, false)) return false;
    constexpr float lsbPerG_16g = 2048;
    *vector /= lsbPerG_16g;
    return true;
}

bool Imu::getGyroDps(Vector3* vector) {
    if (!this->i2c->readVector(this->address, Reg::GyroXoutH::ADDR, vector, false)) return false;
    constexpr float lsbPerDps_2k = 16.4;
    *vector /= lsbPerDps_2k;
    return true;
}

bool Imu::getTemperature(float* value) {
    if (!this->i2c->readValues(this->address, Reg::TempOutH::ADDR, value, 1, false)) return false;
    constexpr float lsbPerC = 326.8;
    constexpr float offsetC = 25;
    *value = *value / lsbPerC + offsetC;
    return true;
}

bool Imu::getAccelGyroRaw(int16_t* values) {
    int16_t data[7];  // accel[0..2], temp[3], gyro[4..6]
    if (!this->i2c->readValues(this->address, Reg::AccelXoutH::ADDR, data, 7, false)) return false;
    memcpy(values, data, sizeof(int16_t) * 3);
    memcpy(values + 3, data + 4, sizeof(int16_t) * 3);
    return true;
}

bool Imu::getAccelRaw(int16_t* values) {
    return this->i2c->readValues(this->address, Reg::AccelXoutH::ADDR, values, 3, false);
}

bool Imu::getAccelRawX(int16_t* value) {
    return this->i2c->readValues(this->address, Reg::AccelXoutH::ADDR, value, 1, false);
}

bool Imu::getAccelRawY(int16_t* value) {
    return this->i2c->readValues(this->address, Reg::AccelYoutH::ADDR, value, 1, false);
}

bool Imu::getAccelRawZ(int16_t* value) {
    return this->i2c->readValues(this->address, Reg::AccelZoutH::ADDR, value, 1, false);
}

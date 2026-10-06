#include <Arduino.h>
#include <motor.h>

Motor::Motor(I2c* i2c, Address address) : i2c(i2c), address(static_cast<uint8_t>(address)) {
}

bool Motor::drive(float voltage) {
    constexpr float voltagePerLsb = 4 * 1.285 / 64;  // DRV8830.pdf, p.10: 4 * VREF / 64
    const float absoluteVoltage = constrain(fabs(voltage), 0, this->maxVoltage);
    const uint8_t vset = min(absoluteVoltage / voltagePerLsb, static_cast<float>(Reg::Control::Vset::MAX));

    uint8_t control = Reg::Control::Bridge::COAST;
    if (vset >= Reg::Control::Vset::MIN) {
        const uint8_t bridge = voltage >= 0 ? Reg::Control::Bridge::FORWARD : Reg::Control::Bridge::REVERSE;
        control = (vset << Reg::Control::Vset::SHIFT) + bridge;
    }
    return this->i2c->write(this->address, Reg::Control::ADDR, control);
}

bool Motor::brake() {
    return this->i2c->write(this->address, Reg::Control::ADDR, Reg::Control::Bridge::BRAKE);
}

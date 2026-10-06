#include <Arduino.h>
#include <gpio.h>

Gpio::Gpio(uint8_t pinId) : pinId(pinId) {
    pinMode(this->pinId, INPUT);
}

Gpio::~Gpio() {
    this->detachPin();
    pinMode(this->pinId, INPUT);
}

Gpio::Mode Gpio::getMode() {
    return this->mode;
}

void Gpio::setMode(Mode mode) {
    if (mode == this->mode) return;
    this->detachPin();
    this->mode = mode;
    if (this->mode == Mode::IN) {
        pinMode(this->pinId, this->isPullupEnabled ? INPUT_PULLUP : INPUT);
    } else {
        pinMode(this->pinId, OUTPUT);
    }
}

bool Gpio::input() {
    this->setMode(Mode::IN);
    return digitalRead(this->pinId) == HIGH;
}

uint16_t Gpio::inputAnalog() {
    this->setMode(Mode::IN);
    return analogRead(this->pinId);
}

void Gpio::enablePullup(bool enabled) {
    this->isPullupEnabled = enabled;
    if (this->mode == Mode::IN) {
        pinMode(this->pinId, this->isPullupEnabled ? INPUT_PULLUP : INPUT);
    } else {
        this->setMode(Mode::IN);
    }
}

void Gpio::setInterrupt(void (*isr)(void), Edge edge) {
    this->setMode(Mode::IN);
    if (isr) {
        #ifdef ARDUINO_ARCH_MEGAAVR
        const PinStatus edges[] = { PinStatus::CHANGE, PinStatus::FALLING, PinStatus::RISING };
        #else
        const uint8_t edges[] = { CHANGE, FALLING, RISING };
        #endif
        attachInterrupt(digitalPinToInterrupt(this->pinId), isr, edges[static_cast<uint8_t>(edge)]);
        this->isInterruptSet = true;
    } else {
        detachPin();
    }
}

void Gpio::output(bool value) {
    this->setMode(Mode::OUT);
    digitalWrite(this->pinId, value ? HIGH : LOW);
}

void Gpio::outputPwm(uint16_t value) {
    this->setMode(Mode::PWM);
    analogWrite(this->pinId, min(value, 255));
}

void Gpio::detachPin() {
    if (this->mode == Mode::IN && this->isInterruptSet) {
        detachInterrupt(digitalPinToInterrupt(this->pinId));
        this->isInterruptSet = false;
    }
}

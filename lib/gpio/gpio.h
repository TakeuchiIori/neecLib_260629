#pragma once

#include <stdint.h>

class Gpio {
public:
    enum class Mode : uint8_t { IN, OUT, PWM };
    enum class Edge : uint8_t { BOTH, FALL, RISE };
    Gpio(uint8_t pinId);
    ~Gpio();
    Mode getMode();
    void setMode(Mode mode);
    bool input();
    uint16_t inputAnalog();  // 0~1023
    void enablePullup(bool enabled);
    void setInterrupt(void (*isr)(void) = nullptr, Edge edge = Edge::BOTH);
    void output(bool value);
    void outputPwm(uint16_t value);  // 0~255
private:
    void detachPin();
    uint8_t pinId;  // set by constructor
    Mode mode = Mode::IN;
    bool isPullupEnabled = false;
    bool isInterruptSet = false;
};

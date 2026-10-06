#pragma once

#include <stdint.h>

namespace Pinout {
    constexpr uint8_t D0_UART_RX = 0;
    constexpr uint8_t D1_UART_TX = 1;
    constexpr uint8_t D2 = 2;
    constexpr uint8_t D3_PWM = 3;
    constexpr uint8_t D4 = 4;
    constexpr uint8_t D5_PWM = 5;
    constexpr uint8_t D6_PWM = 6;
    constexpr uint8_t D7 = 7;
    // constexpr uint8_t D8 = 8;
    // constexpr uint8_t D9_PWM = 9;
    // constexpr uint8_t D10_PWM = 10;
    #if defined(ARDUINO_ARCH_MEGAAVR)
    // constexpr uint8_t D11 = 11;
    #else
    // constexpr uint8_t D11_PWM = 11;
    #endif
    // constexpr uint8_t D12 = 12;
    constexpr uint8_t D13_LED = 13;
    constexpr uint8_t A0 = 14;
    constexpr uint8_t A1 = 15;
    constexpr uint8_t A2 = 16;
    constexpr uint8_t A3 = 17;
    // constexpr uint8_t A4_I2C_SDA = 18;
    // constexpr uint8_t A5_I2C_SCL = 19;
    #if defined(ARDUINO_ARCH_MEGAAVR)
    constexpr uint8_t A6 = 20;
    constexpr uint8_t A7 = 21;
    #else
    constexpr uint8_t A6_AIN = 20;
    constexpr uint8_t A7_AIN = 21;
    #endif
}

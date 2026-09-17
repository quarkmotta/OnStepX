#pragma once

#include <Arduino.h>
#include <Wire.h>

#include "RP2040Pins.h"

#ifndef HAL_VCC
#define HAL_VCC 3.3F
#endif

#define HAL_FRACTIONAL_SEC 100.0F

#define HAL_MAXRATE_LOWER_LIMIT 10.0F
#define HAL_PULSE_WIDTH 10000

#ifndef HAL_WIRE
#define HAL_WIRE Wire
#endif

#ifndef HAL_WIRE_CLOCK
#define HAL_WIRE_CLOCK 400000
#endif

#define HAL_TEMP() (NAN)

#define HAL_RESET() rp2040.reboot()

#ifndef digitalWriteFast
#define digitalWriteFast(pin, value) digitalWrite((pin), (value))
#endif

// Non-volatile storage ----------------------------------------------------------------------------
#if NV_DRIVER == NV_DEFAULT
  #undef NV_DRIVER
  #define E2END 1023
  #define NV_DRIVER NV_EEPROM
#endif

namespace OnStepRP2040 {

static inline void pinModeOutput(uint8_t pin) {
    pinMode(pin, OUTPUT);
}

static inline void writeFast(uint8_t pin, bool state) {
    digitalWriteFast(pin, state ? HIGH : LOW);
}

}

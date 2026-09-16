#pragma once

/*
 * OnStepX HAL - Raspberry Pi RP2040
 *
 * Target:
 *   RP2040 Zero / RP2040 boards
 *   Earle Philhower Arduino-Pico core
 */

#include <Arduino.h>
#include <Wire.h>

// -----------------------------------------------------------------------------
// Timing
// -----------------------------------------------------------------------------

#define HAL_FRACTIONAL_SEC 100.0F

// RP2040 hardware timer/micros() gives us substantially better timing
// resolution than the original Mbed-oriented implementation.

// Minimum step interval in microseconds.
// Start conservatively; this should be benchmarked with the actual driver.
#define HAL_MAXRATE_LOWER_LIMIT 10.0F

// Requested minimum STEP pulse width in nanoseconds.
#define HAL_PULSE_WIDTH 1000

// -----------------------------------------------------------------------------
// ADC / DAC / PWM
// -----------------------------------------------------------------------------

#ifndef HAL_VCC
#define HAL_VCC 3.3F
#endif

#ifndef ANALOG_READ_RANGE
#define ANALOG_READ_RANGE 4095
#endif

#ifndef ANALOG_WRITE_RANGE
#define ANALOG_WRITE_RANGE 255
#endif

// -----------------------------------------------------------------------------
// I2C
// -----------------------------------------------------------------------------

#ifndef HAL_WIRE
#define HAL_WIRE Wire
#endif

#ifndef HAL_WIRE_CLOCK
#define HAL_WIRE_CLOCK 400000
#endif

// -----------------------------------------------------------------------------
// Non-volatile storage
// -----------------------------------------------------------------------------

/*
 * The RP2040 has no EEPROM peripheral.
 *
 * Arduino-Pico provides flash-backed EEPROM emulation.
 *
 * Therefore don't silently select an external AT24C32 as the default.
 */
#if NV_DRIVER == NV_DEFAULT
#undef NV_DRIVER
#define NV_DRIVER NV_NONE
#endif

// -----------------------------------------------------------------------------
// Temperature
// -----------------------------------------------------------------------------

#define HAL_TEMP() (NAN)

// -----------------------------------------------------------------------------
// Reset
// -----------------------------------------------------------------------------

#define HAL_RESET() rp2040.reboot()

// -----------------------------------------------------------------------------
// Platform initialization
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Platform initialization
// -----------------------------------------------------------------------------

#ifndef HAL_INIT
static inline void HAL_INIT() {
    HAL_FAST_TICKS_INIT();
}
#endif


namespace OnStepRP2040 {

static inline void stepHigh(uint8_t pin) {
    digitalWriteFast(pin, HIGH);
}

static inline void stepLow(uint8_t pin) {
    digitalWriteFast(pin, LOW);
}

static inline void stepPulse(uint8_t pin, uint8_t activeState) {

    digitalWriteFast(pin, activeState);

    /*
     * A4988 requires only a very short STEP high/low time.
     * OnStepX's HAL_PULSE_WIDTH remains 10 us for conservative
     * compatibility with different drivers.
     */
    delayNanoseconds(HAL_PULSE_WIDTH);

    digitalWriteFast(pin, activeState ? LOW : HIGH);
}

}

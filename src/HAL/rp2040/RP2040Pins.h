#pragma once

/*
 * Raspberry Pi RP2040 Zero board-level definitions.
 *
 * These are GPIO numbers, not physical header positions.
 */

#ifndef RP2040_ZERO_LED_PIN
  #define RP2040_ZERO_LED_PIN 16
#endif

/*
 * RP2040 GPIO is 3.3V only.
 *
 * Never connect a 5V STEP/DIR signal directly to the RP2040.
 */

#define RP2040_GPIO_COUNT 30

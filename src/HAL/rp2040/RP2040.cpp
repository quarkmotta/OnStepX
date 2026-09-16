#include "RP2040.h"

/*
 * RP2040-specific HAL implementation.
 *
 * The actual high-rate OnStepX scheduler continues to live in the
 * existing axis/motion-control implementation.
 *
 * This file exists so that future RP2040 hardware-specific facilities
 * don't have to be placed into generic HAL headers.
 */

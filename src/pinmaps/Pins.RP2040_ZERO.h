#pragma once

#if defined(ARDUINO_ARCH_RP2040) && !defined(ARDUINO_ARCH_MBED)

/*
 * RP2040 Zero
 *
 * GPIO numbering, not physical connector numbering.
 *
 * RA:
 *   GPIO2 STEP
 *   GPIO3 DIR
 *
 * DEC:
 *   GPIO4 STEP
 *   GPIO5 DIR
 *
 * Driver enable:
 *   GPIO6
 *
 * Home:
 *   GPIO7 RA
 *   GPIO8 DEC
 *
 * Limit:
 *   GPIO9
 *
 * LED:
 *   GPIO16
 */

#define AUX3_PIN 7
#define AUX4_PIN 8

#define LIMIT_SENSE_PIN 9

#ifndef MATRIX_STATUS_LED
    #define MATRIX_STATUS_LED ON
    #define NUM_LEDS 1
#endif

#define STATUS_LED_PIN 16
#define MOUNT_LED_PIN STATUS_LED_PIN
#define RETICLE_LED_PIN STATUS_LED_PIN

#define STATUS_BUZZER_PIN OFF

#define PPS_SENSE_PIN OFF
#define PEC_SENSE_PIN OFF

// -----------------------------------------------------------------------------
// Shared stepper-driver enable
// -----------------------------------------------------------------------------

#define SHARED_ENABLE_PIN 6

// -----------------------------------------------------------------------------
// Axis 1 - RA/AZM
// -----------------------------------------------------------------------------

#define AXIS1_ENABLE_PIN SHARED

#define AXIS1_M0_PIN OFF
#define AXIS1_M1_PIN OFF
#define AXIS1_M2_PIN OFF
#define AXIS1_M3_PIN OFF

#define AXIS1_STEP_PIN 2
#define AXIS1_DIR_PIN 3

#define AXIS1_SENSE_HOME_PIN AUX3_PIN

#define AXIS1_SERVO_PH1_PIN OFF
#define AXIS1_SERVO_PH2_PIN OFF

#define AXIS1_ENCODER_A_PIN OFF
#define AXIS1_ENCODER_B_PIN OFF

// -----------------------------------------------------------------------------
// Axis 2 - DEC/ALT
// -----------------------------------------------------------------------------

#define AXIS2_ENABLE_PIN SHARED

#define AXIS2_M0_PIN OFF
#define AXIS2_M1_PIN OFF
#define AXIS2_M2_PIN OFF
#define AXIS2_M3_PIN OFF

#define AXIS2_STEP_PIN 4
#define AXIS2_DIR_PIN 5

#define AXIS2_SENSE_HOME_PIN AUX4_PIN

#define AXIS2_SERVO_PH1_PIN OFF
#define AXIS2_SERVO_PH2_PIN OFF

#define AXIS2_ENCODER_A_PIN OFF
#define AXIS2_ENCODER_B_PIN OFF

// -----------------------------------------------------------------------------
// Axis 3-9 disabled
// -----------------------------------------------------------------------------

#define AXIS3_ENABLE_PIN OFF
#define AXIS3_STEP_PIN OFF
#define AXIS3_DIR_PIN OFF

#define AXIS4_ENABLE_PIN OFF
#define AXIS4_STEP_PIN OFF
#define AXIS4_DIR_PIN OFF

#define AXIS5_ENABLE_PIN OFF
#define AXIS5_STEP_PIN OFF
#define AXIS5_DIR_PIN OFF

#define AXIS6_ENABLE_PIN OFF
#define AXIS6_STEP_PIN OFF
#define AXIS6_DIR_PIN OFF

#define AXIS7_ENABLE_PIN OFF
#define AXIS7_STEP_PIN OFF
#define AXIS7_DIR_PIN OFF

#define AXIS8_ENABLE_PIN OFF
#define AXIS8_STEP_PIN OFF
#define AXIS8_DIR_PIN OFF

#define AXIS9_ENABLE_PIN OFF
#define AXIS9_STEP_PIN OFF
#define AXIS9_DIR_PIN OFF

// -----------------------------------------------------------------------------
// ST4 disabled
// -----------------------------------------------------------------------------

#define ST4_RA_W_PIN OFF
#define ST4_DEC_S_PIN OFF
#define ST4_DEC_N_PIN OFF
#define ST4_RA_E_PIN OFF

#else

#error "Wrong processor for RP2040_ZERO configuration!"

#endif

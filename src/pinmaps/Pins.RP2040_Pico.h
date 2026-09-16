// -------------------------------------------------------------------------------------------------
// OnStep 4.24 RP2040 Raspberry Pi Pico pin map
//
// This is a generic Pico pin map, not a specific commercial motor-driver PCB.
//
// Recommended external hardware:
//
//   Axis 1: STEP / DIR / EN + M0/M1/M2
//   Axis 2: STEP / DIR / EN + M0/M1/M2
//
// I2C:
//
//   GPIO20 = SDA
//   GPIO21 = SCL
//
// ST4:
//
//   GPIO16 = RA-
//   GPIO17 = DEC-
//   GPIO18 = DEC+
//   GPIO19 = RA+
//
// All GPIOs are 3.3 V logic.
// -------------------------------------------------------------------------------------------------

#if defined(ARDUINO_ARCH_RP2040)

// General purpose pins

#define Aux0                 25      // Pico onboard LED
#define Aux1                 22      // PPS
#define Aux2                 26      // Limit
#define Aux3                 27      // Axis 1 home
#define Aux4                 28      // Axis 2 home

#define OneWirePin           28

// PEC index

#define PecPin               26
#define AnalogPecPin         26

// Limit input

#define LimitPin             26

// Status LEDs

#define LEDnegPin            Aux0
#define LEDneg2Pin           Aux0
#define ReticlePin           Aux0

// Buzzer

#define TonePin              22

// PPS

#define PpsPin               22

// -----------------------------------------------------------------------------------------------
// Axis 1 RA / Azimuth
// -----------------------------------------------------------------------------------------------

#define Axis1_EN              2

#define Axis1_M0              3
#define Axis1_M1              4
#define Axis1_M2              5
#define Axis1_M3              8

#define Axis1_STEP            6
#define Axis1_DIR             7

#define Axis1_DECAY           Axis1_M2
#define Axis1_FAULT           Axis1_M3
#define Axis1_HOME            Aux3

// -----------------------------------------------------------------------------------------------
// Axis 2 DEC / Altitude
// -----------------------------------------------------------------------------------------------

#define Axis2_EN              9

#define Axis2_M0             10
#define Axis2_M1             11
#define Axis2_M2             12
#define Axis2_M3             15

#define Axis2_STEP           13
#define Axis2_DIR            14

#define Axis2_DECAY           Axis2_M2
#define Axis2_FAULT           Axis2_M3
#define Axis2_HOME            Aux4

// -----------------------------------------------------------------------------------------------
// Axis 3 rotator
// -----------------------------------------------------------------------------------------------

#define Axis3_EN             OFF
#define Axis3_STEP           OFF
#define Axis3_DIR            OFF

// -----------------------------------------------------------------------------------------------
// Axis 4 focuser
// -----------------------------------------------------------------------------------------------

#define Axis4_EN             OFF
#define Axis4_STEP           OFF
#define Axis4_DIR            OFF

// -----------------------------------------------------------------------------------------------
// Axis 5 focuser
// -----------------------------------------------------------------------------------------------

#define Axis5_EN             OFF
#define Axis5_STEP           OFF
#define Axis5_DIR            OFF

// -----------------------------------------------------------------------------------------------
// ST4
// -----------------------------------------------------------------------------------------------

#define ST4RAw               16
#define ST4DEs               17
#define ST4DEn               18
#define ST4RAe               19

// -----------------------------------------------------------------------------------------------
// I2C
// -----------------------------------------------------------------------------------------------
//
// Arduino Mbed RP2040 supports the Pico I2C pins below.

#ifndef I2C_SDA
  #define I2C_SDA           20
#endif

#ifndef I2C_SCL
  #define I2C_SCL           21
#endif

#else

#error "Wrong processor for RP2040 Pico configuration!"

#endif

#pragma once

#include "NvDeviceBase.h"
#include <EEPROM.h>
#include <Arduino.h>

#if !defined(NV_DRIVER) || (NV_DRIVER != NV_EEPROM)
  #error "EepromArduino.h included but NV_DRIVER != NV_EEPROM"
#endif

#ifndef NV_EEPROM_SIZE
  #error "NV_EEPROM_SIZE must be defined for RP2040 EEPROM"
#endif

class NvDeviceEepromArduino : public NvDevice {
public:
  bool init() override {
    Serial.println("### EEPROM: init ENTER ###");
    #if defined(ARDUINO_ARCH_RP2040)
        Serial.println("### EEPROM: RP2040 detected ###");
        Serial.print("### EEPROM: requested size = ");
        Serial.println((unsigned long)NV_EEPROM_SIZE);
        /*
        * Arduino-Pico EEPROM implementation.
        *
        * EEPROM.begin(size) returns void on RP2040.
        * Do NOT test it as:
        *
        *   if (!EEPROM.begin(size))
        *
        * because that is invalid for Arduino-Pico.
        */
        EEPROM.begin(NV_EEPROM_SIZE);
        Serial.println("### EEPROM: EEPROM.begin() returned ###");
        /*
        * Verify that the EEPROM object can actually be read.
        *
        * We don't modify anything here.
        */
        const uint8_t test = EEPROM.read(0);
        Serial.print("### EEPROM: read(0) = 0x");
        Serial.println(test, HEX);
        initialized_ = true;
        Serial.println("### EEPROM: init SUCCESS ###");
        return true;
    #else
      // Nothing to init for classic EEPROM
      VLF("MSG: NvDevice, using built-in EEPROM via Arduino library");
      initialized_ = true;
      return true;
    
    #endif
  }


  uint32_t sizeBytes() const override {
    return NV_EEPROM_SIZE & ~15u;
  }


  Endurance endurance() const override {
    return Endurance::Mid;
  }


  IoStatus read(uint16_t addr, void* dst, uint16_t len) override {
    if (!initialized_)      return IoStatus::NotReady;
    if (!dst)      return IoStatus::OutOfRange;
    if ((uint32_t)addr + (uint32_t)len > sizeBytes())      return IoStatus::OutOfRange;

    uint8_t* p = (uint8_t*)dst;

    for (uint16_t i = 0; i < len; i++) {
      p[i] = EEPROM.read((int)(addr + i));
    }
    return IoStatus::Ok;
  }


  IoStatus write(uint16_t addr, const void* src, uint16_t len) override {
    if (!initialized_)      return IoStatus::NotReady;
    if (!src)      return IoStatus::OutOfRange;
    if ((uint32_t)addr + (uint32_t)len > sizeBytes())      return IoStatus::OutOfRange;
    if (!isWritable())      return IoStatus::ReadOnly;

    const uint8_t* p =      static_cast<const uint8_t*>(src);

    for (uint16_t i = 0; i < len; i++) {
          const int a = (int)(addr + i);
          const uint8_t v = p[i];

          // AVR internal EEPROM: update() is supported and avoids needless wear.
          #if defined(ARDUINO_ARCH_AVR)
            EEPROM.update(a, v);
          #elif defined(ARDUINO_ARCH_RP2040)
            EEPROM.write((int)(addr + i), p[i]);
          #elif defined(HAL_EEPROM_HAS_UPDATE)
            EEPROM.update(a, v);
          #else
            EEPROM.write(a, v);
          #endif
    }
    return IoStatus::Ok;
  }

      bool hasCommit() const override {    return false;  }
      IoStatus commit() override {    return IoStatus::Ok;  }
      bool commitDone() const override {    return true;  }
      bool isReadable() const override {    return initialized_;  }
      bool isWritable() const override {    return initialized_;  }

    private:

      bool initialized_ = false;
    };

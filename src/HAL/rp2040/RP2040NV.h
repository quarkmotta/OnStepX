#if defined(ARDUINO_ARCH_RP2040) && !defined(ARDUINO_ARCH_MBED)

#include <EEPROM.h>

class RP2040NV {
public:
    static constexpr size_t SIZE = 4096;

    void begin() {
        EEPROM.begin(SIZE);
    }

    uint8_t read(size_t address) {
        if (address >= SIZE)
            return 0xFF;

        return EEPROM.read(address);
    }

    void write(size_t address, uint8_t value) {
        if (address >= SIZE)
            return;

        EEPROM.write(address, value);
    }

    void commit() {
        EEPROM.commit();
    }
};

#endif

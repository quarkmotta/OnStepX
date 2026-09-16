#pragma once

#include <Arduino.h>

namespace OnStepRP2040 {

class StepTimer {
public:

    using Callback = void (*)();

    StepTimer() = default;

    bool begin(Callback callback) {
        _callback = callback;
        return true;
    }

    void start(uint32_t periodUs) {
        _periodUs = periodUs;
        _running = true;
    }

    void stop() {
        _running = false;
    }

    bool running() const {
        return _running;
    }

    uint32_t period() const {
        return _periodUs;
    }

    void service() {
        if (!_running || _callback == nullptr)
            return;

        const uint32_t now = micros();

        if ((uint32_t)(now - _last) >= _periodUs) {
            _last = now;
            _callback();
        }
    }

private:

    Callback _callback = nullptr;
    uint32_t _last = 0;
    uint32_t _periodUs = 1000;
    volatile bool _running = false;
};

}

#include "timer.hpp"
#include <Arduino.h>

Timer::Timer() : next_timeout(0) {
}

void Timer::start(const unsigned long timeout) {
    next_timeout = millis() + timeout;
}

bool Timer::has_expired() const {
    return millis() >= next_timeout;
}

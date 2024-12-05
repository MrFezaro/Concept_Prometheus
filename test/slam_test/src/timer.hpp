//
// Created by oscwa on 11.10.2024.
//

#ifndef TIMER_HPP
#define TIMER_HPP

#include <Arduino.h>

class Timer {
public:
    Timer(): next_timeout(0) {
    };

    void start(const unsigned long time) {
        next_timeout = millis() + time;
    }

    [[nodiscard]] bool has_expired() const {
        return millis() >= next_timeout;
    }

private:
    unsigned long next_timeout;
};


#endif //TIMER_HPP

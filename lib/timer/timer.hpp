#ifndef TIMER_HPP
#define TIMER_HPP

class Timer {
public:
    Timer();

    void start(unsigned long timeout);

    bool has_expired() const;

private:
    unsigned long next_timeout;
};

#endif //TIMER_HPP

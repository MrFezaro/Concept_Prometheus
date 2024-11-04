#ifndef PID_HPP
#define PID_HPP

#include "ArduPID.h"

class PID {
public:
    // Constructor
    PID(double setPoint, double Kp, double Ki, double Kd);

    // Method to set up PID
    void setup();

    // Method to compute PID
    int compute(const int value);

private:
    ArduPID myController;
    double setPoint;
    double Kp;
    double Ki;
    double Kd;
    double input;
    double output;
};

#endif // PID_HPP
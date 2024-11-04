#include "pid.hpp"

// Constructor
PID::PID(double setPoint, double Kp, double Ki, double Kd)
    : myController(), setPoint(setPoint), Kp(Kp), Ki(Ki), Kd(Kd), input(0), output(0) {
}

// Method to set up PID
void PID::setup() {
    myController.begin(&input, &output, &setPoint, Kp, Ki, Kd);
    myController.setOutputLimits(-255, 255);
    myController.setBias(0);
    myController.setWindUpLimits(-10, 10);
    myController.start();
}

// Method to compute PID
int PID::compute(const int value) {
    input = value;
    myController.compute();
    return output;
}
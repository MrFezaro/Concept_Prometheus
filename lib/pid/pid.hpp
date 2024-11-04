//
// Created by Fezaro on 16.09.2024.
//
#ifndef PID_HPP
#define PID_HPP

#include "ArduPID.h"

class PID {
public:
    // Constructor
    PID(double setPoint, double Kp, double Ki, double Kd)
        : myController(), setPoint(setPoint), Kp(Kp), Ki(Ki), Kd(Kd), input(0), output(0) {
    }

    // Method to set up PID
    void setup() {
        myController.begin(&input, &output, &setPoint, Kp, Ki, Kd);
        myController.setOutputLimits(-255, 255);
        myController.setBias(0);
        myController.setWindUpLimits(-10, 10);
        myController.start();
    }

    // Method to compute PID
    int compute(const int value) {
        input = value;
        myController.compute();
        return output;
    }


private:
    ArduPID myController;
    double setPoint;
    double Kp;
    double Ki;
    double Kd;
    double input;
    double output;
};


#endif //PID_HPP
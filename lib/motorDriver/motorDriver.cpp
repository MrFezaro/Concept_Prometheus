#include "MotorDriver.hpp"
#include <Arduino.h>

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

volatile unsigned long lastPulseTime1 = 0;
volatile unsigned long currentPulseTime1 = 0;
volatile unsigned long lastPulseTime2 = 0;
volatile unsigned long currentPulseTime2 = 0;

void encoder1ISR() {
    lastPulseTime1 = currentPulseTime1;
    currentPulseTime1 = micros();
}

void encoder2ISR() {
    lastPulseTime2 = currentPulseTime2;
    currentPulseTime2 = micros();
}

void motorSetup() {
    pinMode(AOUT1, INPUT);
    pinMode(AOUT2, INPUT);
    pinMode(BOUT1, INPUT);
    pinMode(BOUT2, INPUT);

    attachInterrupt(digitalPinToInterrupt(AOUT1), encoder1ISR, RISING);
    attachInterrupt(digitalPinToInterrupt(BOUT1), encoder2ISR, RISING);
}

void driveMotor1(const int speed, const int baseSpeed) {
    motor1.drive(constrain((baseSpeed + speed), 0, 255));
}

void driveMotor2(const int speed, const int baseSpeed) {
    motor2.drive(constrain((baseSpeed - speed), 0, 255));
}

int getMotor1Speed() {
    const unsigned long pulseDuration = currentPulseTime1 - lastPulseTime1;
    if (pulseDuration > 0) {
        return 1000000 / pulseDuration; // Speed in pulses per second
    }
    return 0;
}

int getMotor2Speed() {
    const unsigned long pulseDuration = currentPulseTime2 - lastPulseTime2;
    if (pulseDuration > 0) {
        return 1000000 / pulseDuration; // Speed in pulses per second
    }
    return 0;
}

void stopMotors() {
    motor1.brake();
    motor2.brake();
}
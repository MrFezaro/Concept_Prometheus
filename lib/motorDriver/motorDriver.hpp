#ifndef MOTORDRIVER_HPP
#define MOTORDRIVER_HPP

#include <SparkFun_TB6612.h>

#define AIN1 A0
#define AIN2 A1
#define BIN1 A2
#define BIN2 A3
#define PWMA 10
#define PWMB 11
#define STBY A4

constexpr int offsetA = 1;
constexpr int offsetB = 1;

extern Motor motor1;
extern Motor motor2;

void driveMotor1(int speed, int baseSpeed);

void driveMotor2(int speed, int baseSpeed);

void stopMotors();

#endif // MOTORDRIVER_HPP

#ifndef MOTORDRIVER_HPP
#define MOTORDRIVER_HPP

#include <SparkFun_TB6612.h>

#define AIN1 A0
#define AIN2 A1
#define BIN1 A2
#define BIN2 A3
#define PWMA 10
#define PWMB 11
#define STBY 0
#define AOUT1 12
#define AOUT2 13
#define BOUT1 A6
#define BOUT2 A7

constexpr int offsetA = 1;
constexpr int offsetB = 1;

extern Motor motor1;
extern Motor motor2;

void motorSetup();

void driveMotor1(int speed, int baseSpeed);

void driveMotor2(int speed, int baseSpeed);

int getMotor1Speed();

int getMotor2Speed();

void stopMotors();

#endif // MOTORDRIVER_HPP

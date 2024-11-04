//
// Created by Fezaro on 23.09.2024.
//

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

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

inline void driveMotor1(int speed, int baseSpeed) {
    motor1.drive(constrain((baseSpeed+speed), 0, 255));

}

inline void driveMotor2(int speed, int baseSpeed) {
    motor2.drive(constrain((baseSpeed-speed), 0, 255));
}



#endif //MOTORDRIVER_HPP
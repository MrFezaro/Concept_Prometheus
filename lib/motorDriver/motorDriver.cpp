#include "MotorDriver.hpp"

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void driveMotor1(int speed, int baseSpeed) {
    motor1.drive(constrain((baseSpeed + speed), 0, 255));
}

void driveMotor2(int speed, int baseSpeed) {
    motor2.drive(constrain((baseSpeed - speed), 0, 255));
}
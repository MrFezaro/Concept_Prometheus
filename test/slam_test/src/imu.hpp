//
// Created by oscwa on 15.10.2024.
//

#ifndef IMU_HPP
#define IMU_HPP

#include <Arduino.h>
#include <Wire.h>

// Variables for gyroscope rates (angular velocity)
float RateRoll, RatePitch, RateYaw;
float RateCalibrationRoll, RateCalibrationPitch, RateCalibrationYaw;
int RateCalibrationNumber;

// Variables for accelerometer data
float AccX, AccY, AccZ;
float AngleRoll, AnglePitch;

// Kalman filter variables for Roll, Pitch, and Yaw
float KalmanAngleRoll = 0, KalmanUncertaintyAngleRoll = 2 * 2;
float KalmanAnglePitch = 0, KalmanUncertaintyAnglePitch = 2 * 2;
float KalmanAngleYaw = 0, KalmanUncertaintyAngleYaw = 2 * 2; // Add Yaw variables
float Kalman1DOutput[] = {0, 0};

// Timer variable for loop control
inline uint32_t LoopTimer;

// Kalman filter function (1D)
inline void kalman_1d(float &KalmanState, float &KalmanUncertainty, float KalmanInput, float KalmanMeasurement) {
    KalmanState = KalmanState + 0.004 * KalmanInput; // Prediction
    KalmanUncertainty = KalmanUncertainty + 0.004 * 0.004 * 4 * 4; // Increase uncertainty

    // Kalman gain calculation
    float KalmanGain = KalmanUncertainty * 1 / (1 * KalmanUncertainty + 3 * 3);

    // Update with new measurement
    KalmanState = KalmanState + KalmanGain * (KalmanMeasurement - KalmanState);
    KalmanUncertainty = (1 - KalmanGain) * KalmanUncertainty;

    // Output the updated state and uncertainty
    Kalman1DOutput[0] = KalmanState;
    Kalman1DOutput[1] = KalmanUncertainty;
}

// Function to read gyroscope and accelerometer signals
inline void gyro_signals() {
    Wire.beginTransmission(0x68);
    Wire.write(0x3B); // Start reading from register 0x3B (accelerometer)
    Wire.endTransmission();
    Wire.requestFrom(0x68, 6);

    int16_t AccXLSB = Wire.read() << 8 | Wire.read();
    int16_t AccYLSB = Wire.read() << 8 | Wire.read();
    int16_t AccZLSB = Wire.read() << 8 | Wire.read();

    Wire.beginTransmission(0x68);
    Wire.write(0x43); // Start reading from register 0x43 (gyroscope)
    Wire.endTransmission();
    Wire.requestFrom(0x68, 6);

    int16_t GyroX = Wire.read() << 8 | Wire.read();
    int16_t GyroY = Wire.read() << 8 | Wire.read();
    int16_t GyroZ = Wire.read() << 8 | Wire.read();

    RateRoll = (float) GyroX / 65.5;
    RatePitch = (float) GyroY / 65.5;
    RateYaw = (float) GyroZ / 65.5; // Yaw angular velocity

    AccX = (float) AccXLSB / 4096;
    AccY = (float) AccYLSB / 4096;
    AccZ = (float) AccZLSB / 4096;

    // Calculate roll and pitch angles from accelerometer data
    AngleRoll = atan(AccY / sqrt(AccX * AccX + AccZ * AccZ)) * (180.0 / PI);
    AnglePitch = -atan(AccX / sqrt(AccY * AccY + AccZ * AccZ)) * (180.0 / PI);
}

inline void IMUsetup() {
    Serial.begin(57600);

    Wire.setClock(400000);
    Wire.begin();

    delay(250);

    Wire.beginTransmission(0x68);
    Wire.write(0x6B); // Wake up MPU6050
    Wire.write(0x00);
    Wire.endTransmission();

    // Calibrate the gyroscope
    for (RateCalibrationNumber = 0; RateCalibrationNumber < 2000; RateCalibrationNumber++) {
        gyro_signals();
        RateCalibrationRoll += RateRoll;
        RateCalibrationPitch += RatePitch;
        RateCalibrationYaw += RateYaw;
        delay(1);
    }

    RateCalibrationRoll /= 2000;
    RateCalibrationPitch /= 2000;
    RateCalibrationYaw /= 2000;

    LoopTimer = micros();
}

inline float getAngle() {
    gyro_signals();

    // Subtract calibration values from gyro data
    RateRoll -= RateCalibrationRoll;
    RatePitch -= RateCalibrationPitch;
    RateYaw -= RateCalibrationYaw;

    // Apply Kalman filter for Roll and Pitch
    kalman_1d(KalmanAngleRoll, KalmanUncertaintyAngleRoll, RateRoll, AngleRoll);
    KalmanAngleRoll = Kalman1DOutput[0];
    KalmanUncertaintyAngleRoll = Kalman1DOutput[1];

    kalman_1d(KalmanAnglePitch, KalmanUncertaintyAnglePitch, RatePitch, AnglePitch);
    KalmanAnglePitch = Kalman1DOutput[0];
    KalmanUncertaintyAnglePitch = Kalman1DOutput[1];

    // Yaw Kalman filter: Use RateYaw (from gyroscope) as input and no direct accelerometer correction
    kalman_1d(KalmanAngleYaw, KalmanUncertaintyAngleYaw, RateYaw, KalmanAngleYaw); // Use previous yaw as measurement
    KalmanAngleYaw = Kalman1DOutput[0];
    KalmanUncertaintyAngleYaw = Kalman1DOutput[1];


    // Wait until the loop time reaches 4000us (4ms)
    while (micros() - LoopTimer < 4000) {
    }
    LoopTimer = micros();

    return KalmanAngleYaw - 0.00825; // Return the yaw angle with a small offset
}


#endif //IMU_HPP

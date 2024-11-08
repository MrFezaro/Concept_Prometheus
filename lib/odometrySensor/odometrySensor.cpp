#include "odometrySensor.hpp"
#include <Arduino.h>

QwiicOTOS myOtos; // Create an Optical Tracking Odometry Sensor object

void odometrySensorSetup() {
    Serial.println("Qwiic OTOS Example 1 - Basic Readings");

    // Attempt to begin the sensor
    while (myOtos.begin() == false) {
        Serial.println("OTOS not connected, check your wiring and I2C address!");
        delay(1000);
    }

    Serial.println("OTOS connected!");

    Serial.println("Ensure the OTOS is flat and stationary, then enter any key to calibrate the IMU");

    // Clear the serial buffer
    while (Serial.available())
        Serial.read();
    // Wait for user input
    while (!Serial.available()) {
    }

    Serial.println("Calibrating IMU...");

    // Calibrate the IMU, which removes the accelerometer and gyroscope offsets
    myOtos.calibrateImu();

    // Reset the tracking algorithm - this resets the position to the origin,
    // but can also be used to recover from some rare tracking errors
    myOtos.resetTracking();
}

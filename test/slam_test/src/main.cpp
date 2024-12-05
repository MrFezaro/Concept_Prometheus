#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_light.h>
#include "timer.hpp"
#include "coordinates.hpp"

float angleDeg, angleRad, deltaX, deltaY, x, y = 0;

Timer myTimer;
MPU6050 mpu(Wire);

// Calibration constants
const float xScaleFactor = 0.004689;
const float yScaleFactor = 0.004585;
const float xToYCrossTalk = 0.00217;
const float yToXCrossTalk = 0.00459;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Wire.begin();
    mouseSetup();

    const byte status = mpu.begin();
    Serial.print(F("MPU6050 status: "));
    Serial.println(status);
    while(status != 0) { } // Stop everything if cannot connect to MPU6050

    Serial.println(F("Calculating offsets, do not move MPU6050"));
    delay(1000);
    mpu.calcOffsets(); // gyro and accelero
    Serial.println("Done!\n");
}

void loop() {
    mpu.update();

    if (mouse1.available()) {
        deltaX = static_cast<float>(mouse1.getMouseX());
        deltaY = static_cast<float>(mouse1.getMouseY());
        mouse1.mouseDataClear();
    } else {
        deltaX = 0;
        deltaY = 0;
    }

    // Scale the raw values
    deltaX *= xScaleFactor;
    deltaY *= yScaleFactor;

    // Remove cross-talk
    deltaY -= deltaX * xToYCrossTalk;
    deltaX -= deltaY * yToXCrossTalk;

    // Get the angle from the MPU6050
    angleDeg = mpu.getAngleZ();
    angleRad = (angleDeg * 3.14159) / 180.0;
    angleRad *= 1.0055865921787709497206703910615; // Correct for the MPU6050's slight error

    // Rotate the x and y values
    x += deltaX * cos(angleRad) + deltaY * sin(angleRad);
    y += -deltaX * sin(angleRad) + deltaY * cos(angleRad);

    // Print the values every 50ms
    if (myTimer.has_expired()) {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.print(angleDeg);
        Serial.print(",");
        Serial.print(x);
        Serial.print(",");
        Serial.println(y);
        myTimer.start(50);
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }
}

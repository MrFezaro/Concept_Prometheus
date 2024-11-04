#include <Arduino.h>
#include <Wire.h>
#include "timer.hpp"
#include "coordinates.hpp"
#include "odometrySensor.hpp"
#include "pid.hpp"
#include "lineSensor.hpp"
#include "motorDriver.hpp"

Timer addPointTimer; // Timer object to control the timing of adding points
PID PID_1(500, 0.5, 0, 4); // PID object for line following

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Wire.begin();
    odometrySensorSetup();
    PID_1.setup();
    lineSensorSetup();
}

void loop() {
    sfe_otos_pose2d_t myPosition;
    myOtos.getPosition(myPosition);
    // myPosition.h
    if (addPointTimer.has_expired()) {
        digitalWrite(LED_BUILTIN, HIGH);
        addPoint(myPosition.x, myPosition.y);
        addPointTimer.start(100);
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }
}
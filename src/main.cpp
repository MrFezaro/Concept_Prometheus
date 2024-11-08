#include <Arduino.h>
#include <Wire.h>

#include "coordinates.hpp"
#include "lineSensor.hpp"
#include "motorDriver.hpp"
#include "odometrySensor.hpp"
#include "pid.hpp"
#include "purePursuit.hpp"
#include "timer.hpp"

Timer addPointTimer; // Timer object to control the timing of adding points
PID PID_racing(500, 0.5, 0, 4); // PID object for fast line following
PID PID_mapping(500, 0.5, 0, 4); // PID object for slow line following
PID PID_map_racing(0, 0.5, 0, 4); // PID object for map following

enum State {
    IDLE = 0,
    FOLLOW_LINE = 1,
    MAPPING = 2,
    FOLLOW_MAP = 3,
    RESET_MAP = 4
};

int currentState = IDLE;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Wire.begin();
    odometrySensorSetup();
    PID_racing.setup();
    PID_mapping.setup();
    PID_map_racing.setup();
    lineSensorSetup();
}

void loop() {
    sfe_otos_pose2d_t myPosition;

    switch (currentState) {
        case IDLE: {
            stopMotors();
            break;
        }

        case FOLLOW_LINE: {
            const int sensorValueRace = getLineSensorValue();
            const int PID_race = PID_racing.compute(sensorValueRace);

            if (sensorValueRace > 0 && sensorValueRace < 1000) {
                driveMotor1(PID_race, 200);
                driveMotor2(PID_race, 200);
            } else if (sensorValueRace == 0) {
                motor1.drive(255);
                motor2.brake();
            } else if (sensorValueRace == 1000) {
                motor1.brake();
                motor2.drive(255);
            }
            break;
        }

        case MAPPING: {
            const int sensorValueMap = getLineSensorValue();
            const int PID_map = PID_mapping.compute(sensorValueMap);
            myOtos.getPosition(myPosition);

            if (addPointTimer.has_expired()) {
                digitalWrite(LED_BUILTIN, HIGH);
                addPoint(myPosition.x, myPosition.y);
                addPointTimer.start(100);
            } else {
                digitalWrite(LED_BUILTIN, LOW);
            }
            driveMotor1(PID_map, 100);
            driveMotor2(PID_map, 100);
            break;
        }

        case FOLLOW_MAP: {
            myOtos.getPosition(myPosition);

            float targetX, targetY, steeringAngle;

            steeringAngle = purePursuit({myPosition.x, myPosition.y}, 1.0, targetX, targetY, steeringAngle);
            PID_map_racing.setpoint(steeringAngle);

            const int PID_map_race = PID_mapping.compute(myPosition.h);

            driveMotor1(PID_map_race, 255);
            driveMotor2(PID_map_race, 255);
            break;
        }

        case RESET_MAP: {
            stopMotors();
            myOtos.resetTracking();
            resetPoints();
            break;
        }

        default: {
            stopMotors();
        }
    }
}

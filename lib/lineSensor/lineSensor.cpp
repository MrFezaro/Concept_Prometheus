#include "LineSensor.hpp"

QTRSensors qtr;

uint16_t sensorValues[SensorCount];

void lineSensorSetup() {
    qtr.setTypeRC();
    qtr.setSensorPins((const uint8_t[]){2, 3, 4, 5, 6, 7, 8, 9}, SensorCount);

    delay(500);

    for (uint16_t i = 0; i < 150; i++) {
        qtr.calibrate();
    }

    for (uint8_t i = 0; i < SensorCount; i++) {
        Serial.print(qtr.calibrationOn.minimum[i]);
        Serial.print(' ');
    }
    Serial.println();

    for (uint8_t i = 0; i < SensorCount; i++) {
        Serial.print(qtr.calibrationOn.maximum[i]);
        Serial.print(' ');
    }
    Serial.println();
    Serial.println();
    delay(1000);
}

int getLineSensorValue() {
    const uint16_t position = qtr.readLineBlack(sensorValues);

    int mappedValue = map(position, 0, 5000, 0, 1000);
    mappedValue = constrain(mappedValue, 0, 1000);

    Serial.print(mappedValue);

    return mappedValue;
}

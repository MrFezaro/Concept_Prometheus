//
// Created by Fezaro on 16.09.2024.
//
#ifndef LINESENSOR_HPP
#define LINESENSOR_HPP

#include <Arduino.h>
#include <QTRSensors.h>

float alpha = 0.8; // Smoothing factor (0 < alpha <= 1)
float filteredValue = 0;

QTRSensors qtr;

const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];

inline void lineSensorSetup() {
    qtr.setTypeRC();
    qtr.setSensorPins((const uint8_t[]){3, 4, 5, 6, 7, 8}, SensorCount);

    delay(500);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode

    // 2.5 ms RC read timeout (default) * 10 reads per calibrate() call
    // = ~25 ms per calibrate() call.
    // Call calibrate() 400 times to make calibration take about 10 seconds.
    for (uint16_t i = 0; i < 150; i++) {
        qtr.calibrate();
    }
    digitalWrite(LED_BUILTIN, LOW); // turn off Arduino's LED to indicate we are through with calibration

    // print the calibration minimum values measured when emitters were on
    Serial.begin(9600);
    for (uint8_t i = 0; i < SensorCount; i++) {
        Serial.print(qtr.calibrationOn.minimum[i]);
        Serial.print(' ');
    }
    Serial.println();

    // print the calibration maximum values measured when emitters were on
    for (uint8_t i = 0; i < SensorCount; i++) {
        Serial.print(qtr.calibrationOn.maximum[i]);
        Serial.print(' ');
    }
    Serial.println();
    Serial.println();
    delay(1000);
}

inline int getLineSensorValue() {
    uint16_t position = qtr.readLineBlack(sensorValues);
    //
    // // Apply EMA filter
    // filteredValue = alpha * position + (1 - alpha) * filteredValue;
    //
    int mappedValue = map(position, 0, 5000, 0, 1000);
    mappedValue = constrain(mappedValue, 0, 1000);
    //
    // Serial.print(position);
    // Serial.print(' ');
    // Serial.print(filteredValue);
    // Serial.print(' ');
    Serial.print(mappedValue);

    return mappedValue;
}



#endif //LINESENSOR_HPP
#ifndef LINESENSOR_HPP
#define LINESENSOR_HPP

#include <Arduino.h>
#include <QTRSensors.h>

extern QTRSensors qtr;

constexpr uint8_t SensorCount = 8;
extern uint16_t sensorValues[SensorCount];

void lineSensorSetup();

int getLineSensorValue();

#endif // LINESENSOR_HPP

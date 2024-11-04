#include "coordinates.hpp"
#include <Arduino.h>

// Arrays to store x and y coordinates
float x_[MAX_POINTS];
float y_[MAX_POINTS];

// Variable to track the number of points added
int pointCount = 0;

void addPoint(const float x, const float y) {
    if (pointCount < MAX_POINTS) {
        x_[pointCount] = x;
        y_[pointCount] = y;
        pointCount++;
    } else {
        Serial.println("Max points reached, cannot add more points.");
    }
}
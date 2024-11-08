#include "coordinates.hpp"
#include <Arduino.h>

// Array to store points
Point points[MAX_POINTS];

// Variable to track the number of points added
int pointCount = 0;

void addPoint(const float x, const float y) {
    if (pointCount < MAX_POINTS) {
        points[pointCount].x = x;
        points[pointCount].y = y;
        pointCount++;
    } else {
        Serial.println("Max points reached, cannot add more points.");
    }
}
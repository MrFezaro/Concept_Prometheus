#include "coordinates.hpp"

// Array to hold points
Point points[MAX_POINTS];

// Number of points in the array
int pointCount = 0;

void addPoint(const float x, const float y) {
    if (pointCount < MAX_POINTS) {
        points[pointCount].x = x;
        points[pointCount].y = y;
        pointCount++;
    }
}

void resetPoints() {
    for (int i = 0; i < pointCount; i++) {
        points[i].x = 0;
        points[i].y = 0;
    }
    pointCount = 0;
}

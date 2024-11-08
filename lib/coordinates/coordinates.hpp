#ifndef COORDINATES_HPP
#define COORDINATES_HPP

// Maximum number of points
#define MAX_POINTS 1000 //25000 Max

// Struct to hold x and y coordinates
struct Point {
    float x;
    float y;
};

// Array to hold points
extern Point points[MAX_POINTS];

// Number of points in the array
extern int pointCount;

// Function to add a point to the points array
void addPoint(float x, float y);

// Function to reset all points
void resetPoints();

#endif // COORDINATES_HPP

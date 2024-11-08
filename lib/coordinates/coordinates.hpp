#ifndef COORDINATES_HPP
#define COORDINATES_HPP

// Maximum number of points
#define MAX_POINTS 25000

// Struct to hold x and y coordinates
struct Point {
    float x;
    float y;
};

// Function to add a point to the points array
void addPoint(float x, float y);

#endif // COORDINATES_HPP
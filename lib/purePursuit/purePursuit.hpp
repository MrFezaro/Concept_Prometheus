#ifndef PUREPURSUIT_HPP
#define PUREPURSUIT_HPP

#include "coordinates.hpp"

// Function to calculate the target point and steering angle
float purePursuit(Point currentPos, float lookaheadDistance, float &targetX, float &targetY, float &steeringAngle);

#endif // PUREPURSUIT_HPP
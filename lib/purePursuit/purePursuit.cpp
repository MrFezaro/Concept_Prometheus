#include "purePursuit.hpp"
#include <cmath>
#include <limits>

float purePursuit(const Point currentPos, const float lookaheadDistance, float &targetX, float &targetY,
                  float &steeringAngle) {
    // Find the closest point on the path
    int closestPointIndex = 0;
    float minDistanceSquared = std::numeric_limits<float>::max();
    for (int i = 0; i < pointCount; i++) {
        const float dx = points[i].x - currentPos.x;
        const float dy = points[i].y - currentPos.y;
        const float distanceSquared = dx * dx + dy * dy;
        if (distanceSquared < minDistanceSquared) {
            minDistanceSquared = distanceSquared;
            closestPointIndex = i;
        }
    }

    // Find the lookahead point
    int lookaheadPointIndex = closestPointIndex;
    for (int i = closestPointIndex; i < pointCount; i++) {
        const float dx = points[i].x - currentPos.x;
        const float dy = points[i].y - currentPos.y;
        const float distanceSquared = dx * dx + dy * dy;
        if (distanceSquared >= lookaheadDistance * lookaheadDistance) {
            lookaheadPointIndex = i;
            break;
        }
    }

    // Set the target point
    targetX = points[lookaheadPointIndex].x;
    targetY = points[lookaheadPointIndex].y;

    // Calculate the steering angle
    const float dx = targetX - currentPos.x;
    const float dy = targetY - currentPos.y;

    return steeringAngle = std::atan2(dy, dx);
}

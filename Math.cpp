#pragma once
#include <math.h>

namespace math
{
    double distanceToMeters(float distance)
    {
        const float INCHES_TO_METER_RATE = 39.3701;
        return distance / INCHES_TO_METER_RATE;
    }
    double calculateDistance(float x1, float y1, float z1, float x2, float y2, float z2)
    {
        float dx = (x1 - x2);
        float dy = (y1 - y2);
        float dz = (z1 - z2);
        float distance = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
        return distance;
    }

    double calculateDistanceInMeters(float x1, float y1, float z1, float x2, float y2, float z2)
    {
        return distanceToMeters(calculateDistance(x1, y1, z1, x2, y2, z2));
    }

    double calculateDistance2D(float x1, float y1, float x2, float y2)
    {
        float dx = (x1 - x2);
        float dy = (y1 - y2);
        float distance = sqrt(pow(dx, 2) + pow(dy, 2));
        return distance;
    }

}
#pragma once
#include <vector>
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Math.cpp"

class Aimbot
{
private:
    int m_smoothing = 1000; // min
    int m_fovActivationAngle = 600;

public:
    void update(LocalPlayer *localPlayer, std::vector<Player *> *players)
    {
        if (localPlayer->getZooming() != 1)
            return;

        // LPlayerX: 31495.320312 LPlayerY: -6708.900879 LPlayerZ: -29235.982422
        const float dummLocationX = 31520.320312;
        const float dummLocationY = -6708.900879;
        const float dummLocationZ = -29235.982422;

        // printf("LPlayerX: %.6f LPlayerY: %.6f LPlayerZ: %.6f \n", localPlayer->getLocationX(), localPlayer->getLocationY(), localPlayer->getLocationZ());

        float desiredViewAngleYaw = calculateVieAngleYaw(localPlayer->getLocationX(),
                                                         localPlayer->getLocationY(),
                                                         dummLocationX,
                                                         dummLocationY);

        const float localPlayerViewAngleYaw = localPlayer->getViewAngleYaw();
        const float angleIncrement = calculateAngleDelta(localPlayerViewAngleYaw, desiredViewAngleYaw);
        if (abs(angleIncrement) < m_fovActivationAngle)
        {
            float newViewAngleYaw = flipYawIfNeeded(localPlayerViewAngleYaw + (angleIncrement / m_smoothing));
            localPlayer->setViewAngleY(newViewAngleYaw);
        }
    }
    float flipYawIfNeeded(float angle)
    {
        float myAngle = angle;
        if (myAngle > 180)
            myAngle = (360 - myAngle) * -1;
        else if (myAngle < -180)
            myAngle = (360 + myAngle);
        return myAngle;
    }
    float calculateAngleDelta(float oldAngle, float newAngle)
    {
        float wayA = newAngle - oldAngle;
        float wayB = 360 - abs(wayA);
        if (wayA > 0 && wayB > 0)
            wayB *= -1;
        if (abs(wayA) < abs(wayB))
            return wayA;
        return wayB;
    }
    float calculateVieAngleYaw(float localPlayerLocationX, float localPlayerLocationY, float enemyPlayerLocationX, float enemyPlayerLocationY)
    {
        const float locationDeltaX = enemyPlayerLocationX - localPlayerLocationX;
        const float locationDeltaY = enemyPlayerLocationY - localPlayerLocationY;
        const float yawInRadians = atan2(locationDeltaY, locationDeltaX);
        const float yawInDegrees = yawInRadians * (180 / M_PI);
        return yawInDegrees;
    }
};
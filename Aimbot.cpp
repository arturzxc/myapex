#pragma once
#include <vector>
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Math.cpp"

class Aimbot
{
private:
    int m_smoothing = 500; // min
    int m_fovActivationAngle = 600;

public:
    void update(LocalPlayer *localPlayer, std::vector<Player *> *players)
    {
        if (localPlayer->getZooming() != 1)
            return;
        Player *closestEnemy = findClosestEnemy(localPlayer, players);
        if (closestEnemy == nullptr)
            return;
        float desiredViewAngleYaw = calculateDesiredYaw(localPlayer->getLocationX(),
                                                        localPlayer->getLocationY(),
                                                        closestEnemy->getLocationX(),
                                                        closestEnemy->getLocationY());
        const float localPlayerViewAngleYaw = localPlayer->getViewAngleYaw();
        const float angleDelta = calculateAngleDelta(localPlayerViewAngleYaw, desiredViewAngleYaw);
        if (abs(angleDelta) < m_fovActivationAngle)
        {
            float newViewAngleYaw = flipYawIfNeeded(localPlayerViewAngleYaw + (angleDelta / m_smoothing));
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
    float calculateDesiredYaw(float localPlayerLocationX, float localPlayerLocationY, float enemyPlayerLocationX, float enemyPlayerLocationY)
    {
        const float locationDeltaX = enemyPlayerLocationX - localPlayerLocationX;
        const float locationDeltaY = enemyPlayerLocationY - localPlayerLocationY;
        const float yawInRadians = atan2(locationDeltaY, locationDeltaX);
        const float yawInDegrees = yawInRadians * (180 / M_PI);
        return yawInDegrees;
    }
    Player *findClosestEnemy(LocalPlayer *localPlayer, std::vector<Player *> *players)
    {
        Player *closestPlayerSoFar = nullptr;
        float closestPlayerAngleSoFar;
        for (int i = 0; i < players->size(); i++)
        {
            Player *player = players->at(i);
            if (!player->isValid())
                continue;
            if (player->getTeamNumber() == localPlayer->getTeamNumber())
                continue;
            float desiredViewAngleYaw = calculateDesiredYaw(localPlayer->getLocationX(),
                                                            localPlayer->getLocationY(),
                                                            player->getLocationX(),
                                                            player->getLocationY());
            float angleDelta = calculateAngleDelta(localPlayer->getViewAngleYaw(), desiredViewAngleYaw);
            if (closestPlayerSoFar == nullptr)
            {
                closestPlayerSoFar = player;
                closestPlayerAngleSoFar = abs(angleDelta);
            }
            else
            {

                if (abs(angleDelta) < closestPlayerAngleSoFar)
                {
                    closestPlayerSoFar = player;
                    closestPlayerAngleSoFar = abs(angleDelta);
                }
            }
        }
        return closestPlayerSoFar;
    }
};
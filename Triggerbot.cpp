#pragma once
#include <vector>
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Math.cpp"
#include "Level.cpp"
#include "math.h"
#include "X11Utils.cpp"

class Triggerbot
{
private:
    const float m_triggerAngle = 0.5f;

public:
    void update(Level *level, LocalPlayer *localPlayer, std::vector<Player *> *players, X11Utils *x11Utils)
    {
        if (!x11Utils->triggerKeyDown())
            return;
        if (!level->isPlayable())
            return;
        double desiredViewAngleYaw;
        if (level->isTrainingArea())
        {
            desiredViewAngleYaw = calculateDesiredYaw(localPlayer->getLocationX(),
                                                      localPlayer->getLocationY(),
                                                      31518,
                                                      -6712);
        }
        else
        {
            Player *closestEnemy = findClosestEnemy(localPlayer, players);
            if (closestEnemy == nullptr)
                return;
            desiredViewAngleYaw = calculateDesiredYaw(localPlayer->getLocationX(),
                                                      localPlayer->getLocationY(),
                                                      closestEnemy->getLocationX(),
                                                      closestEnemy->getLocationY());
        }
        const double yaw = localPlayer->getYaw();
        const double angleDelta = calculateAngleDelta(yaw, desiredViewAngleYaw);
        const double angleDeltaAbs = abs(angleDelta);
        if (angleDeltaAbs < m_triggerAngle)
            x11Utils->mouseClick(1);
    }
    double flipYawIfNeeded(double angle)
    {
        double myAngle = angle;
        if (myAngle > 180)
            myAngle = (360 - myAngle) * -1;
        else if (myAngle < -180)
            myAngle = (360 + myAngle);
        return myAngle;
    }
    double calculateAngleDelta(double oldAngle, double newAngle)
    {
        double wayA = newAngle - oldAngle;
        double wayB = 360 - abs(wayA);
        if (wayA > 0 && wayB > 0)
            wayB *= -1;
        if (abs(wayA) < abs(wayB))
            return wayA;
        return wayB;
    }
    double calculateDesiredYaw(double localPlayerLocationX, double localPlayerLocationY, double enemyPlayerLocationX, double enemyPlayerLocationY)
    {
        const double locationDeltaX = enemyPlayerLocationX - localPlayerLocationX;
        const double locationDeltaY = enemyPlayerLocationY - localPlayerLocationY;
        const double yawInRadians = atan2(locationDeltaY, locationDeltaX);
        const double yawInDegrees = yawInRadians * (180 / M_PI);
        return yawInDegrees;
    }
    Player *findClosestEnemy(LocalPlayer *localPlayer, std::vector<Player *> *players)
    {
        Player *closestPlayerSoFar = nullptr;
        double closestPlayerAngleSoFar;
        for (int i = 0; i < players->size(); i++)
        {
            Player *player = players->at(i);
            if (!player->isValid())
                continue;
            if (player->getLifeState() > 0)
                continue;
            if (player->getTeamNumber() == localPlayer->getTeamNumber())
                continue;
            const bool isVisible = player->isVisible();
            if (!isVisible)
                continue;
            double desiredViewAngleYaw = calculateDesiredYaw(localPlayer->getLocationX(),
                                                             localPlayer->getLocationY(),
                                                             player->getLocationX(),
                                                             player->getLocationY());
            double angleDelta = calculateAngleDelta(localPlayer->getYaw(), desiredViewAngleYaw);
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
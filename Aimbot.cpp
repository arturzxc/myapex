#pragma once
#include <vector>
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Math.cpp"
#include "Level.cpp"
#include "math.h"
#include "X11Utils.cpp"
#include "ConfigLoader.cpp"

class Aimbot
{
private:
    ConfigLoader *m_configLoader;
    Level *m_level;
    LocalPlayer *m_localPlayer;
    std::vector<Player *> *m_players;
    X11Utils *m_x11Utils;

    Player *m_lockedOnPlayer = nullptr;

public:
    Aimbot(ConfigLoader *configLoader,
           Level *level,
           LocalPlayer *localPlayer,
           std::vector<Player *> *players,
           X11Utils *x11Utils)
    {
        m_configLoader = configLoader;
        m_level = level;
        m_localPlayer = localPlayer;
        m_players = players;
        m_x11Utils = x11Utils;
    }
    void update()
    {
        // validations
        if (m_configLoader->getAimbotTrigger() != 0x0000)
        { // our trigger is a button
            if (!m_x11Utils->keyDown(m_configLoader->getAimbotTrigger()))
            {
                m_lockedOnPlayer = nullptr;
                return;
            }
        }
        if (!m_level->isPlayable())
        {
            m_lockedOnPlayer = nullptr;
            return;
        }
        if (m_localPlayer->isDead())
        {
            m_lockedOnPlayer = nullptr;
            return;
        }
        if (m_localPlayer->isKnocked())
        {
            m_lockedOnPlayer = nullptr;
            return;
        }
        if (m_configLoader->getAimbotTrigger() == 0x0000) // our trigger is localplayer attacking
            if (!m_localPlayer->isInAttack())
            {
                m_lockedOnPlayer = nullptr;
                return;
            }

        // get desired angle to an enemy
        double desiredViewAngleYaw = 0;
        double desiredViewAnglePitch = 0;
        if (m_level->isTrainingArea())
        {
            printf("X:%.6f \t Y: %.6f \t Z:%.6f \n", m_localPlayer->getLocationX(), m_localPlayer->getLocationY(), m_localPlayer->getLocationZ());
            const float dummyX = 31408.732422;
            const float dummyY = -6711.955566;
            const float dummyZ = -29234.839844;
            double distanceToTarget = math::calculateDistanceInMeters(m_localPlayer->getLocationX(), m_localPlayer->getLocationY(), m_localPlayer->getLocationZ(), dummyX, dummyY, dummyZ);
            if (distanceToTarget > m_configLoader->getAimbotMaxRange())
                return;
            desiredViewAngleYaw = calculateDesiredYaw(m_localPlayer->getLocationX(), m_localPlayer->getLocationY(), dummyX, dummyY);
            desiredViewAnglePitch = calculateDesiredPitch(m_localPlayer->getLocationX(), m_localPlayer->getLocationY(), m_localPlayer->getLocationZ(), dummyX, dummyY, dummyZ);
        }
        else
        {
            if (m_lockedOnPlayer == nullptr || !m_lockedOnPlayer->isVisible())
                m_lockedOnPlayer = findClosestEnemy();
            if (m_lockedOnPlayer == nullptr)
                return;
            double distanceToTarget = math::calculateDistanceInMeters(m_localPlayer->getLocationX(),
                                                                      m_localPlayer->getLocationY(),
                                                                      m_localPlayer->getLocationZ(),
                                                                      m_lockedOnPlayer->getLocationX(),
                                                                      m_lockedOnPlayer->getLocationY(),
                                                                      m_lockedOnPlayer->getLocationZ());
            if (distanceToTarget > m_configLoader->getAimbotMaxRange())
                return;
            desiredViewAngleYaw = calculateDesiredYaw(m_localPlayer->getLocationX(),
                                                      m_localPlayer->getLocationY(),
                                                      m_lockedOnPlayer->getLocationX(),
                                                      m_lockedOnPlayer->getLocationY());
            desiredViewAnglePitch = calculateDesiredPitch(m_localPlayer->getLocationX(),
                                                          m_localPlayer->getLocationY(),
                                                          m_localPlayer->getLocationZ(),
                                                          m_lockedOnPlayer->getLocationX(),
                                                          m_lockedOnPlayer->getLocationY(),
                                                          m_lockedOnPlayer->getLocationZ());
        }

        // Setup Pitch
        const double pitch = m_localPlayer->getPitch();
        const double pitchAngleDelta = calculatePitchAngleDelta(pitch, desiredViewAnglePitch);
        const double pitchAngleDeltaAbs = abs(pitchAngleDelta);
        if (pitchAngleDeltaAbs > m_configLoader->getAimbotActivationFOV() / 2)
            return;

        // Setup Yaw
        const double yaw = m_localPlayer->getYaw();
        const double angleDelta = calculateAngleDelta(yaw, desiredViewAngleYaw);
        const double angleDeltaAbs = abs(angleDelta);
        if (angleDeltaAbs > m_configLoader->getAimbotActivationFOV())
            return;
        double newYaw = flipYawIfNeeded(yaw + (angleDelta / m_configLoader->getAimbotSmoothing()));
        m_localPlayer->setYaw(newYaw);
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
    double calculatePitchAngleDelta(double oldAngle, double newAngle)
    {
        double wayA = newAngle - oldAngle;
        return wayA;
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
    double calculateDesiredYaw(
        double localPlayerLocationX,
        double localPlayerLocationY,
        double enemyPlayerLocationX,
        double enemyPlayerLocationY)
    {
        const double locationDeltaX = enemyPlayerLocationX - localPlayerLocationX;
        const double locationDeltaY = enemyPlayerLocationY - localPlayerLocationY;
        const double yawInRadians = atan2(locationDeltaY, locationDeltaX);
        const double yawInDegrees = yawInRadians * (180 / M_PI);
        return yawInDegrees;
    }
    double calculateDesiredPitch(
        double localPlayerLocationX,
        double localPlayerLocationY,
        double localPlayerLocationZ,
        double enemyPlayerLocationX,
        double enemyPlayerLocationY,
        double enemyPlayerLocationZ)
    {
        const double locationDeltaZ = enemyPlayerLocationZ - localPlayerLocationZ;
        const double distanceBetweenPlayers = math::calculateDistance2D(enemyPlayerLocationX, enemyPlayerLocationY, localPlayerLocationX, localPlayerLocationY);
        const double pitchInRadians = atan2(-locationDeltaZ, distanceBetweenPlayers);
        const double pitchInDegrees = pitchInRadians * (180 / M_PI);
        return pitchInDegrees;
    }
    Player *findClosestEnemy()
    {
        Player *closestPlayerSoFar = nullptr;
        double closestPlayerAngleSoFar;
        for (int i = 0; i < m_players->size(); i++)
        {
            Player *player = m_players->at(i);
            if (!player->isValid())
                continue;
            if (player->isKnocked())
                continue;
            if (player->getTeamNumber() == m_localPlayer->getTeamNumber())
                continue;
            if (!player->isVisible())
                continue;
            double desiredViewAngleYaw = calculateDesiredYaw(m_localPlayer->getLocationX(),
                                                             m_localPlayer->getLocationY(),
                                                             player->getLocationX(),
                                                             player->getLocationY());
            double angleDelta = calculateAngleDelta(m_localPlayer->getYaw(), desiredViewAngleYaw);
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

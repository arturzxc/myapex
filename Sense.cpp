#pragma once
#include <vector>
#include "LocalPlayer.cpp"
#include "Player.cpp"

class Sense
{
private:
    const int m_maxRange = 500;
    const int m_maxRangeSquared = pow(m_maxRange, 2);
    const int m_longRangeStartDistance = 50;
    const int m_longRangeStartDistanceSquared = pow(m_longRangeStartDistance, 2);

public:
    void update(LocalPlayer *localPlayer, std::vector<Player *> *players)
    {
        printf("SENSE RUNNING\n");
        for (int i = 0; i < players->size(); i++)
        {
            Player *player = players->at(i);
            if (!player->isValid())
                continue;
            if (player->getTeamNumber() == localPlayer->getTeamNumber())
                continue;
            long distanceSquared = utils::calcDistanceSquared(localPlayer->getLocationOriginX(),
                                                              localPlayer->getLocationOriginY(),
                                                              localPlayer->getLocationOriginZ(),
                                                              player->getLocationOriginX(),
                                                              player->getLocationOriginY(),
                                                              player->getLocationOriginZ());
            const int currentGlowEnable = player->getGlowEnable();
            const int currenctGlowThroughWall = player->getGlowThroughWall();
            if (distanceSquared > m_maxRangeSquared)
            { // reset
                if (currentGlowEnable == 5 || currentGlowEnable == 7)
                    player->setGlowEnable(2);
                if (currenctGlowThroughWall == 2)
                    player->setGlowThroughWall(5);
            }
            else
            {
                if (distanceSquared >= m_longRangeStartDistanceSquared && localPlayer->getZooming() == 1)
                { // Caustic scan
                    if (currentGlowEnable != 5)
                        player->setGlowEnable(5);
                    if (currenctGlowThroughWall != 5)
                        player->setGlowThroughWall(5);
                }
                else
                { // Bloodhound scan
                    if (currentGlowEnable != 7)
                        player->setGlowEnable(7);
                    if (currenctGlowThroughWall != 2)
                        player->setGlowThroughWall(2);
                }
            }
        }
    }
};
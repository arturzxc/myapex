#pragma once
#include <vector>
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Math.cpp"
#include "Level.cpp"

class Sense
{
public:
    void update(Level *level, LocalPlayer *localPlayer, std::vector<Player *> *players)
    {
        if (!level->isPlayable())
            return;
        for (int i = 0; i < players->size(); i++)
        {
            Player *player = players->at(i);
            if (!player->isValid())
                continue;
            if (player->getTeamNumber() == localPlayer->getTeamNumber())
                continue;
            const float distance = math::calculateDistance(localPlayer->getLocationX(),
                                                           localPlayer->getLocationY(),
                                                           localPlayer->getLocationZ(),
                                                           player->getLocationX(),
                                                           player->getLocationY(),
                                                           player->getLocationZ());
            if (localPlayer->isZooming() && distance > 500)
            {
                player->setGlowEnable(5);
            }
            else
            {
                player->setGlowEnable(7);
                player->setGlowThroughWall(2);
            }
        }
    }
};
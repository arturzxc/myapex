#pragma once
#include <vector>
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Math.cpp"

class Sense
{
public:
    void update(LocalPlayer *localPlayer, std::vector<Player *> *players)
    {
        for (int i = 0; i < players->size(); i++)
        {
            Player *player = players->at(i);
            if (!player->isValid())
                continue;
            if (player->getTeamNumber() == localPlayer->getTeamNumber())
                continue;
            player->setGlowEnable(7);
            player->setGlowThroughWall(2);
        }
    }
};
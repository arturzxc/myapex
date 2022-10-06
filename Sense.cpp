#pragma once
#include <vector>
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Math.cpp"
#include "Level.cpp"
#include "X11Utils.cpp"

class Sense
{
public:
    void update(Level *level, LocalPlayer *localPlayer, std::vector<Player *> *players, X11Utils *x11Utils)
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
            if (player->isVisible())
            {
                player->setGlowEnable(5);
                player->setGlowThroughWall(1);
            }
            else
            {
                player->setGlowEnable(7);
                player->setGlowThroughWall(2);
            }
        }
    }
};
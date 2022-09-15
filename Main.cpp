#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <vector>
#include "Utils.cpp"
#include "Offsets.cpp"
#include "Level.cpp"
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Sense.cpp"
#include "NoRecoil.cpp"

int main()
{
    if (getuid())
    {
        printf("MUST RUN AS ROOT!\n");
        return -1;
    }
    if (mem::GetPID() == 0)
    {
        printf("GAME NOT FOUND. EXITING!\n");
        return -1;
    }

    Level *level = new Level();
    LocalPlayer *localPlayer = new LocalPlayer();
    std::vector<Player *> *players = new std::vector<Player *>;
    for (int i = 0; i < 60; i++)
    {
        players->push_back(new Player(i));
    }
    Sense *sense = new Sense();
    while (true)
    {
        try
        {
            if (level->isPlayable())
            {
                sense->update(localPlayer, players);
                printf("SENSE RUNNING\n");
            }
            else
            {
                printf("SENSE PAUSED\n");
            }
        }
        catch (...)
        {
            printf("SENSE ERROR\n");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

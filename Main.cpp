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
#include "Aimbot.cpp"

bool IS_SENSE_ON = true;
bool IS_NO_RECOIL_ON = true;
bool IS_AIMBOT_ON = true;

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
    NoRecoil *noRecoil = new NoRecoil();
    Aimbot *aimbot = new Aimbot();
    while (true)
    {
        try
        {
            if (level->isPlayable())
            {
                if (IS_SENSE_ON)
                    sense->update(localPlayer, players);
                if (IS_NO_RECOIL_ON)
                    noRecoil->update(localPlayer);
                if (IS_AIMBOT_ON)
                    aimbot->update(localPlayer, players);
            }
        }
        catch (...)
        {
            printf("UPDATE LOOP ERROR, RAND: %d\n", rand());
        }
        sleep(50 / 1000);
    }
}

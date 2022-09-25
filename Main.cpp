#include <iostream>
#include <string>
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
    printf("MYAPEX RUNNING\n");
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
    while (1)
    {
        try
        {
            sense->update(level, localPlayer, players);
            noRecoil->update(level, localPlayer);
            aimbot->update(level, localPlayer, players);
            printf("LOOP OK: %d\n", rand());
        }
        catch (...)
        {
            printf("LOOP ERROR, RAND: %d\n", rand());
        }
        sleep(10 / 1000);
    }
}

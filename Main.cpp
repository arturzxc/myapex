#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <chrono>
#include <thread>
#include "Utils.cpp"
#include "Offsets.cpp"
#include "Level.cpp"
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Sense.cpp"
#include "NoRecoil.cpp"
#include "Aimbot.cpp"
#include "X11Utils.cpp"
#include "ConfigLoader.cpp"

int main(int argc, char *argv[])
{
    ConfigLoader *configLoader = new ConfigLoader();
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
    X11Utils *x11Utils = new X11Utils();
    std::vector<Player *> *players = new std::vector<Player *>;
    for (int i = 0; i < 60; i++)
    {
        players->push_back(new Player(i));
    }
    Sense *sense = new Sense();
    NoRecoil *noRecoil = new NoRecoil();
    Aimbot *aimbot = new Aimbot();

    // Main loop
    printf("MYAPEX STARTING MAIN LOOP\n");
    int counter = 0;
    while (1)
    {
        try
        {
            // resolve pointers only once per loop for all players
            localPlayer->markForPointerResolution();
            for (int i = 0; i < players->size(); i++)
            {
                Player *player = players->at(i);
                player->markForPointerResolution();
            }

            // run features
            if (configLoader->isNorecoilOn())
                noRecoil->update(level, localPlayer, x11Utils);
            if (configLoader->isAimbotOn())
                aimbot->update(level, localPlayer, players, x11Utils);
            if (configLoader->isSenseOn())
                sense->update(level, localPlayer, players, x11Utils);
            printf("UPDATE[%d]\tOK. \n", counter);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        catch (...)
        {
            printf("UPDATE[%d] ERROR (LOADING SCREEN?). SLEEPING FOR 10 SECONDS\n", counter); // this happens on loading screen
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
        counter++;
        if (counter > 1000)
            counter = 0;
    }
}

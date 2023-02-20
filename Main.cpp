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
    // Make sure we are root and the game us running
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

    // create objects
    ConfigLoader *configLoader = new ConfigLoader();
    Level *level = new Level();
    LocalPlayer *localPlayer = new LocalPlayer();
    X11Utils *x11Utils = new X11Utils();
    std::vector<Player *> *players = new std::vector<Player *>;
    for (int i = 0; i < 60; i++)
    {
        players->push_back(new Player(i));
    }
    Sense *sense = new Sense(configLoader, level, localPlayer, players, x11Utils);
    NoRecoil *noRecoil = new NoRecoil(configLoader, level, localPlayer, players, x11Utils);
    Aimbot *aimbot = new Aimbot(configLoader, level, localPlayer, players, x11Utils);

    // start the main loop
    printf("MYAPEX STARTING MAIN LOOP\n");
    int counter = 0;
    while (1)
    {
        try
        {
            // reload config if required
            if (counter % 200 == 0)
                configLoader->reloadFile();

            // run features
            if (configLoader->isNorecoilOn())
            {
                noRecoil->update();
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }

            if (configLoader->isAimbotOn())
                aimbot->update();

            if (configLoader->isSenseOn())
                sense->update();

            // all ran fine
            if (counter == 0)
            {
                printf("RUNNING OK. Time: %s\n", utils::current_time().c_str());
            }

            // sleep a bit
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        catch (...)
        {
            printf("UPDATE[%d] ERROR (LOADING SCREEN?). SLEEPING FOR 10 SECONDS\n", counter);
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
        counter++;
        if (counter > 10000)
            counter = 0;
    }
}

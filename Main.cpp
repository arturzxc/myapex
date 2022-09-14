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
        std::cout << "You.must.be.ROOT!!!" << std ::endl;
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
    while (1)
    {
        try
        {
            sense->update(localPlayer, players);
        }
        catch (...)
        {
            std::cout << "SENSE ERROR" << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}

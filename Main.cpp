#include <iostream>
#include <string>
#include "Utils.cpp"
#include "Offsets.cpp"
#include "Level.cpp"
#include "LocalPlayer.cpp"
#include "Player.cpp"

int main()
{
    std::cout << "PID: " << std::dec << utils::GetPID() << std ::endl;

    Level *level = new Level();
    level->print();

    LocalPlayer *localPlayer = new LocalPlayer();
    localPlayer->print();

    for (int i = 0; i < 6; i++)
    {
        Player *player = new Player(i);
        player->print();
        delete player;
    }

    delete localPlayer;
    delete level;
    return 0;
}

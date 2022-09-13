#include <iostream>
#include <string>
#include "Utils.cpp"
#include "Offsets.cpp"
#include "Level.cpp"
#include "Player.cpp"

int main()
{
    std::cout << "PID: " << std::dec << utils::GetPID() << std ::endl;
    Level *level = new Level();
    level->print();
    LocalPlayer *player = new LocalPlayer();
    player->print();
    std::cout << std ::endl;
    delete player;
    delete level;
    return 0;
}

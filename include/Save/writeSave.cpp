#include "../basicStructures/gameElements.h"
#include <iostream>
#include <fstream>
// using namespace std;

void saveGame(Game &game)
{
    // for testing i have used All Items Function
    // AllItems(test.player.inventory);
    std::ofstream fileSave("./gameSave.save");
    fileSave << "[Space Invaders]" << endl;
    fileSave << "[Player]" << endl;
    fileSave << "Health" << "\t" << game.player.health << endl;
    fileSave << "[Points]" << endl;
    bool playerEmpty = false;
    for (size_t i = 0; !playerEmpty && i < 100; i++)
    {
        if (game.score[i] == 0 || game.nick[i].nick[0] == '\0')
        {
            playerEmpty = true;
        }
        else
        {
            fileSave << "Nick" << "\t" << game.nick[i].nick[0] << game.nick[i].nick[1] << game.nick[i].nick[2] << endl;
            fileSave << "Points" << "\t" << game.score[i] << endl;
        }
    }
    fileSave.close();
}
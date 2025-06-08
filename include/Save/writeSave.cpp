#include "../basicStructures/gameElements.h"
#include <iostream>
#include <fstream>
// using namespace std;

void saveGame(Game &game)
{
    // for testing i have used All Items Function
    // AllItems(test.player.inventory);
    std::ofstream fileSave("C:\\Users\\Erick\\roguelike_cmd\\gameSave.save");
    fileSave << "[Space Invaders]" << endl;
    fileSave << "[Player]" << endl;
    fileSave << "Health" << "\t" << game.player.health << endl;
    fileSave << "Damage" << "\t" << game.player.damage << endl;
    fileSave << "Position" << "\t" << game.player.position.X << "\t" << game.player.position.Y << endl;
    fileSave << "Shield" << "\t" << game.player.shield << endl;
    bool playerEmpty = false;
    for (size_t i = 0; !playerEmpty && i < 100; i++)
    {
        if (game.points[i] == 0 || game.nick[i].nick[0] == '\0')
        {
            playerEmpty = true;
        }
        else
        {
            fileSave << "Points" << "\t" << game.points[i] << endl;
            fileSave << "Nick" << "\t" << game.nick[i].nick[0] << game.nick[i].nick[1] << game.nick[i].nick[2] << endl;
        }
    }
    fileSave.close();
}
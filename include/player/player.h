#ifndef player_h
#define player_h
#include <thread>
#include <windows.h>
#include "./items.h"
#include "../basicStructures/gameElements.h"
using namespace std;
void setPosition(int x, int y, Player player)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), player.position);
    cout << " ";
    player.position.X = x;
    player.position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), player.position);
    cout << player.playerChar;
}

void setRelativePosition(int x, int y, Player player)
{
    if ((player.position.X + x) >= 0 && (player.position.Y + y) >= 0)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), player.position);
        cout << " ";
        player.position.X += x;
        player.position.Y += y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), player.position);
        cout << player.playerChar;
    }
}
// function SavedGame(Game &game)

// {
//     Player * = game.player;
// }

#endif
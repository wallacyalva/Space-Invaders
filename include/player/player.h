#ifndef player_h
#define player_h
#include <thread>
#include <windows.h>
#include "./items.h"
// #include "../basicStructures/gameElements.h"
using namespace std;
struct Player
{
    COORD position = {0, 0};
    Inventory inventory;
    char projetil = '|';
    int health = 100, shield = 0, damage = 10, maxhealth = 100;
    void setPosition(int x, int y)
    {
        // functions to sound
        //  thread Steep(SteepSound);
        //  Steep.detach();
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
        cout << " ";
        position.X = x;
        position.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
        cout << playerChar;
    }

    void setRelativePosition(int x, int y)
    {
        if ((position.X + x) >= 0 && (position.Y + y) >= 0)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
            cout << " ";
            position.X += x;
            position.Y += y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
            cout << playerChar;
        }
    }
    char playerChar = '^';
    DWORD color = (0 << 4) | 7;
};
// function SavedGame(Game &game)
// {
//     Player * = game.player;
// }

#endif
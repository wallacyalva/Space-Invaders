#include <thread>
#include <windows.h>
#include "../include/player/items.h"
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
        position.X = x;
        position.Y = y;
    }

    void setRelativePosition(int &x, int &y)
    {
        position.X += x;
        position.Y += y;
    }
    char playerChar = '^';
    DWORD color = (0 << 4) | 7;
};
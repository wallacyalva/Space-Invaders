#ifndef gameElements
#define gameElements
#include "../player/player.h"
const int maxEnemies = 50;
int SCREEN_WIDTH = 0;
int SCREEN_HEIGHT = 0;
// utilities Functions
void getConsoleSize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    SCREEN_WIDTH = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    SCREEN_HEIGHT = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
struct GameElements
{
    char person = 'A';
    char enemy = 'W';
};

struct Enemy
{
    COORD position = {0, 0};
    bool active = true;
};
struct Game
{
    Player player;
    Enemy Enemies[maxEnemies] = {Enemy()};
};
#endif
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
    static const int columnMap = 23;
    static const int lineMap = 33;
};

struct Enemy
{
    COORD position = {0, 0};
    bool active = true;
};
struct Player
{
    COORD position = {0, 0};
    Inventory inventory;
    char projetil = '|';
    int health = 3, shield = 0, damage = 1, maxhealth = 3;
    char playerChar = 'A';
    DWORD color = (0 << 4) | 7;
    void setPosition(int x, int y)
    {
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
};
struct Game
{
    Player player;
    Enemy Enemies[maxEnemies] = {Enemy()};
};
#endif
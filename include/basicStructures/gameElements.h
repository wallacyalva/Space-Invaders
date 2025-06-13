#ifndef gameElements
#include <windows.h>
#include <iostream>
#include <conio.h>
#define gameElements
#include "../player/player.h"
using namespace std;

const int maxEnemies = 50;
int SCREEN_WIDTH = 0;
int SCREEN_HEIGHT = 0;
// utilities Functions
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void getConsoleSize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    SCREEN_WIDTH = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    SCREEN_HEIGHT = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
struct GameElements
{
    static const char person = 'A';
    static const int enemy = 3;
    static const int columnMap = 33;
    static const int lineMap = 23;
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
        if (((position.X + x) >= 1 && (position.Y + y) >= 1) &&
            ((position.X + x) <= GameElements::columnMap - 2 && (position.Y + y) <= GameElements::lineMap - 2))
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
struct Nick
{
    char nick[3] = {};
};
struct Game
{
    Player player;
    int score[10] = {};
    Nick nick[10] = {};
    Enemy enemies[maxEnemies] = {
        {{7, 1}, true}, {{9, 1}, true}, {{11, 1}, true}, {{13, 1}, true}, {{15, 1}, true}, {{17, 1}, true}, {{19, 1}, true}, {{21, 1}, true}, {{23, 1}, true}, {{25, 1}, true},
        {{7, 2}, true}, {{9, 2}, true}, {{11, 2}, true}, {{13, 2}, true}, {{15, 2}, true}, {{17, 2}, true}, {{19, 2}, true}, {{21, 2}, true}, {{23, 2}, true}, {{25, 2}, true},
        {{7, 3}, true}, {{9, 3}, true}, {{11, 3}, true}, {{13, 3}, true}, {{15, 3}, true}, {{17, 3}, true}, {{19, 3}, true}, {{21, 3}, true}, {{23, 3}, true}, {{25, 3}, true},
        {{7, 4}, true}, {{9, 4}, true}, {{11, 4}, true}, {{13, 4}, true}, {{15, 4}, true}, {{17, 4}, true}, {{19, 4}, true}, {{21, 4}, true}, {{23, 4}, true}, {{25, 4}, true},
        {{7, 5}, true}, {{9, 5}, true}, {{11, 5}, false}, {{13, 5}, true}, {{15, 5}, true}, {{17, 5}, true}, {{19, 5}, true}, {{21, 5}, true}, {{23, 5}, true}, {{25, 5}, true}
    };
};

string types[9] = {
    " ",      // 0 vazio
    "\u2588", // 1 parede
    "A",      // 2 player
    "W",      // 3 inimigo
    "!",      // 4 ataque inimigo
    " ",      // 5
    " ",      // 6
    " ",      // 7
    " "       // 8
};

Game game;

#endif
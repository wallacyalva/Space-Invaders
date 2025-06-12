#ifndef gameElements
#define gameElements
#include "../player/player.h"
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
    char person = 'A';
    char enemy = 'W';
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
    Enemy enemies[maxEnemies] = {
        {{1, 7}, true}, {{1, 9}, true}, {{1, 11}, true}, {{1, 13}, true}, {{1, 15}, true}, {{1, 17}, true}, {{1, 19}, true}, {{1, 21}, true}, {{1, 23}, true}, {{1, 25}, true}, {{2, 7}, true}, {{2, 9}, true}, {{2, 11}, true}, {{2, 13}, true}, {{2, 15}, true}, {{2, 17}, true}, {{2, 19}, true}, {{2, 21}, true}, {{2, 23}, true}, {{2, 25}, true}, {{3, 7}, true}, {{3, 9}, true}, {{3, 11}, true}, {{3, 13}, true}, {{3, 15}, true}, {{3, 17}, true}, {{3, 19}, true}, {{3, 21}, true}, {{3, 23}, true}, {{3, 25}, true}, {{4, 7}, true}, {{4, 9}, true}, {{4, 11}, true}, {{4, 13}, true}, {{4, 15}, true}, {{4, 17}, true}, {{4, 19}, true}, {{4, 21}, true}, {{4, 23}, true}, {{4, 25}, true}, {{5, 7}, true}, {{5, 9}, true}, {{5, 11}, true}, {{5, 13}, true}, {{5, 15}, true}, {{5, 17}, true}, {{5, 19}, true}, {{5, 21}, true}, {{5, 23}, true}, {{5, 25}, true}};
};

string types[9] = {
    " ",      // 0 vazio
    "\u2588", // 1 parede
    "A",      // 2 player
    "W",      // 3 inimigo
    " ",      // 4
    " ",      // 5
    " ",      // 6
    " ",      // 7
    " "       // 8
};

Game game;

#endif
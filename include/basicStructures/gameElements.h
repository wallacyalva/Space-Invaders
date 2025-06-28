#ifndef gameElements
#include <windows.h>
#include <iostream>
#include <conio.h>
#define gameElements
#include "../player/player.h"
#include "../player/items.h"
using namespace std;
#define speedInputUpdate 41
const int maxEnemyProjectiles = 50;
const int maxEnemies = 50;
const int itensMenu = 7;
int SCREEN_WIDTH = 0;
int SCREEN_HEIGHT = 0;
int maxLines = 5;
const int maxItems = 10;
int maxColuns = 10;
void cleanBuffer(){
while (_kbhit()) {
    _getch();
}
}
// utilities Functions
uint64_t timeMillis(){
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
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
    static const int enemyAttack = 4;
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
    int health = 5, shield = 0, damage = 1, maxhealth = 5;
    DWORD playerColor = (0 << 4) | 7;
    char playerChar = 'A';
    uint64_t speedBoostEndTime = 0;
    uint64_t extraShotsEndTime = 0;
    uint64_t multiShotEndTime = 0;
    DWORD color = (0 << 4) | 7;
    void setPosition(int x, int y)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
        cout << " ";
        position.X = x;
        position.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
        SetConsoleTextAttribute(hConsole, playerColor);
        cout << playerChar;
        SetConsoleTextAttribute(hConsole, (0 << 4) | 7); // Reseta para cor padrão
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
            SetConsoleTextAttribute(hConsole, playerColor);
            cout << playerChar;
            SetConsoleTextAttribute(hConsole, (0 << 4) | 7); // Reseta para cor padrão
        }
    }
};
struct Nick
{
    char nick[3] = {};
};
struct EnemyProjectile {
    COORD position = {0, 0};
    int speed = 1;
    char projectileChar = '!'; // seta pra baixo
    bool active = true;
};

Enemy enemiesLive[maxEnemies] = {
    {{7, 1}, true}, {{9, 1}, true}, {{11, 1}, true}, {{13, 1}, true}, {{15, 1}, true}, {{17, 1}, true}, {{19, 1}, true}, {{21, 1}, true}, {{23, 1}, true}, {{25, 1}, true},
    {{7, 2}, true}, {{9, 2}, true}, {{11, 2}, true}, {{13, 2}, true}, {{15, 2}, true}, {{17, 2}, true}, {{19, 2}, true}, {{21, 2}, true}, {{23, 2}, true}, {{25, 2}, true},
    {{7, 3}, true}, {{9, 3}, true}, {{11, 3}, true}, {{13, 3}, true}, {{15, 3}, true}, {{17, 3}, true}, {{19, 3}, true}, {{21, 3}, true}, {{23, 3}, true}, {{25, 3}, true},
    {{7, 4}, true}, {{9, 4}, true}, {{11, 4}, true}, {{13, 4}, true}, {{15, 4}, true}, {{17, 4}, true}, {{19, 4}, true}, {{21, 4}, true}, {{23, 4}, true}, {{25, 4}, true},
    {{7, 5}, true}, {{9, 5}, true}, {{11, 5}, true}, {{13, 5}, true}, {{15, 5}, true}, {{17, 5}, true}, {{19, 5}, true}, {{21, 5}, true}, {{23, 5}, true}, {{25, 5}, true}
};

struct Game{
    string menu[itensMenu] = {"Iniciar","Como Jogar","Score","Sobre","Dificuldade","Jogo Automático","Sair"};
    Player player = {Player()};
    int score[100] = {};
    Nick nick[100] = {};
    int enemiesDie = 0;
    Enemy enemies[maxEnemies];
    EnemyProjectile enemyProjectiles[maxEnemyProjectiles];
    int enemyProjectilesInGame = 0;
    Items activeItems[maxItems];
    int itemsInGame = 0;
    uint64_t freezeEnemiesEndTime = 0;
    int difficulty = 0;
    Game(int thisDifficulty = 0) {
        switch (thisDifficulty) {
            case 0: // Fácil
                player.health = 5;
                break;
            case 1: // Médio
                player.health = 4;
                break;
            case 2: // Difícil
                player.health = 3;
                break;
            default:
                player.health = 5;
                break;
        }
        player.maxhealth = player.health;
        // Copia os inimigos do modelo base
        for (int i = 0; i < maxEnemies; i++) {
            enemies[i] = enemiesLive[i];
        }
    }
};
const int MAX_INPUTS = 10; // Máximo de inputs simultâneos por frame
struct Input {
    int inputs[MAX_INPUTS] = {};
    int count = 0;
};
string types[9] = {
    " ",      // 0 vazio
    "\u2588", // 1 parede
    "A",      // 2 player
    "W",      // 3 inimigo
    "!",      // 4 ataque inimigo
    "\u2588", // 5 barreira
    " ",      // 6
    " ",      // 7
    " "       // 8
};

Game game;

// Variáveis de controle de movimento inimigo
int enemyDirection = 1; // 1 = direita, -1 = esquerda
int enemyMoveCounter = 0;
int baseEnemyDelay = 1000;
int enemyDelay = baseEnemyDelay; 

void initEnemies(Game &game) {
    for (int i = 0; i < maxEnemies; i++) {
        game.enemies[i] = enemiesLive[i];
    }
    game.enemiesDie = 0;
}
#endif
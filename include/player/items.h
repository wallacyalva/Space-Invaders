#include <string>
#include <windows.h>
#ifndef items_h
#define items_h

using namespace std;

// Criação dos itens, usado para se fazer os itens para o jogo
struct Items
{
    enum TypeofItems
    {
        ExtraLife,
        SpeedBoost,
        ExtraShots,
        MultiShot,
        ExtraPoints,
        FreezeEnemies,
        empty,
    };
    TypeofItems type = empty;
    bool active = false;
    COORD position = {0, 0};
    char itemAppearance = ' ';
    DWORD color = (0 << 4) | 7;
};

struct Inventory
{
    Items items[10] = {Items()};
    short int size;
};

#endif
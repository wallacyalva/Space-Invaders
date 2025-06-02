#include "./map.h"
#include <windows.h>
#include <ctime>
#include <iostream>
using namespace std;

int Seed(int y, int x, int seed)
{ // Adicionando geração infinitas de mapas
    seed = (y * 983) + (x * 797) + (seed * 929);
    seed = seed % 13 + 1;
    return seed; // selectMap
}
int generateSeed()
{ // Limite máximo
    srand(time(NULL));
    return rand() % 999999;
}
int enemyHealth = 10, enemyDamage = 10;
// void definedMap(Gamemap &currentMap, short int newMap[33][23])
// {
//     int amount = 0;
//     currentMap.clearEnemyRoom(); // Garante que a lista de inimigos está limpa

//     for (int i = 0; i < 16; i++)
//     {
//         for (int j = 0; j < 16; j++)
//         {
//             currentMap.map[i][j] = newMap[i][j];
//         }
//     }
//     enemyHealth += rand() % 5 + 1; // Adiciona dificuldade ao inimigos progressivamente
//     enemyDamage += rand() % 5 + 1; // Adiciona dificuldade ao inimigos progressivamente
//     for (int i = 0; i < 16; i++)
//     {
//         for (int j = 0; j < 16; j++)
//         {
//             // Verifica se:
//             // - Ainda há espaço na lista de inimigos (amount < maxEnemy)
//             // - A posição atual no mapa é um piso (floor)
//             // - A chance aleatória (1%) ocorreu
//             if (amount < currentMap.maxEnemy && currentMap.map[i][j] == Gamemap::entities::floor && (rand() % 100 < 1))
//             {
//                 // Se todas as condições forem verdadeiras, adicione o inimigo:
//                 currentMap.map[i][j] = currentMap.entities::enemy; // Coloca o inimigo visualmente no mapa
//                 currentMap.enemyList[amount] = enemy();            // Adiciona um novo inimigo à lista
//                 currentMap.enemyList[amount].health = enemyHealth;
//                 currentMap.enemyList[amount].damage = enemyDamage;

//                 // Define a posição do inimigo na lista.
//                 // ATENÇÃO: COORD usa X, Y. No loop, j é coluna (X) e i é linha (Y).
//                 currentMap.enemyList[amount].position = {(short)j, (short)i};

//                 amount++; // Incrementa o contador de inimigos adicionados à lista
//             }
//         }
//     }
// };

// Responsável por definir no mapa o que cada coisa é
void printMap(Gamemap &mapCurrent, HANDLE hConsole)
{
    SetConsoleTextAttribute(hConsole, mapCurrent.themeColor); // Define a cor tema
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            switch (mapCurrent.map[i][j])
            {
            // desenhando piso
            case 0:
                cout << " ";
                break;
            case mapCurrent.entities::parede:
                SetConsoleTextAttribute(hConsole, mapCurrent.themeColor);
                cout << "\u2588";
                break;
            case mapCurrent.entities::enemy:
                cout << "!";
                break;
            case mapCurrent.entities::portaLat:
                SetConsoleTextAttribute(hConsole, mapCurrent.themeColor);
                cout << "\u007C";
                break;
            case mapCurrent.entities::portaSupInf:
                SetConsoleTextAttribute(hConsole, mapCurrent.themeColor);
                cout << "-";
                break;
            case mapCurrent.entities::chest:
                SetConsoleTextAttribute(hConsole, Gamemap::amarelo);
                cout << "\u00A4";
                SetConsoleTextAttribute(hConsole, mapCurrent.themeColor);
                break;
            case mapCurrent.entities::mimic:
                SetConsoleTextAttribute(hConsole, Gamemap::amarelo);
                cout << "\u00A4";
                SetConsoleTextAttribute(hConsole, mapCurrent.themeColor);
                break;
            case mapCurrent.entities::vazio:
                cout << " ";
                break;
            case mapCurrent.entities::fakewall:
                SetConsoleTextAttribute(hConsole, Gamemap::branco);
                cout << "\u2588";
                SetConsoleTextAttribute(hConsole, mapCurrent.themeColor);
                break;
            case mapCurrent.entities::armadilha:
                cout << " ";
                break;
            case mapCurrent.entities::escada:
                SetConsoleTextAttribute(hConsole, Gamemap::branco);
                cout << 'H';
                SetConsoleTextAttribute(hConsole, mapCurrent.themeColor);
                break;
            default:
                break;
            }
        }
        cout << endl;
    }
    // SetConsoleTextAttribute(hConsole, Gamemap::padrao); /*Para caso queira resetar a coloração do mapa para "Default"*/
}
// Criação dos mapas, matriz mãe.
void mapa(Gamemap &newMap, short int mapSelect)
{
    // newMap.spawnPos[Gamemap::bottom] = {5, 5};
    newMap.enemy; // Inimigo = Número 2

    short int Template[33][23] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    // Seleção da matriz mapa para printar no terminal
    // switch (mapSelect)
    // {
    // case 1:
    //     definedMap(newMap, inicial1);
    //     break;
    // default:
    //     break;
    // }
}

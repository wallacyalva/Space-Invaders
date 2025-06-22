#include "../enemies/render.h"
#include "./gameMap.h"
#include <windows.h>
#include <ctime>
#include <iostream>
using namespace std;

// Responsável por definir no mapa o que cada coisa é
void printMap(Gamemap &mapCurrent, HANDLE hConsole)
{
    SetConsoleTextAttribute(hConsole, mapCurrent.themeColor); // Define a cor tema
    for (int i = 0; i < GameElements::lineMap; i++)
    {
        for (int j = 0; j < GameElements::columnMap; j++)
        {
            string typeCout = types[mapCurrent.map[i][j]];
            switch (mapCurrent.map[i][j])
            {
            // desenhando piso
            case mapCurrent.entities::parede:
                SetConsoleTextAttribute(hConsole, Gamemap::amarelo);
                break;
            case mapCurrent.entities::inimigo:
                SetConsoleTextAttribute(hConsole, Gamemap::vermelho);
                break;
            default:
                break;
            }
            cout << typeCout;
            SetConsoleTextAttribute(hConsole, mapCurrent.themeColor);

        }
        cout << endl;
    }
}

void renderBarrier(int Template[GameElements::lineMap][GameElements::columnMap]){
    
    Template[18][5] = 1;
    Template[18][6] = 1;
    Template[18][7] = 1;

    Template[19][5] = 1;
    Template[19][6] = 1;
    Template[19][7] = 1;
    
    Template[20][5] = 1;
    Template[20][7] = 1;
    

    
    Template[18][11] = 1;
    Template[18][12] = 1;
    Template[18][13] = 1;

    Template[19][11] = 1;
    Template[19][12] = 1;
    Template[19][13] = 1;
    
    Template[20][11] = 1;
    Template[20][13] = 1;
    


    Template[18][16] = 1;
    Template[18][17] = 1;
    Template[18][18] = 1;

    Template[19][16] = 1;
    Template[19][17] = 1;
    Template[19][18] = 1;
    
    Template[20][16] = 1;
    Template[20][18] = 1;
    


    Template[18][21] = 1;
    Template[18][22] = 1;
    Template[18][23] = 1;

    Template[19][21] = 1;
    Template[19][22] = 1;
    Template[19][23] = 1;
    
    Template[20][21] = 1;
    Template[20][23] = 1;
    


    Template[18][27] = 1;
    Template[18][28] = 1;
    Template[18][29] = 1;

    Template[19][27] = 1;
    Template[19][28] = 1;
    Template[19][29] = 1;
    
    Template[20][27] = 1;
    Template[20][29] = 1;
}

// Criação dos mapas, matriz mãe.
void mapa(Gamemap &newMap, int mapSelect)
{
    // newMap.spawnPos[Gamemap::bottom] = {5, 5};
    mapSelect = 1; // Seleciona o mapa a ser printado
    int Template[GameElements::lineMap][GameElements::columnMap] = {

        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//0
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//1
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//2
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//3
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//4
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//5
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//6
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//7
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//8
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//9
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//10
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//11
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//12
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//13
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//14
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//15
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//16
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//17
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//18
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//19
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//20
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//21
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};//22
    // Seleção da matriz mapa para printar no terminal
    renderEnemy(Template);
    
    renderBarrier(Template);

    switch (mapSelect)
    {
    case 1:
    {
        for (int i = 0; i < GameElements::lineMap; i++)
        {
            for (int j = 0; j < GameElements::columnMap; j++)
            {
                newMap.map[i][j] = Template[i][j];
            }
        }

        printMap(newMap, GetStdHandle(STD_OUTPUT_HANDLE));
        break;
    }
    default:
        cout << char(219);
        break;
    }
}

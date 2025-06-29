#include "../enemies/render.h"
#include "../basicStructures/gameElements.h"
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
                // cout<<types[1];
                break;
            case mapCurrent.entities::inimigo:{
                Enemy* inimigo = localizarInimigoRecursivo(enemiesLive,COORD {i,j});
                if (inimigo != nullptr) {
                    if (inimigo->life == 1) {
                        SetConsoleTextAttribute(hConsole, Gamemap::verde);
                    } else if (inimigo->life == 2) {
                        SetConsoleTextAttribute(hConsole, Gamemap::amarelo);
                    } else if (inimigo->life == 3) {
                        SetConsoleTextAttribute(hConsole, Gamemap::vermelho);
                    } else {
                        SetConsoleTextAttribute(hConsole, Gamemap::azul);
                    }
                } else {
                    SetConsoleTextAttribute(hConsole, Gamemap::rosa); // fallback
                }

            }
                break;
            case mapCurrent.entities::barreira:
                SetConsoleTextAttribute(hConsole, Gamemap::verde);
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

void printLevel(int mapSelect) {
    // Limpa a tela
    system("cls");

    // Centraliza o texto baseado no tamanho da janela
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns = 80, rows = 25; // valores padrão

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    string message = "Nível " + to_string(mapSelect + 1);
    int textX = (columns - message.size()) / 2;
    int textY = rows / 2;

    COORD pos = { (SHORT)textX, (SHORT)textY };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Verde claro
    cout << message;

    // Espera 3 segundos
    this_thread::sleep_for(chrono::seconds(1));

    // Limpa a mensagem se desejar:
    system("cls");
}

void renderBarrier(int Template[GameElements::lineMap][GameElements::columnMap]){

    Template[game.cordEndY][4] = Gamemap::barreira;
    Template[game.cordEndY][5] = Gamemap::barreira;
    Template[game.cordEndY][6] = Gamemap::barreira;

    Template[game.cordEndY + 1][4] = Gamemap::barreira;
    Template[game.cordEndY + 1][5] = Gamemap::barreira;
    Template[game.cordEndY + 1][6] = Gamemap::barreira;
    
    Template[game.cordEndY + 2][4] = Gamemap::barreira;
    Template[game.cordEndY + 2][6] = Gamemap::barreira;
    

    
    Template[game.cordEndY][10] = Gamemap::barreira;
    Template[game.cordEndY][11] = Gamemap::barreira;
    Template[game.cordEndY][12] = Gamemap::barreira;

    Template[game.cordEndY + 1][10] = Gamemap::barreira;
    Template[game.cordEndY + 1][11] = Gamemap::barreira;
    Template[game.cordEndY + 1][12] = Gamemap::barreira;
    
    Template[game.cordEndY + 2][10] = Gamemap::barreira;
    Template[game.cordEndY + 2][12] = Gamemap::barreira;
    


    Template[game.cordEndY][15] = Gamemap::barreira;
    Template[game.cordEndY][16] = Gamemap::barreira;
    Template[game.cordEndY][17] = Gamemap::barreira;

    Template[game.cordEndY + 1][15] = Gamemap::barreira;
    Template[game.cordEndY + 1][16] = Gamemap::barreira;
    Template[game.cordEndY + 1][17] = Gamemap::barreira;
    
    Template[game.cordEndY + 2][15] = Gamemap::barreira;
    Template[game.cordEndY + 2][17] = Gamemap::barreira;
    


    Template[game.cordEndY][20] = Gamemap::barreira;
    Template[game.cordEndY][21] = Gamemap::barreira;
    Template[game.cordEndY][22] = Gamemap::barreira;

    Template[game.cordEndY + 1][20] = Gamemap::barreira;
    Template[game.cordEndY + 1][21] = Gamemap::barreira;
    Template[game.cordEndY + 1][22] = Gamemap::barreira;
    
    Template[game.cordEndY + 2][20] = Gamemap::barreira;
    Template[game.cordEndY + 2][22] = Gamemap::barreira;
    


    Template[game.cordEndY][26] = Gamemap::barreira;
    Template[game.cordEndY][27] = Gamemap::barreira;
    Template[game.cordEndY][28] = Gamemap::barreira;

    Template[game.cordEndY + 1][26] = Gamemap::barreira;
    Template[game.cordEndY + 1][27] = Gamemap::barreira;
    Template[game.cordEndY + 1][28] = Gamemap::barreira;
    
    Template[game.cordEndY + 2][26] = Gamemap::barreira;
    Template[game.cordEndY + 2][28] = Gamemap::barreira;
}

// Criação dos mapas, matriz mãe.
void mapa(Gamemap &newMap, int mapSelect = 1)
{
    printLevel(mapSelect);

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

    for (int i = 0; i < GameElements::lineMap; i++)
    {
        for (int j = 0; j < GameElements::columnMap; j++)
        {
            newMap.map[i][j] = Template[i][j];
        }
    }

    printMap(newMap, GetStdHandle(STD_OUTPUT_HANDLE));
}

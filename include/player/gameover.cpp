#include <windows.h>
#include <iostream>
#include <conio.h>
using namespace std;

// Função para posicionar o cursor no console
void gotoxy(int x, int y)
{
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Função para exibir a tela de Game Over
void showGameOverScreen()
{
    system("cls"); // Limpa a tela
    string title = "GAME OVER";
    string message = "Pressione qualquer tecla para sair...";

    int titleX = (SCREEN_WIDTH - title.length()) / 2;
    int titleY = SCREEN_HEIGHT / 2 - 1;

    int msgX = (SCREEN_WIDTH - message.length()) / 2;
    int msgY = SCREEN_HEIGHT / 2 + 1;

    // Centraliza e exibe as mensagens
    gotoxy(titleX, titleY);
    cout << title;

    gotoxy(msgX, msgY);
    cout << message;

    getch(); // Espera o usuário apertar uma tecla
}

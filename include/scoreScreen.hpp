#include <iostream>
#include "./basicStructures/gameElements.h"
using namespace std;
void nickCp(char *destino, char *origem)
{
    for (int i = 0; i < 3; i++)
    {
        destino[i] = origem[i];
        i++;
    }
}
void ordenarRankingPorScore(Game &game, int quantidadeScores)
{
    for (int i = 0; i < quantidadeScores - 1; i++)
    {
        for (int j = i + 1; j < quantidadeScores; j++)
        {
            if (game.score[j] > game.score[i])
            {
                // Troca os scores
                int tempScore = game.score[i];
                game.score[i] = game.score[j];
                game.score[j] = tempScore;

                // Troca os nicks (assumindo que nick[i].nick é um char[])
                char tempNick[3];
                nickCp(tempNick, game.nick[i].nick);
                nickCp(game.nick[i].nick, game.nick[j].nick);
                nickCp(game.nick[j].nick, tempNick);
            }
        }
    }
}
void showScoreboard(Game &game, int quantidadeScores)
{
    getConsoleSize();
    ordenarRankingPorScore(game, quantidadeScores);
    system("cls"); // Limpa a tela (no Windows)
    COORD midPrint = {(SHORT)((SCREEN_WIDTH / 2) - 15), (SHORT)((SCREEN_HEIGHT / 2) - quantidadeScores)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), midPrint);
    cout << "===== RANKING DE SCORES =====";
    midPrint.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), midPrint);
    cout << "Posição  Score   Nick";
    midPrint.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), midPrint);
    cout << "--------------------------";
    midPrint.Y += 1;
    for (int i = 0; i < quantidadeScores; i++)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), midPrint);
        cout << i + 1 << "°         " << game.score[i] << "     ";
        for (int j = 0; j < 3; j++)
        {
            cout << game.nick[i].nick[j];
        }
        midPrint.Y++;
    }
    midPrint.X = (SCREEN_WIDTH / 2) - 24;
    midPrint.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), midPrint);
    cout << "Pressione Qualquer tecla para voltar ao menu...";
    getch();
}

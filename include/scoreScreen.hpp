#include <iostream>
#include "./basicStructures/gameElements.h"
using namespace std;

void showScoreboard(Game &game, int quantidadeScores)
{
    system("cls"); // Limpa a tela (no Windows)
    cout << "===== RANKING DE SCORES =====\n\n";
    cout << "Posição  Score   Nick\n";
    cout << "--------------------------\n";

    for (int i = 0; i < quantidadeScores; i++)
    {
        cout << i + 1 << "        "
             << game.score[i] << "     "
             << game.nick[i].nick << "\n";
    }

    cout << "\nPressione ENTER para voltar ao menu...";
    cin.ignore();
    cin.get();
}

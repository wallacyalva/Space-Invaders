#include <windows.h>
#include <iostream>
#include <cstdlib> // Para srand()
#include <ctime>   // Para time()
#include "./include/player/gameloop.h"
#include "./include/menu.cpp"
#include "./include/player/convert.cpp"
#include "./include/Save/writeSave.cpp"
#include "./include/Save/readSave.cpp"
#include "./include/scoreScreen.hpp"

int main()
{
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    int indexNick = readSave(game);
    int option = -1;
    do
    {
        option = -1;
        if (game.player.health <= 0)
            game.player.health = 3;
        cleanBuffer();
        option = mainMenu();
        switch (option)
        {
        case 0:
            /* Play Game*/
            // game.nick[indexNick] = SetNick();
            // system("cls");
            // cout << indexNick;
            // getch();
            game.player = Player();
            initEnemies(game);
            game.enemiesDie = 0;
            // Limpa os itens e power-ups da partida anterior
            game.itemsInGame = 0;
            for (int i = 0; i < maxItems; ++i) {
                game.activeItems[i].active = false;
            }
            game.enemyProjectilesInGame = 0;
            GameLoop(indexNick);
            saveGame(game);
            indexNick++;
            break;
        case 1:
            system("cls");
            cout<<indexNick;
            cout << "Como Jogar:\n\n";
            cout << "Use as teclas 'A' e 'D' para mover o player.\n";
            cout << "Use a tecla 'ESPAÇO' para atirar.\n";
            cout << "Use a tecla 'ESC' para sair do jogo.\n\n";
            cout << "Pontuação:\n\n";
            cout << "Você ganha pontos ao matar inimigos.\n";
            cout << "Você ganha mais pontos se for rápido ao passar na fase\n";
            cout << "A pontuação é exibida no final do jogo.\n\n\n";
            cout << "Pressione qualquer tecla para voltar ao menu principal.\n";
            getch(); // Espera o usuário pressionar uma tecla para continuar
            break;
        case 2:
            /* Score*/
            system("cls");
            showScoreboard(game, indexNick);
            break;
        case 3:
            system("cls");
            cout << "Sobre:\n\n";
            cout << "Space Invaders é um jogo de tiro inspirado no clássico jogo de arcade.\n";
            cout << "O objetivo é destruir todos os inimigos antes que eles cheguem ao chão.\n";
            cout << "Desenvolvido por Rodrigo Buratto Ribas, Erick Mafra e Wallacy Avarenga.\n";
            cout << "Este é um projeto de aprendizado.\n";
            cout << "Agradecimentos especiais ao Professor Alex Luciano Roesler Rese.\n\n";
            cout << "Pressione qualquer tecla para voltar ao menu principal.\n";
            getch();
            break;
        default:
            break;
        }
    } while (option != 4);
    if (game.player.health <= 0)
        game.player.health = 3;
    // saveGame(game);
    system("cls");
    return 0;
}

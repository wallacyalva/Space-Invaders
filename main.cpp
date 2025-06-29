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
            game.player.health = game.player.maxhealth;
        option = mainMenu(game);
        switch (option)
        {
        case 0:
            /* Play Game*/
            game.player = Player();
            aplicarDificuldade(game);
            aplicarNaves(game);
            initEnemies(game);
            game.enemiesDie = 0;
            game.bosshasKilled = false;
            // Limpa os itens e power-ups da partida anterior
            game.itemsInGame = 0;
            for (int i = 0; i < maxItems; ++i) {
                game.activeItems[i].active = false;
            }
            game.enemyProjectilesInGame = 0;
            GameLoop(indexNick,game);
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
        case 4:
            system("cls");
            game.difficulty = escolherDificuldade(game.difficulty);
            aplicarDificuldade(game);
            break;
        case 5:
            system("cls");
            game.difficulty = 0;
            game.player = Player();
            aplicarDificuldade(game);
            aplicarNaves(game);
            game.autoPlay = true;
            initEnemies(game);
            game.enemiesDie = 0;
            // Limpa os itens e power-ups da partida anterior
            game.itemsInGame = 0;
            for (int i = 0; i < maxItems; ++i) {
                game.activeItems[i].active = false;
            }
            game.enemyProjectilesInGame = 0;
            GameLoop(indexNick,game);
            game.autoPlay = false;
            saveGame(game);
            indexNick++;
            break;
        case 6:
            system("cls");
            game.nave = escolherNaves(game.nave);
            aplicarNaves(game);
            break;

            case 7:
            game.difficulty = 2;
            game.player = Player();
            aplicarDificuldade(game);
            aplicarNaves(game);
            initEnemies(game);
            game.enemiesDie = 0;
            // Limpa os itens e power-ups da partida anterior
            game.itemsInGame = 0;
            for (int i = 0; i < maxItems; ++i) {
                game.activeItems[i].active = false;
            }
            game.enemyProjectilesInGame = 0;
            game.infiniteGame = true;
            GameLoop(indexNick,game);
            game.autoPlay = false;
            indexNick++;
            break;
        default:
            break;
        }
    } while (option != (itensMenu-1));
    if (game.player.health <= 0)
        game.player.health =  game.player.maxhealth;
    // saveGame(game);
    system("cls");
    return 0;
}

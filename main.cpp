#include <windows.h>
#include <iostream>
#include "./include/player/gameloop.h"
#include "./include/menu.cpp"
int main()
{
    int option = -1;
    do
    {
        option = mainMenu();
        switch (option)
        {
        case 0:
            /* Play Game*/
            GameLoop();
            break;
        case 1:
            cout << "Como Jogar:\n\n";
            cout << "Use as teclas 'A' e 'D' para mover o player.\n";
            cout << "Use a tecla 'ESPAÇO' para atirar.\n";
            cout << "Use a tecla 'ESC' para sair do jogo.\n";
            cout << "Pontuação:\n\n";
            cout << "Você ganha pontos ao matar inimigos.\n";
            cout << "Você ganha mais pontos se for rápido ao passar na fase\n";
            cout << "A pontuação é exibida no final do jogo.\n\n\n";
            cout << "Pressione qualquer tecla para voltar ao menu principal.\n";
            getch(); // Espera o usuário pressionar uma tecla para continuar
            break;
        case 2:
            /* Score*/
            break;
        case 3:
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
    return 0;
}
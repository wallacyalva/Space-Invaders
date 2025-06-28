#include <windows.h>
#include <iostream>
#include <conio.h>
#include <thread>
#include<Xinput.h>
#include "../basicStructures/gameElements.h"
#include "../map/gameMap.h"
#include "./powerups.hpp"
using namespace std;

struct Projectile
{
    COORD position = {0, 0};
    int speed = 1;
    char projectileChar = '|';
};
void explosionSound() {
    XINPUT_VIBRATION vibration;
    vibration.wLeftMotorSpeed = 65535;
    vibration.wRightMotorSpeed = 65535; 
    XInputSetState(0,&vibration);
    Beep(1000, 80);
    Beep(800, 60);
    Beep(600, 100);
    vibration.wLeftMotorSpeed = 0;
    vibration.wRightMotorSpeed = 0; 
    XInputSetState(0,&vibration);
}

void visualExplosion(COORD position) {
    // Posições relativas para formar um 'X' com o caractere '*'
    COORD offsets[] = {
        {-1, -1}, {1, -1},
        {-1,  1}, {1,  1}
    };

    // Desenha a explosão
    SetConsoleTextAttribute(hConsole, Gamemap::amarelo); // Cor amarela para a explosão
    for (const auto& offset : offsets) {
        COORD explosionPos = { (SHORT)(position.X + offset.X), (SHORT)(position.Y + offset.Y) };
        // Garante que não vai desenhar fora do mapa
        if (explosionPos.X > 0 && explosionPos.X < GameElements::columnMap - 1 &&
            explosionPos.Y > 0 && explosionPos.Y < GameElements::lineMap - 1) {
            SetConsoleCursorPosition(hConsole, explosionPos);
            cout << "*";
        }
    }

    // Pausa para o efeito ser visível
    Sleep(75);

    // Apaga a explosão
    for (const auto& offset : offsets) {
        COORD explosionPos = { (SHORT)(position.X + offset.X), (SHORT)(position.Y + offset.Y) };
        if (explosionPos.X > 0 && explosionPos.X < GameElements::columnMap - 1 &&
            explosionPos.Y > 0 && explosionPos.Y < GameElements::lineMap - 1) {
            SetConsoleCursorPosition(hConsole, explosionPos);
            cout << " ";
        }
    }
}

Enemy* searchEnemy(COORD position) {
    // Itera por todos os inimigos para encontrar um na posição especificada.
    for (int i = 0; i < maxEnemies; ++i) {
        // Primeiro, verifica se o inimigo está ativo para otimizar a busca.
        if (game.enemies[i].active) {
            // Se estiver ativo, compara as coordenadas.
            if (game.enemies[i].position.X == position.X && game.enemies[i].position.Y == position.Y) {
                // Inimigo encontrado, retorna um ponteiro para ele.
                return &game.enemies[i];
            }
        }
    }
    // Se nenhum inimigo ativo for encontrado na posição, retorna nulo.
    return nullptr;
}
void UpdateProjectiles(Projectile *projectiles, int &projectilesinGame, Gamemap &gamemap, Game &game, int indexNick)
{
    for (int i = 0; i < projectilesinGame; ++i)
    {
        // Apaga a posição antiga do projétil
        SetConsoleCursorPosition(hConsole, projectiles[i].position);
        cout << " ";

        // Move o projétil
        projectiles[i].position.Y -= projectiles[i].speed;

        // Verifica se o projétil saiu da tela ou atingiu um inimigo
        bool hit = false;
        if (projectiles[i].position.Y < 1){
            hit = true; // Saiu do topo da tela
        }else{
            Enemy *enemy = searchEnemy(projectiles[i].position);
            if ((enemy != nullptr && enemy->active)){
                    hit = true;
                    COORD enemyPos = enemy->position; // Salva a posição antes de desativar o inimigo

                    thread explosion(explosionSound);
                    explosion.detach();

                    // Inicia o efeito visual da explosão em uma nova thread
                    visualExplosion(enemyPos);
                    

                    // Chance de dropar um power-up
                    if(rand() % 100 < 20) { // 20% de chance
                        Items::TypeofItems itemType = (Items::TypeofItems)(rand() % 6);
                        CreateItem(game, itemType, enemyPos);
                    }
                    game.score[indexNick] += 10;
                    game.enemiesDie += 1;
                    // Apaga o inimigo da tela imediatamente para evitar "fantasmas"
                    SetConsoleCursorPosition(hConsole, enemyPos);
                    cout << " ";
                    enemy->active = false;
            }else if(gamemap.map[projectiles[i].position.Y][projectiles[i].position.X] == Gamemap::barreira){// Verifica colisão com barreira
                hit = true;
                gamemap.map[projectiles[i].position.Y][projectiles[i].position.X] = 0;// Limpa o caractere da barreira na tela
            }else{
                SetConsoleCursorPosition(hConsole, projectiles[i].position);
                cout << " ";
            }
        }

        if (hit)
        {
            // Remove o projétil da lista de forma eficiente
            projectiles[i] = projectiles[projectilesinGame - 1];
            projectilesinGame--;
            i--; // Reavalia o índice atual, que agora contém um novo projétil
        }
        else
        {
            // Se não atingiu nada, desenha o projétil na nova posição
            SetConsoleCursorPosition(hConsole, projectiles[i].position);
            cout << projectiles[i].projectileChar;
        }
    }
}
void CreateProjectiles(Projectile *&projectiles, Projectile projectile, int &projectilesInGame)
{
    // Aloca novo array com +1
    Projectile *newProjectiles = new Projectile[projectilesInGame + 1];

    // Copia projéteis antigos
    for (int i = 0; i < projectilesInGame; i++)
    {
        newProjectiles[i] = projectiles[i];
    }

    // Adiciona novo projétil
    newProjectiles[projectilesInGame] = projectile;

    // Libera o antigo
    delete[] projectiles;

    // Atualiza ponteiro e contador
    projectiles = newProjectiles;
    projectilesInGame++;
}
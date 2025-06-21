#include <windows.h>
#include <iostream>
#include <conio.h>
#include <thread>
#include<Xinput.h>
#include "../basicStructures/gameElements.h"
#include "../map/gameMap.h"
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
    for (int i = 0; i < projectilesinGame; i++)
    {
        if (projectiles[i].position.Y == 1)
        {
            SetConsoleCursorPosition(hConsole, projectiles[i].position);
            cout << " ";
            projectiles[i].position.Y--;
        }

        if (projectiles[i].position.Y > 1)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), projectiles[i].position);
            cout << " ";
            projectiles[i].position.Y--;
            Enemy *enemy = searchEnemy(projectiles[i].position);
            if (gamemap.map[projectiles[i].position.Y][projectiles[i].position.X] == Gamemap::inimigo && enemy != nullptr)
            {
                thread explosion(explosionSound);
                explosion.detach();
                if(rand()%100 < 10){
                    Items item;
                    int itemSelect =rand()%6;
                    switch (itemSelect)
                    {
                    /*Vida Extra*/
                    case 0:
                        item.itemAppearance = '♥';
                        item.position = projectiles[i].position;
                        
                        game.player.health++;
                        break;
                    case 1:
                        game.player.damage++;
                        break;
                    case 2:
                        game.player.shield++;
                        break;
                    case 3:
                        game.player.maxhealth++;
                        break;

                    }}
                game.score[indexNick] += 10;
                game.enemiesDie += 1;
                gamemap.map[projectiles[i].position.Y][projectiles[i].position.X] = Gamemap::vazio;
                SetConsoleCursorPosition(hConsole, projectiles[i].position);
                cout << " ";
                if (enemy != nullptr){
                    enemy->active = false;
                }
                if (i == 0)
                {
                    projectiles = nullptr;
                    delete[] projectiles;
                    projectilesinGame = 0;
                }
            }
            else
            {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), projectiles[i].position);
                cout << projectiles[i].projectileChar;
            }
        }
        else
        {
            if (i == 0)
            {
                projectiles = nullptr;
                delete[] projectiles;
                projectilesinGame = 0;
            }
            /* case to multiples shots will make later*/
            break;
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
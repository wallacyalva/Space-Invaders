#include <conio.h>
#include "./player.h"
#include "../basicStructures/gameElements.h"
#include "../map/maps.h"
#include "./projectiles.hpp"
#include "./gameover.cpp"
#include "./powerups.hpp"
#include "../enemies/move.h"
#include "../enemies/attack.h"
#include "./inputs.h"
#include <thread>
#include<chrono>
#include<windows.h>
void fireSound() {
    Beep(1200, 30);
    Beep(1000, 20);
}
void laserSound() {
    Beep(1500, 20);
    Beep(1700, 15);
}

int startTime;
string convertTimetoText(int seconds){
    string segundos = to_string(seconds%60);
    if (seconds%60 < 10)
    {
        segundos = "0"+segundos;
    }
    string minutos = to_string(seconds/60);
    if (seconds/60 < 10)
    {
        minutos = "0"+minutos;
    }
    return minutos+":"+segundos;
}
void hudPrint(Game &game, int indexNick)
{
    SetConsoleCursorPosition(hConsole, {(SHORT)(GameElements::columnMap + 2), 0});
    cout << "Player Health: ";
    for (int i = 1; i <= game.player.maxhealth - (game.player.health); i++)
    {
        SetConsoleCursorPosition(hConsole, {(SHORT)(GameElements::columnMap + 21 - i), 0});
        cout << " ";
    }
    SetConsoleCursorPosition(hConsole, {(SHORT)(GameElements::columnMap + 18), 0});
    for (int i = 0; i < game.player.health; i++)
    {
        cout << "♥";
    }
    SetConsoleCursorPosition(hConsole, {(SHORT)(GameElements::columnMap + 2), 1});
    cout << "Score: " << game.score[indexNick];
    SetConsoleCursorPosition(hConsole, {(SHORT)(GameElements::columnMap + 2), 2});
    cout << "Time: " << convertTimetoText((timeMillis()/1000)-startTime);

    // Exibe os power-ups ativos
    int hudLine = 4;
    auto print_powerup = [&](const char* name, uint64_t endTime) {
        SetConsoleCursorPosition(hConsole, {(SHORT)(GameElements::columnMap + 2), (SHORT)hudLine});
        uint64_t currentTime = timeMillis();
        if (currentTime < endTime) {
            cout << name << ": " << (endTime - currentTime) / 1000 << "s   ";
        } else {
            // Limpa a linha se o power-up expirou
            cout << "                    "; // Espaços para limpar a linha
        }
        hudLine++;
    };

    print_powerup("Speed Boost ", game.player.speedBoostEndTime);
    print_powerup("Extra Shots ", game.player.extraShotsEndTime);
    print_powerup("Multi-Shot  ", game.player.multiShotEndTime);
    
    // Para o freeze, que é global
    SetConsoleCursorPosition(hConsole, {(SHORT)(GameElements::columnMap + 2), (SHORT)hudLine});
    uint64_t currentTime = timeMillis();
    cout << (currentTime < game.freezeEnemiesEndTime ? "Enemies Frozen: " + to_string((game.freezeEnemiesEndTime - currentTime) / 1000) + "s   " : "                    ");

}
bool infiniteShots = false;
void GameLoop(int &indexNick,Game &game)
{
    startTime = timeMillis()/1000;
    SetConsoleOutputCP(CP_UTF8);
    bool gameexit = true;
    Player *player = &game.player;
    Player player2 = Player();
    Projectile *projectiles = nullptr;
    getConsoleSize();
    player2.position.Y = GameElements::lineMap - 3;
    player2.position.X = GameElements::columnMap / 2;
    player2.playerChar = GameElements::person;
    game.player.position.Y = GameElements::lineMap - 2;
    game.player.position.X = GameElements::columnMap / 2;
    game.player.playerChar = GameElements::person;
    int projectilesinGame = 0;
    uint64_t inputUpdate = 0;
    uint64_t nextUpdate = 0;
    uint64_t nextUpdateEnemy = 0;
    uint64_t timeAttack = (timeMillis()) + (1000 / 60) * 400;
    uint64_t nextUpdateItems = 0;
    uint64_t nextUpdateAttack = 0;
    Gamemap gamemap;
    system("cls");
    mapa(gamemap, 1);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), game.player.position);
    cout << game.player.playerChar;
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    Input input = Input();
    do
    {
        gameexit = !gameover(game);
        hudPrint(game, indexNick);
        // input.inputs = nullptr;
        if (inputUpdate <= (timeMillis()))
        {
            // 24 fps
            inputUpdate = (timeMillis()) + (1000 / 24);
            inputGet(input);
        }
        for (int i = 0; i < input.count; i++)
        {
            int inputActual = input.inputs[i];
            switch (inputActual)
            {
                case 'a':
                case 'A': {
                    int moveAmount = 1;
                    if (timeMillis() < player->speedBoostEndTime) {
                        moveAmount = 2; // Move mais rápido com o power-up
                    }
                    player->setRelativePosition(-moveAmount, 0);

                    // projectiles = nullptr;
                    break;
                }
                case VK_LEFT:
                    player2.setRelativePosition(-1, 0);
                    break;
                case VK_RIGHT:
                    player2.setRelativePosition(1, 0);
                    break;
                case 'd':
                case 'D': {
                    int moveAmount = 1;
                    if (timeMillis() < player->speedBoostEndTime) {
                        moveAmount = 2; // Move mais rápido com o power-up
                    }
                    player->setRelativePosition(moveAmount, 0);
                    // projectiles = nullptr;
                    break;
                }
                /*spacebar*/
                case 32:
                {
                    /*atack*/

                    /*create projectile*/
                    Projectile actualProjectile;

                    bool canFire = (projectilesinGame < 1 || infiniteShots || timeMillis() < player->extraShotsEndTime);

                    if (canFire)
                    {
                        thread fire(laserSound);
                        fire.detach();

                        if (timeMillis() < player->multiShotEndTime) {
                            // Tiro triplo
                            Projectile p1, p2, p3;
                            p1.position = {player->position.X, (SHORT)(player->position.Y - 1)};
                            p2.position = {SHORT(player->position.X - 2), (SHORT)(player->position.Y - 1)};
                            p3.position = {(SHORT)(player->position.X + 2), (SHORT)(player->position.Y - 1)};
                            CreateProjectiles(projectiles, p1, projectilesinGame);
                            CreateProjectiles(projectiles, p2, projectilesinGame);
                            CreateProjectiles(projectiles, p3, projectilesinGame);
                        } else {
                            // Tiro único
                            actualProjectile.position.X = player->position.X;
                            actualProjectile.position.Y = player->position.Y - 1;
                            CreateProjectiles(projectiles, actualProjectile, projectilesinGame);
                        }
                    }
                    break;
                }
                case VK_RETURN:
                {
                    Projectile actualProjectile;
                    actualProjectile.position.X = player2.position.X;
                    actualProjectile.position.Y = player2.position.Y - 1;
                    if (projectilesinGame < 1 || infiniteShots)
                    {
                        CreateProjectiles(projectiles, actualProjectile, projectilesinGame);
                        thread fire(fireSound);
                        fire.detach();
                    }
                    break;
                }
                /*escape*/
                /*game Exit*/
                case VK_ESCAPE:
                    gameexit = false;
                    /*escape*/
                    break;
                /*game over screen test*/
                case 'c':
                case 'C':
                {
                    int cheatCode = getch();
                    switch (cheatCode)
                    {
                    /*game over*/
                    case 'g':
                    case 'G':
                        gameexit = false;
                        showGameOverScreen(game,indexNick);
                        break;
                    case 'k':
                    case 'K':
                        game.player.health--;
                        break;
                    case 'i':
                    case 'I':
                        infiniteShots = true;
                        break;
                    case 's':
                    case 'S':
                        cout << game.score;
                        break;
                    }
                    break;
                }
            }}
        if (projectiles != nullptr)
        {
            if (nextUpdate <= (timeMillis()))
            {
                // 60 fps test 1 second/60 frames * lowspeed
                nextUpdate = (timeMillis()) + (1000 / 60) * 2.5;
                UpdateProjectiles(projectiles, projectilesinGame, gamemap, game, indexNick);
            }
        }
        
        if (nextUpdateEnemy <= (timeMillis())){
            // Só move os inimigos se o power-up de congelar não estiver ativo
            if (timeMillis() > game.freezeEnemiesEndTime) {
                nextUpdateEnemy = (timeMillis()) + (1000 / 60) * (100 - game.enemiesDie);
                moveEnemies(gamemap,game);
            }
        }
        if(timeAttack <= (timeMillis())){
            timeAttack = (timeMillis()) + (1000 / 60) * 400;
            makeAttackEnemy(gamemap,game);
        }
        if(game.enemyProjectilesInGame > 0){
            if (nextUpdateAttack <= (timeMillis())){
                // 60 fps test 1 second/60 frames * lowspeed
                nextUpdateAttack = (timeMillis()) + (1000 / 60) * 10;
                updateEnemyProjectiles(gamemap, game);
            }
        }
        if (game.itemsInGame > 0) {
            // Atualiza os itens em uma taxa um pouco mais lenta para não sobrecarregar
            if (nextUpdateItems <= (timeMillis()))
            {
                nextUpdateItems = timeMillis() + 150; // Itens caem a cada 150ms
                UpdateItems(game, indexNick);
            }
        }


    } while ((game.player.health > 0)||(player2.health > 0) && gameexit);
    
    cleanBuffer();
    showGameOverScreen(game,indexNick);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

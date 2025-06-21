#include <conio.h>
#include "./player.h"
#include "../basicStructures/gameElements.h"
#include "../map/maps.h"
#include "./projectiles.hpp"
#include "./gameover.cpp"
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
uint64_t timeMillis()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
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
}
bool infiniteShots = false;
void GameLoop(int &indexNick,Game &game)
{
    startTime = timeMillis()/1000;
    SetConsoleOutputCP(CP_UTF8);
    bool gameexit = true;
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
    Input input = {nullptr,0};
    do
    {
        gameexit = !checkAllEnemiesDie(game);
        hudPrint(game, indexNick);
        input.inputs = nullptr;
        if (inputUpdate <= (timeMillis()))
        {
            // 24 fps
            inputUpdate = (timeMillis()) + (1000 / 24);
            inputGet(input);
        }
        for (int i = 0; i < input.count; i++)
        {
            if(input.inputs != nullptr){
            int inputActual = input.inputs[i];
            switch (inputActual)
            {
                case 'a':
                case 'A':
                    game.player.setRelativePosition(-1, 0);
                    // projectiles = nullptr;
                    break;
                case VK_LEFT:
                    player2.setRelativePosition(-1, 0);
                    break;
                case VK_RIGHT:
                    player2.setRelativePosition(1, 0);
                    break;
                case 'd':
                case 'D':
                    game.player.setRelativePosition(1, 0);
                    // projectiles = nullptr;
                    break;
                /*spacebar*/
                case 32:
                {
                    /*atack*/

                    /*create projectile*/
                    Projectile actualProjectile;
                    actualProjectile.position.X = game.player.position.X;
                    actualProjectile.position.Y = game.player.position.Y - 1;
                    if (projectilesinGame < 1 || infiniteShots)
                    {
                        CreateProjectiles(projectiles, actualProjectile, projectilesinGame);
                        thread fire(laserSound);
                        fire.detach();
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
                case 27:
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
            }}}
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
            nextUpdateEnemy = (timeMillis()) + (1000 / 60) * (100 - game.enemiesDie);
            moveEnemies(gamemap,game);
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


    } while ((game.player.health > 0)||(player2.health > 0) && gameexit);
    
    cleanBuffer();
    showGameOverScreen(game,indexNick);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

#include <conio.h>
#include "./player.h"
#include "../basicStructures/gameElements.h"
#include "../map/maps.h"
#include "./projectiles.hpp"
#include "./gameover.cpp"
#include "../enemies/move.h"
#include "../enemies/attack.h"
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
void GameLoop(int &indexNick)
{
    startTime = timeMillis()/1000;
    SetConsoleOutputCP(CP_UTF8);
    bool gameexit = true;
    Player *player;
    player = &game.player;
    Projectile *projectiles = nullptr;
    int input = 0;
    getConsoleSize();
    player->position.Y = GameElements::lineMap - 2;
    player->position.X = GameElements::columnMap / 2;
    player->playerChar = GameElements::person;
    int projectilesinGame = 0;
    int nextUpdate = 0;
    int nextUpdateEnemy = 0;
    int timeAttack = (INT)(timeMillis()) + (1000 / 60) * 400;
    int nextUpdateAttack = 0;
    Gamemap gamemap;
    system("cls");
    mapa(gamemap, 1);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), player->position);
    cout << player->playerChar;
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    do
    {
        gameexit = !checkAllEnemiesDie(game);
        hudPrint(game, indexNick);
        input = 0;
        if (_kbhit())
            input = getch();
        switch (input)
        {
            case 'a':
            case 'A':
                player->setRelativePosition(-1, 0);
                // projectiles = nullptr;
                break;
            case 'd':
            case 'D':
                player->setRelativePosition(1, 0);
                // projectiles = nullptr;
                break;
            /*spacebar*/
            case 32:
            {
                /*atack*/

                /*create projectile*/
                Projectile actualProjectile;
                actualProjectile.position.X = player->position.X;
                actualProjectile.position.Y = player->position.Y - 1;
                if (projectilesinGame < 1 || infiniteShots)
                {
                    CreateProjectiles(projectiles, actualProjectile, projectilesinGame);
                }
                break;
            }
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
                    player->health--;
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
        }
        if (projectiles != nullptr)
        {
            if (nextUpdate <= (INT)(timeMillis()))
            {
                // 60 fps test 1 second/60 frames * lowspeed
                nextUpdate = (INT)(timeMillis()) + (1000 / 60) * 2.5;
                UpdateProjectiles(projectiles, projectilesinGame, gamemap, game, indexNick);
            }
        }
        
        if (nextUpdateEnemy <= (INT)(timeMillis())){
            nextUpdateEnemy = (INT)(timeMillis()) + (1000 / 60) * (100 - game.enemiesDie);
            moveEnemies(gamemap,game);
        }
        if(timeAttack <= (INT)(timeMillis())){
            timeAttack = (INT)(timeMillis()) + (1000 / 60) * 400;
            makeAttackEnemy(gamemap,game);
        }
        if(game.enemyProjectilesInGame > 0){
            if (nextUpdateAttack <= (INT)(timeMillis())){
                // 60 fps test 1 second/60 frames * lowspeed
                nextUpdateAttack = (INT)(timeMillis()) + (1000 / 60) * 10;
                updateEnemyProjectiles(gamemap, game);
            }
        }


    } while (player->health > 0 && gameexit);
    // if (player->health <= 0)
    // {
        showGameOverScreen(game,indexNick);
        indexNick++;
    // }
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

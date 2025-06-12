#include <conio.h>
#include "./player.h"
#include "../basicStructures/gameElements.h"
#include "../map/maps.h"
#include "./projectiles.hpp"
#include "./gameover.cpp"
uint64_t timeMillis()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
bool infiniteShots = false;
void GameLoop(int indexNick)
{
    SetConsoleOutputCP(CP_UTF8);
    bool gameexit = true;
    Player player;
    Projectile *projectiles = nullptr;
    int input = 0;
    getConsoleSize();
    player.position.Y = GameElements::lineMap - 2;
    player.position.X = GameElements::columnMap / 2;
    player.playerChar = GameElements::person;
    int projectilesinGame = 0;
    int nextUpdate = 0;
    Gamemap gamemap;
    system("cls");
    mapa(gamemap, 1);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), player.position);
    cout << player.playerChar;

    do
    {
        input = 0;
        if (_kbhit())
            input = getch();
        switch (input)
        {
        case 'a':
        case 'A':
            player.setRelativePosition(-1, 0);
            // projectiles = nullptr;
            break;
        case 'd':
        case 'D':
            player.setRelativePosition(1, 0);
            // projectiles = nullptr;
            break;
        /*spacebar*/
        case 32:
        {
            /*atack*/

            /*create projectile*/
            Projectile actualProjectile;
            actualProjectile.position.X = player.position.X;
            actualProjectile.position.Y = player.position.Y - 1;
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
                showGameOverScreen();
                gameexit = false;
                break;
            case 'k':
            case 'K':
                player.health--;
                break;
            case 'i':
            case 'I':
                // infiniteShots = true;
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

    } while (player.health > 0 && gameexit);
    if (player.health <= 0)
    {
        showGameOverScreen();
    }
}
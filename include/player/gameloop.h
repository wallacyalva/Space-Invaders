#include <conio.h>
#include "./player.h"
#include "../basicStructures/gameElements.h"
#include "../map/maps.h"
#include "./projectiles.hpp"
uint64_t timeMillis()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
void GameLoop()
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
            if (projectilesinGame < 1)
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
        }
        if (projectiles != nullptr)
        {
            if (nextUpdate <= (INT)(timeMillis()))
            {
                // 60 fps test 1 second/60 frames * lowspeed
                nextUpdate = (INT)(timeMillis()) + (1000 / 60) * 2.5;
                UpdateProjectiles(projectiles, projectilesinGame, gamemap);
            }
        }

    } while (player.health > 0 && gameexit);
}
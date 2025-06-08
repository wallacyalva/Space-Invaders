#include <conio.h>
#include "./player.h"
#include "../basicStructures/gameElements.h"
#include "../map/maps.h"
struct Projectile
{
    COORD position = {0, 0};
    int speed = 1;
    char projectileChar = '|';
};

void UpdateProjectiles(Projectile *projectiles, int projectilesinGame)
{
    for (int i = 0; i < projectilesinGame; i++)
    {
        if (projectiles[i].position.Y > 0)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), projectiles[i].position);
            cout << " ";
            projectiles[i].position.Y--;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), projectiles[i].position);
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
uint64_t timeMillis()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
void GameLoop()
{
    bool gameexit = true;
    Player player;
    Projectile *projectiles = nullptr;
    int input = 0;
    getConsoleSize();
    player.position.Y = SCREEN_HEIGHT - 2;
    player.position.X = SCREEN_WIDTH / 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), player.position);
    cout << player.playerChar;
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
            CreateProjectiles(projectiles, actualProjectile, projectilesinGame);
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
                UpdateProjectiles(projectiles, projectilesinGame);
            }
        }

    } while (player.health > 0 && gameexit);
}
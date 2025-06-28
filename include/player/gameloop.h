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
void handleInput(Input& input, Game& game, Player& player1, Player& player2, Projectile*& projectiles, int& projectilesInGame, bool& gameexit, int indexNick, bool infiniteShots = false)
{
    for (int i = 0; i < input.count; i++) {
        int inputActual = input.inputs[i];

        switch (inputActual) {
        // Movimento Player 1
        case 'a': case 'A': {
            int moveAmount = (timeMillis() < player1.speedBoostEndTime) ? 2 : 1;
            player1.setRelativePosition(-moveAmount, 0);
            break;
        }
        case 'd': case 'D': {
            int moveAmount = (timeMillis() < player1.speedBoostEndTime) ? 2 : 1;
            player1.setRelativePosition(moveAmount, 0);
            break;
        }

        // Movimento Player 2
        case VK_LEFT: {
            int moveAmount = (timeMillis() < player2.speedBoostEndTime) ? 2 : 1;
            player2.setRelativePosition(-moveAmount, 0);
            break;
        }
        case VK_RIGHT: {
            int moveAmount = (timeMillis() < player2.speedBoostEndTime) ? 2 : 1;
            player2.setRelativePosition(moveAmount, 0);
            break;
        }

        // Ataque Player 1 (espaço)
        case 32: {
            bool canFire = (projectilesInGame < 1 || infiniteShots || timeMillis() < player1.extraShotsEndTime);

            if (canFire) {
                std::thread fire(laserSound);
                fire.detach();

                if (timeMillis() < player1.multiShotEndTime) {
                    Projectile p1 = {{player1.position.X, SHORT(player1.position.Y - 1)}};
                    Projectile p2 = {{SHORT(player1.position.X - 2), SHORT(player1.position.Y - 1)}};
                    Projectile p3 = {{SHORT(player1.position.X + 2), SHORT(player1.position.Y - 1)}};
                    CreateProjectiles(projectiles, p1, projectilesInGame);
                    CreateProjectiles(projectiles, p2, projectilesInGame);
                    CreateProjectiles(projectiles, p3, projectilesInGame);
                } else {
                    Projectile p = {{player1.position.X, SHORT(player1.position.Y - 1)}};
                    CreateProjectiles(projectiles, p, projectilesInGame);
                }
            }
            break;
        }

        // Ataque Player 2 (Enter)
        case VK_RETURN: {
            bool canFire = (projectilesInGame < 1 || infiniteShots || timeMillis() < player2.extraShotsEndTime);

            if (canFire) {
                std::thread fire(fireSound);
                fire.detach();

                if (timeMillis() < player2.multiShotEndTime) {
                    Projectile p1 = {{player2.position.X, SHORT(player2.position.Y - 1)}};
                    Projectile p2 = {{SHORT(player2.position.X - 2), SHORT(player2.position.Y - 1)}};
                    Projectile p3 = {{SHORT(player2.position.X + 2), SHORT(player2.position.Y - 1)}};
                    CreateProjectiles(projectiles, p1, projectilesInGame);
                    CreateProjectiles(projectiles, p2, projectilesInGame);
                    CreateProjectiles(projectiles, p3, projectilesInGame);
                } else {
                    Projectile p = {{player2.position.X, SHORT(player2.position.Y - 1)}};
                    CreateProjectiles(projectiles, p, projectilesInGame);
                }
            }
            break;
        }

        // Escape: sair do jogo
        case VK_ESCAPE:
            gameexit = false;
            break;

        // Cheats
        case 'c': case 'C': {
            int cheatCode = getch();
            switch (cheatCode) {
                case 'g': case 'G':
                    gameexit = false;
                    showGameOverScreen(game, indexNick);
                    break;
                case 'k': case 'K':
                    game.player.health--;
                    break;
                case 'i': case 'I':
                    infiniteShots = true;
                    break;
                case 's': case 'S':
                    cout << game.score;
                    break;
            }
            break;
        }
        }
    }
}

bool infiniteShots = false;
void GameLoop(int &indexNick,Game &game)
{
    startTime = timeMillis()/1000;
    SetConsoleOutputCP(CP_UTF8);
    bool gameexit = true;
    Player *player = &game.player;
    Player player2 = Player();
    player2.playerColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
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
    uint64_t nextUpdateHud = 0;
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
    SetConsoleTitle("Space Invaders - Playing");
    do
    {
        gameexit = !gameover(game);
        // input.inputs = nullptr;
        input.count = 0;
        if (inputUpdate <= (timeMillis()))
        {
            inputUpdate = (timeMillis()) + (speedInputUpdate);
            //adquire o input de forma assyncrona pega input de teclado e controle
            thread inputs(inputGet,ref(input));
            inputs.join();
            //convert input para ações
            thread handle(handleInput,ref(input), ref(game), ref(*player), ref(player2), ref(projectiles),
            ref(projectilesinGame), ref(gameexit), indexNick, infiniteShots);
            handle.join();
        }
        
        if (projectiles != nullptr)
        {
            if (nextUpdate <= (timeMillis()))
            {
                // 60 fps test 1 second/60 frames * lowspeed
                nextUpdate = (timeMillis()) + (1000 / 60) * game.timeAttProject;
                UpdateProjectiles(projectiles, projectilesinGame, gamemap, game, indexNick);
            }
        }
        
        if (nextUpdateEnemy <= (timeMillis())){
            // Só move os inimigos se o power-up de congelar não estiver ativo
            if (timeMillis() > game.freezeEnemiesEndTime) {
                nextUpdateEnemy = (timeMillis()) + (1000 / 60) * (game.timeMoveEnemy - game.enemiesDie);
                moveEnemies(gamemap,game);
            }
        }
        if(timeAttack <= (timeMillis())){
            timeAttack = (timeMillis()) + (1000 / 60) * game.timeAttackEnemy;
            makeAttackEnemy(gamemap,game);
        }
        if(game.enemyProjectilesInGame > 0){
            if (nextUpdateAttack <= (timeMillis())){
                // 60 fps test 1 second/60 frames * lowspeed
                nextUpdateAttack = (timeMillis()) + (1000 / 60) * game.timeAttackPlayer;
                updateEnemyProjectiles(gamemap, game);
            }
        }
        if (game.itemsInGame > 0) {
            // Atualiza os itens em uma taxa um pouco mais lenta para não sobrecarregar
            if (nextUpdateItems <= (timeMillis()))
            {
                nextUpdateItems = timeMillis() + 150; // Itens caem a cada 150ms
                UpdateItems(game, *player, player2, indexNick);
            }
        }
        if (nextUpdateHud <= (timeMillis()))
        {
            nextUpdateHud = timeMillis() + 300;
            hudPrint(game,indexNick);
        }
        

    } while ((game.player.health > 0 || player2.health > 0) && gameexit);
    
    //limpando entrada para não preencher sozinho o Nick
    cleanBuffer();
    showGameOverScreen(game,indexNick);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

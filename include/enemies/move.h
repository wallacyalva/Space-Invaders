#include <windows.h>
#include "../basicStructures/gameElements.h"
#include "../map/gameMap.h"
using namespace std;


//limpa inimigos antigos da tela e mapa
void limparInimigosAntigos(Game &game, Gamemap &gamemap){
    for (int i = 0; i < maxEnemies; i++){
        if (game.enemies[i].active){
            COORD pos = game.enemies[i].position;
            SetConsoleCursorPosition(hConsole, pos);
            cout << " ";
            gamemap.map[pos.Y][pos.X] = Gamemap::vazio;
        }

    }
}

// Desenha inimigos no console e atualiza mapa
void desenharInimigos(Game &game, Gamemap &gamemap){
    for (int i = 0; i < maxEnemies; i++){
        if (game.enemies[i].active){
            COORD pos = game.enemies[i].position;
    
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, Gamemap::vermelho);
            cout << types[GameElements::enemy];
            SetConsoleTextAttribute(hConsole, gamemap.themeColor);
    
            gamemap.map[pos.Y][pos.X] = Gamemap::inimigo;
        }

    }
}

// Movimenta os inimigos como no Space Invaders
void moveEnemies(Gamemap &gamemap, Game &game){

    // Verifica se deve descer
    bool shouldDescend = false;
    for (int i = 0; i < maxEnemies; i++){
        if (game.enemies[i].active){
            int nextX = game.enemies[i].position.X + enemyDirection;
            int y = game.enemies[i].position.Y;
    
            if (nextX <= 0 || nextX >= GameElements::columnMap - 1 || gamemap.map[y][nextX] == Gamemap::parede){
                shouldDescend = true;
                break;
            }
        }

    }

    // 2. Limpa posições antigas
    limparInimigosAntigos(game, gamemap);

    // 3. Move os inimigos
    for (int i = 0; i < maxEnemies; i++){
        if (game.enemies[i].active){
            if (shouldDescend){
                game.enemies[i].position.Y++;
            }else{
                game.enemies[i].position.X += enemyDirection;
            }
        }
    }

    // 4. Inverte direção caso tenha descido
    if (shouldDescend){
        enemyDirection *= -1;
    }

    // 5. Redesenha inimigos na nova posição
    desenharInimigos(game, gamemap);

    // 6. reinicia o contador 

    enemyMoveCounter = 0;
}

void updateEnemyProjectiles(Gamemap &gamemap, Game &game) {
    for (int i = 0; i < game.enemyProjectilesInGame; i++) {
        if (game.enemyProjectiles[i].active){
            COORD &pos = game.enemyProjectiles[i].position;
    
            // Apaga posição atual (mas só se não for o player)
            if (!(pos.X == game.player.position.X && pos.Y == game.player.position.Y)) {
                SetConsoleCursorPosition(hConsole, pos);
                cout << " ";
                gamemap.map[pos.Y][pos.X] = Gamemap::vazio;
            }
    
            // Move para baixo
            pos.Y += game.enemyProjectiles[i].speed;
    
            // Verifica se saiu da tela
            if (pos.Y >= GameElements::lineMap - 1) {
                game.enemyProjectiles[i].active = false;
                continue;
            }
    
            // Verifica colisão com barreira
            if (gamemap.map[pos.Y][pos.X] == Gamemap::barreira) {
                game.enemyProjectiles[i].active = false; // Desativa o projétil
                gamemap.map[pos.Y][pos.X] = Gamemap::vazio; // Destroi parte da barreira
                SetConsoleCursorPosition(hConsole, pos); // Limpa o caractere da barreira na tela
                cout << " ";
                continue; // Próximo projétil
            }

            // Verifica colisão com player
            if (pos.X == game.player.position.X && pos.Y == game.player.position.Y) {
                game.enemyProjectiles[i].active = false;
    
                if (game.player.health > 0) game.player.health--;
    
                // Reimprime o player no lugar do impacto
                SetConsoleCursorPosition(hConsole, game.player.position);
                SetConsoleTextAttribute(hConsole, game.player.color);
                cout << game.player.playerChar;
                SetConsoleTextAttribute(hConsole, gamemap.themeColor);
                continue;
            }
    
            // Atualiza novo local do projétil
            gamemap.map[pos.Y][pos.X] = Gamemap::ataqueInimigo;
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, Gamemap::rosa);
            cout << types[GameElements::enemyAttack];
            SetConsoleTextAttribute(hConsole, gamemap.themeColor);
        };

    }
}
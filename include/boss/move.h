#include <windows.h>
#include "../basicStructures/gameElements.h"
#include <iostream>
#include <conio.h>
using namespace std;


//limpa inimigos antigos da tela e mapa
void limparBossAntigo(Game &game, Gamemap &gamemap){
    for (int i = 0; i < maxEnemies; i++){
        if (game.boss.active){
            COORD pos = game.boss.position;
            SetConsoleCursorPosition(hConsole, pos);
            cout << " ";
            gamemap.map[pos.Y][pos.X] = Gamemap::vazio;
        }

    }
}

// Desenha inimigos no console e atualiza mapa
void desenharBoss(Game &game, Gamemap &gamemap){
    if(game.boss.active){
        SetConsoleCursorPosition(hConsole, game.boss.position);
        SetConsoleTextAttribute(hConsole, game.boss.color);
        cout << game.boss.appareance;
        SetConsoleTextAttribute(hConsole, gamemap.themeColor);
        gamemap.map[game.boss.position.Y][game.boss.position.X] = Gamemap::boss;
    }

}

// Movimenta os inimigos como no Space Invaders
void moveBoss(Gamemap &gamemap, Game &game){

    // Verifica se deve descer
    bool shouldDescend = false;
        if (game.boss.active){
            int nextX = game.boss.position.X + enemyDirection;
            int y = game.boss.position.Y;
    
            if (nextX <= 0 || nextX >= GameElements::columnMap - 1 || gamemap.map[y][nextX] == Gamemap::parede){
                shouldDescend = true;
            }
            if (shouldDescend){
                if(y > GameElements::lineMap - 3){
                    return;
                }}
            // 2. Limpa posições antigas
            limparBossAntigo(game, gamemap);

            // 3. Move os inimigos
                if (game.boss.active){
                    if (shouldDescend){
                game.boss.position.Y++;
            }else{
                game.boss.position.X += enemyDirection;
            }
        }

    // 4. Inverte direção caso tenha descido
    if (shouldDescend){
        enemyDirection *= -1;
    }
    
    // 5. Redesenha inimigos na nova posição
    desenharBoss(game, gamemap);
}
}

void updateBossProjectiles(Gamemap &gamemap, Game &game) {
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
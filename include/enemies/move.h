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
    enemyDelay = baseEnemyDelay - game.enemiesDie * 20;

    if (enemyMoveCounter < enemyDelay){
        enemyMoveCounter++;
        return;
    }

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

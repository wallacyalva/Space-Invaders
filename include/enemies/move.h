
#include <windows.h>
#include "../basicStructures/gameElements.h"
#include "../map/gameMap.h"
using namespace std;

int enemyDirection = 1; // 1 para direita, -1 para esquerda
int enemyMoveCounter = 0;
int baseEnemyDelay = 200;
int enemyDelay = baseEnemyDelay;

void moveEnemies(Gamemap &gamemap, Game &game) {
    if (enemyMoveCounter >= enemyDelay) {
        bool shouldDescend = false;

        // Checar se algum inimigo vai colidir com parede
        for (int i = 0; i < maxEnemies; i++) {
            if (game.enemies[i].active){
                int nextX = game.enemies[i].position.X + enemyDirection;
                int y = game.enemies[i].position.Y;
    
                if (nextX <= 0 || nextX >= GameElements::columnMap - 1 || gamemap.map[y][nextX] == Gamemap::parede) {
                    shouldDescend = true;
                    break;
                }
            }
        }

        // Apagar inimigos antigos
        for (int i = 0; i < maxEnemies; i++) {
            if (game.enemies[i].active){
                SetConsoleCursorPosition(hConsole, game.enemies[i].position);
                cout << " ";
            }
        }

        // Mover inimigos
        for (int i = 0; i < maxEnemies; i++) {
            if (game.enemies[i].active){
                if (shouldDescend) {
                    game.enemies[i].position.Y++;
                } else {
                    game.enemies[i].position.X += enemyDirection;
                }
            };
        }

        // Inverter direção se desceu
        if (shouldDescend) {
            enemyDirection *= -1;
        }

        // Redesenhar inimigos na nova posição
        for (int i = 0; i < maxEnemies; i++) {
            if (game.enemies[i].active){
                SetConsoleCursorPosition(hConsole, game.enemies[i].position);
                SetConsoleTextAttribute(hConsole, Gamemap::vermelho);
                cout << types[GameElements::enemy];
                SetConsoleTextAttribute(hConsole, gamemap.themeColor);
            }
        }

        // Aumentar velocidade conforme inimigos são derrotados
        int vivos = 0;
        for (int i = 0; i < maxEnemies; i++) {
            if (game.enemies[i].active){ 
                vivos++;
            }
        }

        enemyDelay = max(2, baseEnemyDelay - vivos / 5); // acelera com menos inimigos
        enemyMoveCounter = 0;
    } else {
        enemyMoveCounter++;
    }
}
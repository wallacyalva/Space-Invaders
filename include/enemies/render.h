#include <windows.h>
#include "../basicStructures/gameElements.h"
#include "../map/gameMap.h"
using namespace std;

// Responsável por renderizar os inimigos no mapa
void renderEnemy(int Template[GameElements::lineMap][GameElements::columnMap]){
    for (int i = 0; i < maxEnemies; i++){
        if(game.enemies[i].active){
            Template[game.enemies[i].position.Y][game.enemies[i].position.X] = GameElements::enemy;
        }
    }
}

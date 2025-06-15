#include <windows.h>
#include "../basicStructures/gameElements.h"
#include "../map/gameMap.h"
using namespace std;
int maxLines = 5;
int maxColuns = 10;

int findIndexActive(Game &game, int randN, int add = 0, int initialRandN = -1) {
    // Inicializa o valor original na primeira chamada
    if (initialRandN == -1) {
        initialRandN = randN;
    }

    // Passou de todas as colunas e voltou ao começo sem encontrar
    if (randN >= maxColuns) {
        // Reinicia a busca da coluna 0
        randN = 0;
    }

    // Caso retorne para a coluna inicial após procurar todas
    if (randN == initialRandN && add >= maxLines) {
        return -1;
    }

    // Passa para a próxima coluna
    if (add >= maxLines) {
        return findIndexActive(game, randN + 1, 0, initialRandN);
    }

    int myIndex = ((maxLines - 1 - add) * maxColuns) + randN;

    // Verifica se está dentro dos limites do array
    if (myIndex < 0 || myIndex >= maxEnemies) {
        // pula para próxima coluna
        return findIndexActive(game, randN + 1, 0, initialRandN); 
    }

    if (game.enemies[myIndex].active) {
        return myIndex;
    } else {
        // Sobe mais na mesma coluna
        return findIndexActive(game, randN, add + 1, initialRandN);
    }
}

void makeAttackEnemy(Gamemap &gamemap, Game &game){

    int randN = rand() % maxColuns;
    
    int myIndex = findIndexActive(game,randN);

    if(myIndex != -1){
        COORD pos = {game.enemies[myIndex].position.X,(game.enemies[myIndex].position.Y + 1)};

        if (game.enemyProjectilesInGame < maxEnemyProjectiles) {
            EnemyProjectile proj;
            proj.position = pos;

            game.enemyProjectiles[game.enemyProjectilesInGame++] = proj;
        }
    }

}
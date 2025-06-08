const int maxEnemies = 50;

struct GameElements
{
    char person = 'A';
    char enemy = 'W';
};

struct Enemy
{
    int x;
    int y;
    bool active = true;
};

Enemy Enemies[maxEnemies];
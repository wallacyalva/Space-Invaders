// const maxEnemies = 50;

struct GameElements
{
    char person = 'A';
    char enemy = 'W';
    static const int columnMap = 33;
    static const int lineMap = 23;
};

struct Enemy
{
    int x;
    int y;
    bool active = true;
};

// Enemies Enemy[maxEnemies]
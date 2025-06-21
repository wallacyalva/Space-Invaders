#include <iostream>
#include <fstream>
#include <sstream>
#include "../basicStructures/gameElements.h"
using namespace std;

int indexPoints = 0;
const char tabChar = '\t';
int readSave(Game &game)
{
    int indexNick = 0;
    ifstream fileSave("./gameSave.save");
    string line;
    string pastSession = "";
    string actualSession = "";
    enum valueType
    {
        Health,
        Damage,
        Shield,
        Position,
        Type,
        Quantity,
        Durability,
        Defense,
        Heal,
        Art,
        MidX,
        MidY,
        Description,
        seed,
        ReturnType,
        points,
        roomsMoved,
        Nick,
        inMap,
        Size
    };
    short int i = -1;
    if (fileSave.is_open())
    {
        Player player = game.player;
        while (getline(fileSave, line))
        {
            if (line == "[Space Invaders]") continue;
            pastSession = actualSession;
            if (line[0] == '[')
            {
                actualSession = line;
                continue;
            }
             if (actualSession == "[Player]")
            {
                cout << "Player Save" << endl;
                string value = "";
                stringstream valuesLine(line);
                bool isValue = false;
                valueType type;
                if (line != "[Player]")
                    while (getline(valuesLine, value, tabChar))
                    {
                        cout << value << endl;
                        if (isValue && type == valueType::Health)
                        {
                            player.health = stoi(value);
                            cout << player.health << " This is Life of Player";
                            isValue = false;
                        }
                        else if (isValue && type == valueType::Damage)
                        {
                            player.damage = stoi(value);
                            cout << player.damage << " This is Damage of Player";
                            isValue = false;
                        }
                        else if (isValue && type == valueType::Position)
                        {
                            player.position.X = stoi(value);
                            player.position.Y = stoi(value);
                        }
                        else if (isValue && type == valueType::Shield)
                        {
                            player.shield = stoi(value);
                        }
                        if (value == "Health")
                        {
                            isValue = true;
                            type = valueType::Health;
                        }
                        else if (value == "Position")
                        {
                            isValue = true;
                            type = valueType::Position;
                        }
                    };
                isValue = false;
            }
            else if (actualSession == "[Points]")
            {
                valueType type;
                bool isValue = false;
                string value = "";

                stringstream valuesLine(line);
                while (getline(valuesLine, value, tabChar))
                {
                    if (isValue)
                    {
                        switch (type)
                        {
                        case valueType::points:
                            game.score[indexPoints++] = stoi(value);
                            break;

                        case valueType::Nick:
                            for (int i = 0; i < 3; i++)
                            {
                                if (i < value.size())
                                    game.nick[indexNick].nick[i] = value[i];
                                else
                                    game.nick[indexNick].nick[i] = '\0';
                            }
                            indexNick++;
                            break;

                        default:
                            break;
                        }
                        isValue = false; // resetar para não processar valores indevidos
                    }

                    if (value == "Points")
                    {
                        isValue = true;
                        type = valueType::points;
                    }
                    else if (value == "Nick")
                    {
                        isValue = true;
                        type = valueType::Nick;
                    }
                }
            }

            cout << endl
            << player.position.X << "," << player.position.Y << endl;
        }
        game.player = player;
        fileSave.close();
    }
    return indexNick;
}

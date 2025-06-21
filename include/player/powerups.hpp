#pragma once
#include <windows.h>
#include <iostream>
#include "../basicStructures/gameElements.h"

// Adiciona um novo item ao jogo
void CreateItem(Game &game, Items::TypeofItems type, COORD position) {
    if (game.itemsInGame >= maxItems) {
        return; // Limite de itens na tela
    }

    int index = -1;
    for (int i = 0; i < maxItems; ++i) {
        if (!game.activeItems[i].active) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        game.itemsInGame++;
        Items &item = game.activeItems[index];
        item.active = true;
        item.type = type;
        item.position = position;

        switch (type) {
            case Items::ExtraLife:
                item.itemAppearance = '+'; // Coração já é usado para vida
                item.color = FOREGROUND_RED | FOREGROUND_INTENSITY;
                break;
            case Items::SpeedBoost:
                item.itemAppearance = '>';
                item.color = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                break;
            case Items::ExtraShots:
                item.itemAppearance = '^';
                item.color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                break;
            case Items::MultiShot:
                item.itemAppearance = 'W';
                item.color = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY; // Amarelo
                break;
            case Items::ExtraPoints:
                item.itemAppearance = '$';
                item.color = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY; // Amarelo
                break;
            case Items::FreezeEnemies:
                item.itemAppearance = '*';
                item.color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY; // Ciano
                break;
            default:
                item.active = false; // Tipo desconhecido
                game.itemsInGame--;
                break;
        }
    }
}

// Aplica o efeito do power-up ao jogador
void ApplyPowerUp(Game &game, Items::TypeofItems type, int indexNick) {
    Beep(2000, 50); // Som de coleta
    switch (type) {
        case Items::ExtraLife:
            if (game.player.health < game.player.maxhealth) game.player.health++;
            break;
        case Items::SpeedBoost:
            game.player.speedBoostEndTime = timeMillis() + 8000;
            break;
        case Items::ExtraShots:
            game.player.extraShotsEndTime = timeMillis() + 6000;
            break;
        case Items::MultiShot:
            game.player.multiShotEndTime = timeMillis() + 5000;
            break;
        case Items::ExtraPoints:
            game.score[indexNick] += 50;
            break;
        case Items::FreezeEnemies:
            game.freezeEnemiesEndTime = timeMillis() + 2000;
            break;
        default:
            break;
    }
}

// Atualiza a posição e o estado dos itens na tela
void UpdateItems(Game &game, int indexNick) {
    for (int i = 0; i < maxItems; ++i) {
        if (game.activeItems[i].active) {
            Items &item = game.activeItems[i];

            // Apaga a posição antiga
            SetConsoleCursorPosition(hConsole, item.position);
            cout << " ";

            // Move para baixo
            item.position.Y++;

            // Verifica colisão com o jogador
            if (item.position.X == game.player.position.X && item.position.Y == game.player.position.Y) {
                ApplyPowerUp(game, item.type, indexNick);
                item.active = false;
                game.itemsInGame--;
            }
            // Verifica se saiu da tela
            else if (item.position.Y >= GameElements::lineMap - 1) {
                item.active = false;
                game.itemsInGame--;
            }
            // Se ainda estiver na tela, desenha na nova posição
            else {
                SetConsoleCursorPosition(hConsole, item.position);
                SetConsoleTextAttribute(hConsole, item.color);
                cout << item.itemAppearance;
                SetConsoleTextAttribute(hConsole, (0 << 4) | 7); // Reseta para cor padrão
            }
        }
    }
}
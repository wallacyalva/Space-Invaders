#ifndef gameMap_h
#define gameMap_h
#include <windows.h>
#include "../basicStructures/gameElements.h"
using namespace std;

// Toda a criação do tipo map
struct Gamemap
{
    // Tamanho máximo do mapa e outras funções sobre
    int map[GameElements::lineMap][GameElements::columnMap] = {};
    enum mapSpawnPositions
    {
        top,
        bottom,
        left,
        right,
    };
    // Todas as coisas usadas na criação do mapa
    enum entities
    {
        floor = 0,
        parede = 1,
        inimigo = 3,
        vazio = 9,
    };
    entities entity;
    static const DWORD padrao = (0 << 4) | 7;    /* Define o mapa para printar fundo preto e escrita branca */
    static const DWORD branco = (0 << 4) | 15;   /* Define o mapa para printar fundo preto e escrita branca */
    static const DWORD amarelo = (0 << 4) | 14;  /* Define o mapa para printar fundo preto e escrita amarela */
    static const DWORD azul = (0 << 4) | 9;      /* Define o mapa para printar fundo preto e escrita azul */
    static const DWORD vermelho = (0 << 4) | 12; /* Define o mapa para printar fundo preto e escrita vermelha */
    DWORD themeColor = padrao;                   /* Define para começar na cor padrão */
};
#endif
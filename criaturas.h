#ifndef CRIATURAS
#define CRIATURAS

#include "raylib.h"
#include "player.h"

typedef struct
{
    int vida, dano, armadura;
    double velocidade;
    Rectangle colisao;

} mob;

void criarCriatura(mob *criatura, double posX, double posY);

void moverCriatura(mob *criatura, int posX, int posY);

void atingiuOPlayer(mob *criatura, nerdola *player);

void criarWave(int wave, int *qtdCriaturasVivas, mob **criaturas);

int acertouACriatura(bala *projetil, mob **Criaturas, int wave);

#endif
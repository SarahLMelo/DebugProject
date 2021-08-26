#ifndef CRIATURAS
#define CRIATURAS

#include "raylib.h"
#include "player.h"
#include "armas.h"

typedef struct
{
    int vida, dano, armadura;
    double velocidade;
    Rectangle colisao;

} mob;

void criarCriatura(mob *criatura, double posX, double posY);

int bateuNaParede(Rectangle *grid, mob criatura, int quantidadeDeParedes);

void moverCriatura(mob *criatura, int posX, int posY, Rectangle *grid, int quantidadeDeParedes);

void atingiuOPlayer(mob *criatura, nerdola *player);

void criarWave(int wave, int *qtdCriaturasVivas, mob **criaturas, int w, int h);

int acertouACriatura(bala *projetil, mob **Criaturas, int wave, int *pontuacao);

#endif
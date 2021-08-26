#ifndef ARMAS
#define ARMAS

#include "player.h"
#include "armas.h"
#include "raylib.h"

typedef struct
{
    int viva, dano;
    double velocidade, x, y;
    Rectangle colisao;
} bala;

bala atirarComTeclado(int key1, int key2, nerdola jogador, Sound som, int armaAtiva);

bala atirarComMouse(float xMira, float yMira, nerdola jogador, Sound som, int armaAtiva);

Vector2 circleMira(Vector2 coord, Vector2 p);

int bateuNaParedeP(Rectangle *grid, bala projetil);

void movimentarProjetil(bala *projetil, Rectangle *grid);

#endif

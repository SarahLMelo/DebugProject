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
    float angulo;

} bala;

bala atirarComTeclado(int key1, int key2, nerdola jogador, Sound som, int armaAtiva);

bala atirarComMouse(float xMira, float yMira, nerdola jogador, Sound som, int armaAtiva);

Vector2 circleMira(Vector2 coord, Vector2 p);

void movimentarProjetil(bala *projetil, Texture2D balaAnimation);

#endif

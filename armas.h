#ifndef ARMAS
#define ARMAS

#include "raylib.h"

typedef struct
{
    float dano, velocidade;
    char[40] nome;
} arma;

typedef struct
{
    int viva, dano, x, y;
    double velocidade;
    Rectangle colisao;
} bala;

void inicializaArma(modelo *arma);

bala atirar(int key1, int key2, nerdola jogador);

void destruirProjetil(bala **vetor, int *tamanho);

void movimentarProjetil(bala *projetil);

#endif ARMAS

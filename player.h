#ifndef PLAYER
#define PLAYER

#include "raylib.h"

typedef struct{
    int vida, armadura, dano; //O dano é o indicador de qual arma ele está utilizando
    double velocidade;
    Rectangle colisao;

} nerdola;

typedef struct{
    int dano, tempo, x, y;
    double velocidade;
    Rectangle colisao;
} bala;

void inicializaPlayer(nerdola *jogador);

void movimentarPlayer(nerdola *jogador);

bala atirar(int key1, int key2, nerdola jogador);

void playerEstaAtirando(bala **vetor, nerdola jogador, int *tamanho);

void destruirProjetil(bala **vetor, int *tamanho);

void movimentarProjetil(bala *projetil);

#endif PLAYER
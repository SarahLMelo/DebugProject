#ifndef PLAYER
#define PLAYER

#include "raylib.h"

typedef struct
{
    int vida, armadura, dano; //O dano é o indicador de qual arma ele está utilizando
    double velocidade;
    Rectangle colisao;

} nerdola;

typedef struct
{
    int viva, dano;
    double velocidade, x, y;
    Rectangle colisao;
} bala;

void inicializaPlayer(nerdola *jogador);

int acertouAParede(nerdola jogador, Rectangle *grid, int quantidadeDeParedes);

void movimentarPlayer(nerdola *jogador, Rectangle *grid, int quantidadeDeParedes);

bala atirar(int key1, int key2, nerdola jogador, Sound som);

bala atirarComMouse(float xMira, float yMira, nerdola jogador, Sound som);

Vector2 circleMira(Vector2 coord, Vector2 p);

void playerEstaAtirando(bala *vetor, nerdola jogador, int *tamanho, Sound tiro, Vector2 cameraTarget);

void destruirProjetil(bala **vetor, int *tamanho);

void movimentarProjetil(bala *projetil);

#endif
#ifndef PLAYER
#define PLAYER

#include "raylib.h"

typedef struct
{
    int vida, armadura; //O dano é o indicador de qual arma ele está utilizando
    double velocidade;
    Rectangle colisao;
    Vector2 posicaoNerdola;

} nerdola;

void inicializaPlayer(nerdola *jogador);

int acertouAParede(nerdola jogador, Rectangle *grid, int quantidadeDeParedes);

int movimentarPlayer(nerdola *jogador, Rectangle *grid, int quantidadeDeParedes);

void playerEstaAtirando(bala *vetor, nerdola jogador, int *tamanho, Sound tiro, Vector2 cameraTarget, int armaAtiva, int modRifle, int modPistola);

#endif
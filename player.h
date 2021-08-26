#ifndef PLAYER
#define PLAYER

#include "raylib.h"

typedef struct
{
    int vida, armadura; //O dano é o indicador de qual arma ele está utilizando
    double velocidade;
    Rectangle colisao;

} nerdola;

void inicializaPlayer(nerdola *jogador);

int acertouAParede(nerdola jogador, Rectangle *grid, int quantidadeDeParedes);

void movimentarPlayer(nerdola *jogador, Rectangle *grid, int quantidadeDeParedes);


#endif
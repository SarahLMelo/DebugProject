#include "raylib.h"

typedef struct{
    int vida, armadura;
    double velocidade;
    Rectangle colisao;

} nerdola;

void inicializaPlayer(nerdola *jogador);

void movimentarPlayer(nerdola *jogador);
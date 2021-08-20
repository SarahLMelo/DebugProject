#include "raylib.h"

typedef struct{
    int vida, dano, armadura;
    double velocidade;
    Rectangle colisao;

} mob;

void criarCriatura(mob *criatura, double posX, double posY);

void moverCriatura(mob *criatura, int posX, int posY);
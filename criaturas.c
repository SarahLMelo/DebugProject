#include "criaturas.h"
#include "raylib.h"
#include <stdlib.h>
#include <math.h>

#define SPEED_N 10

void criarCriatura(mob *criatura, double posX, double posY){
    //Status básicos da criatura
    (*criatura).armadura = 5;
    (*criatura).vida =10;
    (*criatura).dano =1;
    (*criatura).velocidade =10;

    //Criando o retangulo de colusão
    (*criatura).colisao.height = 50;
    (*criatura).colisao.width = 50;
    (*criatura).colisao.x = posX;
    (*criatura).colisao.y = posY;

    return;
}

void moverCriatura(mob *criatura, int posX, int posY){
    //posição do player
    double playerX = (double) posX, playerY = (double) posY;

    double angulo = atan2(playerX-(*criatura).colisao.x, playerY-(*criatura).colisao.y); //angulação da reta entre o player e o mob

    //alterando posição do mob
    (*criatura).colisao.y += (int)(cos(angulo)*(*criatura).velocidade);
    (*criatura).colisao.x += (int)(sin(angulo)*(*criatura).velocidade);

    return;
}
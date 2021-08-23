#include "criaturas.h"
#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include "player.h"

void criarCriatura(mob *criatura, double posX, double posY){
    //Status básicos da criatura
    (*criatura).armadura = 5;
    (*criatura).vida =10;
    (*criatura).dano =1;
    (*criatura).velocidade =5;

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

void atingiuOPlayer(mob *criatura, nerdola *player){
    if(CheckCollisionRecs((*criatura).colisao, (*player).colisao)){
        (*player).vida -= ((*criatura).dano - (*player).armadura);
    }

    return;
}

void criarWave(int wave, int *qtdCriaturasVivas, mob **criaturas){
    (*criaturas) = (mob*) realloc((*criaturas), sizeof(mob)*wave);

    for(int i=0; i<wave; i++){
        int x, y;
        x = rand()%1700;
        y = rand()%800;
        criarCriatura((*criaturas)+i, x, y);
    }

    //(*qtdCriaturasVivas) = wave;

    return;
}

int acertouACriatura(bala *projetil, mob **Criaturas, int wave){
    int achouAlguem = 0;
    for(int i=0; i<wave && achouAlguem == 0; i++){
        if((*Criaturas)[i].vida <= 0) continue;
        else if(CheckCollisionRecs((*projetil).colisao, (*Criaturas)[i].colisao) == true){
            achouAlguem = 1;
            (*projetil).viva = 0;
            (*Criaturas)[i].vida -= (*projetil).dano;
        }
    }

    return achouAlguem;
}
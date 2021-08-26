#include "criaturas.h"
#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include "player.h"
#include "armas.h"
#include "mapa.h"
//pedro passou aqui

void criarCriatura(mob *criatura, double posX, double posY)
{
    //Status básicos da criatura
    (*criatura).armadura = 5;
    (*criatura).vida =80;
    (*criatura).dano =1;
    (*criatura).velocidade =5;

    //Criando o retangulo de colusão
    (*criatura).colisao.height = 50;
    (*criatura).colisao.width = 50;
    (*criatura).colisao.x = posX;
    (*criatura).colisao.y = posY;

    return;
}

int bateuNaParede(Rectangle *grid, mob criatura, int quantidadeDeParedes){
    int bateu = 0;
    for(int i=0; i<quantidadeDeParedes && bateu == 0; i++){
        if(CheckCollisionRecs(criatura.colisao, grid[i])) bateu = 1;
    }
    return bateu;
}

void moverCriatura(mob *criatura, int posX, int posY, Rectangle *grid, int quantidadeDeParedes)
{
    //posição do player
    double playerX = (double)posX, playerY = (double)posY;

    double angulo = atan2(playerY - (*criatura).colisao.y, playerX - (*criatura).colisao.x); //angulação da reta entre o player e o mob

    //alterando posição do mob
    (*criatura).colisao.x += (int)(cos(angulo) * (*criatura).velocidade);
    (*criatura).colisao.y += (int)(sin(angulo) * (*criatura).velocidade);
    if(bateuNaParede(grid, (*criatura), quantidadeDeParedes) == 1){
        (*criatura).colisao.x -= (int)(cos(angulo) * (*criatura).velocidade);
        (*criatura).colisao.y -= (int)(sin(angulo) * (*criatura).velocidade);

        //Primeiro quadrante
        if(angulo>0 && angulo<(PI/2)){
            (*criatura).colisao.x += (*criatura).velocidade; //mover para a direita
            if(bateuNaParede(grid, (*criatura), quantidadeDeParedes) == 1){
                (*criatura).colisao.x -= (*criatura).velocidade; //desfaz
                (*criatura).colisao.y += (*criatura).velocidade;//move para cima
                 if(bateuNaParede(grid, (*criatura), quantidadeDeParedes) == 1) (*criatura).colisao.y -= (*criatura).velocidade;//desfaz e fica parado esperando
            }
        }
        //Segundo quadrante
        if(angulo>(PI/2)){
            (*criatura).colisao.x -= (*criatura).velocidade; //mover para a esquerda
            if(bateuNaParede(grid, (*criatura), quantidadeDeParedes) == 1){
                (*criatura).colisao.x += (*criatura).velocidade; //desfaz
                (*criatura).colisao.y += (*criatura).velocidade;//move para cima
                 if(bateuNaParede(grid, (*criatura), quantidadeDeParedes) == 1) (*criatura).colisao.y -= (*criatura).velocidade;//desfaz e fica parado esperando
            }
        }
        //Terceiro quadrante
        if(angulo<(-PI/2)){
            (*criatura).colisao.x -= (*criatura).velocidade; //mover para a esquerda
            if(bateuNaParede(grid, (*criatura), quantidadeDeParedes) == 1){
                (*criatura).colisao.x += (*criatura).velocidade; //desfaz
                (*criatura).colisao.y -= (*criatura).velocidade;//move para baixo
                 if(bateuNaParede(grid, (*criatura), quantidadeDeParedes) == 1) (*criatura).colisao.y += (*criatura).velocidade;//desfaz e fica parado esperando
            }
            
        }
        //Quarto quadrante
        if(angulo<0 && angulo>(-PI/2)){
            (*criatura).colisao.x += (*criatura).velocidade; //mover para a direita
            if(bateuNaParede(grid, (*criatura), quantidadeDeParedes) == 1){
                (*criatura).colisao.x -= (*criatura).velocidade; //desfaz
                (*criatura).colisao.y -= (*criatura).velocidade;//move para baixo
                 if(bateuNaParede(grid, (*criatura), quantidadeDeParedes) == 1) (*criatura).colisao.y += (*criatura).velocidade;//desfaz e fica parado esperando
            }
        }
    }

    return;
}

void atingiuOPlayer(mob *criatura, nerdola *player)
{
    if (CheckCollisionRecs((*criatura).colisao, (*player).colisao))
    {
        (*player).vida -= ((*criatura).dano - (*player).armadura);
    }

    return;
}

void criarWave(int wave, int *qtdCriaturasVivas, mob **criaturas, int w, int h){
    (*criaturas) = (mob*) malloc(sizeof(mob)*wave);
    for(int i=0; i<wave; i++){
        int x, y, sIndex;
        if(i>7) sIndex = i %7;
        else sIndex = i;
        // x = rand()%1700;
        // y = rand()%800;
        Vector2 localizacao = spawnPoints(sIndex, w, h);
        criarCriatura((*criaturas)+i, localizacao.x , localizacao.y);
    }

    //(*qtdCriaturasVivas) = wave;

    return;
}

int acertouACriatura(bala *projetil, mob **Criaturas, int wave){
    int achouAlguem = 0, matouACriatura = 0;
    for(int i=0; i<wave && achouAlguem == 0; i++){
        if((*Criaturas)[i].vida <= 0) continue;
        else if(CheckCollisionRecs((*projetil).colisao, (*Criaturas)[i].colisao) == true){
            achouAlguem = 1;
            (*projetil).viva = 0;
            (*Criaturas)[i].vida -= (*projetil).dano;
            if((*Criaturas)[i].vida<=0) matouACriatura = 1;
        }
    }

    return matouACriatura;
}
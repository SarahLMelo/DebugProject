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
    //Setando animação da criatura
    (*criatura).anima.morreu = 0;
    (*criatura).anima.quantFrames = 2;
    (*criatura).anima.frameCounter = 0;
    (*criatura).anima.frameSpeed = 12;
    (*criatura).anima.currentFrame = 0;
    (*criatura).anima.flagAnimMorte = 0;
    (*criatura).anima.oldposition = (Vector2) {posX*1.0f, posY*1.0f};
    (*criatura).anima.position = (Vector2) {posX*1.0f, posY*1.0f};

    //Setando animcao da morte
    (*criatura).animaMorte.quantFrames = 9;
    (*criatura).animaMorte.frameCounter = 0;
    (*criatura).animaMorte.frameSpeed = 12;
    (*criatura).animaMorte.currentFrame = 0;
    (*criatura).animaMorte.flagAnimMorte = 0;
    (*criatura).animaMorte.morreu = 0;
    (*criatura).anima.position = (Vector2) {posX*1.0f, posY*1.0f};

    //Status básicos da criatura
    (*criatura).armadura = 5;
    (*criatura).vida =80;
    (*criatura).dano =1;
    (*criatura).velocidade =5;
    (*criatura).alguemJaChocou = 0;

    //Criando o retangulo de colisão
    (*criatura).colisao.height = 50;
    (*criatura).colisao.width = 50;
    (*criatura).colisao.x = posX;
    (*criatura).colisao.y = posY;

    //Criando o retangulo de colisão entre elas
    (*criatura).pequenaColisao.height = 25;
    (*criatura).pequenaColisao.width = 25;
    (*criatura).pequenaColisao.x = posX;
    (*criatura).pequenaColisao.y = posY;

    return;
}

int bateuNaParede(Rectangle *grid, mob criatura, int quantidadeDeParedes){
    int bateu = 0;
    for(int i=0; i<quantidadeDeParedes && bateu == 0; i++){
        if(CheckCollisionRecs(criatura.colisao, grid[i])) bateu = 1;
    }
    return bateu;
}

int bateuEmOutraCriatura(mob criatura, int i, mob **vetorCriatura, int wave){
    if(criatura.alguemJaChocou == 1) return 1;
    for(int j = i+1; j<wave; j++){
        if((*vetorCriatura)[j].vida>0){
            if(CheckCollisionRecs(criatura.pequenaColisao, (*vetorCriatura)[j].pequenaColisao)) (*vetorCriatura)[j].alguemJaChocou = 1;
        }
    }

    return 0;
}

void moverCriatura(mob **criatura, int posX, int posY, Rectangle *grid, int quantidadeDeParedes, int wave)
{
    //posição do player
    double playerX = (double)posX, playerY = (double)posY;

    for(int i=0; i<wave; i++){
        if((*criatura)[i].vida<=0) continue;
        double angulo = atan2(playerY - (*criatura)[i].colisao.y, playerX - (*criatura)[i].colisao.x); //angulação da reta entre o player e o mob

        //alterando posição do mob
        (*criatura)[i].colisao.x += (int)(cos(angulo) *(*criatura)[i].velocidade);
       (*criatura)[i].colisao.y += (int)(sin(angulo) *(*criatura)[i].velocidade);
        if(bateuNaParede(grid,(*criatura)[i], quantidadeDeParedes) == 1 || bateuEmOutraCriatura((*criatura)[i], i ,criatura, wave) == 1){
           (*criatura)[i].colisao.x -= (int)(cos(angulo) *(*criatura)[i].velocidade);
           (*criatura)[i].colisao.y -= (int)(sin(angulo) *(*criatura)[i].velocidade);

            //Primeiro quadrante
            if(angulo>0 && angulo<(PI/2)){
               (*criatura)[i].colisao.x +=(*criatura)[i].velocidade; //mover para a direita
                if(bateuNaParede(grid,(*criatura)[i], quantidadeDeParedes) == 1 || bateuEmOutraCriatura((*criatura)[i], i ,criatura, wave) == 1){
                   (*criatura)[i].colisao.x -=(*criatura)[i].velocidade; //desfaz
                   (*criatura)[i].colisao.y +=(*criatura)[i].velocidade;//move para cima
                    if(bateuNaParede(grid,(*criatura)[i], quantidadeDeParedes) == 1 || bateuEmOutraCriatura((*criatura)[i], i ,criatura, wave) == 1)(*criatura)[i].colisao.y -=(*criatura)[i].velocidade;//desfaz e fica parado esperando
                }
            }
            //Segundo quadrante
            if(angulo>(PI/2)){
               (*criatura)[i].colisao.x -=(*criatura)[i].velocidade; //mover para a esquerda
                if(bateuNaParede(grid,(*criatura)[i], quantidadeDeParedes) == 1 || bateuEmOutraCriatura((*criatura)[i], i ,criatura, wave) == 1){
                   (*criatura)[i].colisao.x +=(*criatura)[i].velocidade; //desfaz
                   (*criatura)[i].colisao.y +=(*criatura)[i].velocidade;//move para cima
                    if(bateuNaParede(grid,(*criatura)[i], quantidadeDeParedes) == 1  || bateuEmOutraCriatura((*criatura)[i], i ,criatura, wave) == 1)(*criatura)[i].colisao.y -=(*criatura)[i].velocidade;//desfaz e fica parado esperando
                }
            }
            //Terceiro quadrante
            if(angulo<(-PI/2)){
               (*criatura)[i].colisao.x -=(*criatura)[i].velocidade; //mover para a esquerda
                if(bateuNaParede(grid,(*criatura)[i], quantidadeDeParedes) == 1 || bateuEmOutraCriatura((*criatura)[i], i ,criatura, wave) == 1){
                   (*criatura)[i].colisao.x +=(*criatura)[i].velocidade; //desfaz
                   (*criatura)[i].colisao.y -=(*criatura)[i].velocidade;//move para baixo
                    if(bateuNaParede(grid,(*criatura)[i], quantidadeDeParedes) == 1|| bateuEmOutraCriatura((*criatura)[i], i ,criatura, wave) == 1)(*criatura)[i].colisao.y +=(*criatura)[i].velocidade;//desfaz e fica parado esperando
                }
                
            }
            //Quarto quadrante
            if(angulo<0 && angulo>(-PI/2)){
               (*criatura)[i].colisao.x +=(*criatura)[i].velocidade; //mover para a direita
                if(bateuNaParede(grid,(*criatura)[i], quantidadeDeParedes) == 1|| bateuEmOutraCriatura((*criatura)[i], i ,criatura, wave) == 1){
                   (*criatura)[i].colisao.x -=(*criatura)[i].velocidade; //desfaz
                   (*criatura)[i].colisao.y -=(*criatura)[i].velocidade;//move para baixo
                    if(bateuNaParede(grid,(*criatura)[i], quantidadeDeParedes) == 1|| bateuEmOutraCriatura((*criatura)[i], i ,criatura, wave) == 1)(*criatura)[i].colisao.y +=(*criatura)[i].velocidade;//desfaz e fica parado esperando
                }
            }
        }
    }
    for(int i=0; i<wave; i++) (*criatura)[i].alguemJaChocou = 0;

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
        sIndex = i % 7;
        // x = rand()%1700;
        // y = rand()%800;
        Vector2 localizacao = spawnPoints(sIndex, w, h);
        criarCriatura((*criaturas)+i, localizacao.x , localizacao.y);
    }

    //(*qtdCriaturasVivas) = wave;

    return;
}

int acertouACriatura(bala *projetil, mob **Criaturas, int wave, int *pontuacao){
    int achouAlguem = 0, matouACriatura = 0;
    for(int i=0; i<wave && achouAlguem == 0; i++){
        if((*Criaturas)[i].vida <= 0) continue;
        else if(CheckCollisionRecs((*projetil).colisao, (*Criaturas)[i].colisao) == true){
            achouAlguem = 1;
            (*projetil).viva = 0;
            (*Criaturas)[i].vida -= (*projetil).dano;
            if((*Criaturas)[i].vida<=0){
                matouACriatura = 1;
                (*Criaturas)[i].animaMorte.morreu = 1;
                (*pontuacao)++;
            }
        }
    }

    return matouACriatura;
}
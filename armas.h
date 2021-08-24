#ifndef ARMAS
#define ARMAS

#include "raylib.h"
#include "player.h"

//DEFINIR ARMAS
//ARMAS MAIORES TIPO 1
//ARMAS MENORES TIPO 2
//Pistola
#define ARMA_PISTOLA_ID 337
#define ARMA_PISTOLA_TIPO 2
#define ARMA_PISTOLA_NOME "Pistola"
#define ARMA_PISTOLA_QTDBALA 24
#define ARMA_PISTOLA_DANO 23
#define ARMA_PISTOLA_ASSET assets/pistola.png
//Rifle
#define ARMA_RIFLE_ID 338
#define ARMA_RIFLE_TIPO 1
#define ARMA_RIFLE_NOME "Rifle"
#define ARMA_RIFLE_QTDBALA 48
#define ARMA_RIFLE_DANO 36     
#define ARMA_RIFLE_ASSET assets/rifle.png

typedef struct{
    
    char nome[20];
    int qtdBala;
    int dano;
    int qtdPente;
    bala balas[50];
    int balasgastas;

} arma_;

typedef struct
{
    int viva, dano, x, y;
    double velocidade;
    Rectangle colisao;

} bala;

bala atirar(int key1, int key2, nerdola jogador);

void destruirProjetil(bala **vetor, int *tamanho);

void movimentarProjetil(bala *projetil);

#endif ARMAS

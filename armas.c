#include "raylib.h"
#include "armas.h"
#include "player.h"
#include <math.h>


#define danoRifle 40
#define danoPistola 20
#define miraRadius 100

void InitAudioDevice(void);

bala atirarComTeclado(int key1, int key2, nerdola jogador, Sound som, int armaAtiva)
{
    //Som do projetil
    PlaySound(som);

    //Inicializando projetil
    bala projetil;
    projetil.velocidade = 20;
    projetil.x = 0;
    projetil.y = 0;
    projetil.viva = 1;

    if(armaAtiva==1)  projetil.dano = danoRifle;
    else if(armaAtiva==2) projetil.dano = danoPistola;

    //Criando caixa de colisão
    projetil.colisao.height = 10;
    projetil.colisao.width = 10;
    projetil.colisao.x = jogador.colisao.x;
    projetil.colisao.y = jogador.colisao.y;

    //Criando direção
    if (key1 == KEY_UP)
        projetil.y = -1;
    if (key1 == KEY_LEFT)
        projetil.x = -1;
    if (key1 == KEY_DOWN)
        projetil.y = 1;
    if (key1 == KEY_RIGHT)
        projetil.x = 1;

    if (key2 != 0)
        projetil.velocidade /= sqrt(2);
    if (key2 == KEY_UP)
        projetil.y = -1;
    if (key2 == KEY_LEFT)
        projetil.x = -1;
    if (key2 == KEY_DOWN)
        projetil.y = 1;
    if (key2 == KEY_RIGHT)
        projetil.x = 1;

    return projetil;
}

bala atirarComMouse(float xMira, float yMira, nerdola jogador, Sound som, int armaAtiva)
{
    //Som do projetil
    PlaySound(som);

    //Inicializando projetil
    bala projetil;
    double angulo = atan2(jogador.colisao.x - xMira, jogador.colisao.y - yMira);
    projetil.frameCounter = 0;
    projetil.velocidade = 20;
    projetil.x = -sin(angulo);
    projetil.y = -cos(angulo);
    projetil.viva = 1;
    projetil.angulo = -90+angulo*57.2f;
    if(armaAtiva==1) projetil.dano = danoRifle;
    if(armaAtiva==2) projetil.dano = danoPistola;

    //Criando caixa de colisão
    projetil.colisao.height = 10;
    projetil.colisao.width = 10;
    projetil.colisao.x = jogador.colisao.x;
    projetil.colisao.y = jogador.colisao.y;

    return projetil;
}

Vector2 circleMira(Vector2 coord, Vector2 p){
    Vector2 newCoord;

    const double angulo = atan2(coord.x - p.x, coord.y - p.y);
    
    newCoord.x = p.x + miraRadius * sin(angulo);
    newCoord.y = p.y + miraRadius * cos(angulo);
    return newCoord;
}

int bateuNaParedeP(Rectangle *grid, bala projetil){
    int bateu = 0;
    for(int i=0; i<4 && bateu == 0; i++){
        if(CheckCollisionRecs(projetil.colisao, grid[i])) bateu = 1;
    }
    for(int i=10; i<20 && bateu == 0; i++){
        if(CheckCollisionRecs(projetil.colisao, grid[i])) bateu = 1;
    }
    for(int i=26; i<30 && bateu == 0; i++){
        if(CheckCollisionRecs(projetil.colisao, grid[i])) bateu = 1;
    }
    for(int i=41; i<44 && bateu == 0; i++){
        if(CheckCollisionRecs(projetil.colisao, grid[i])) bateu = 1;
    }

    return bateu;
}

void movimentarProjetil(bala *projetil, Rectangle *grid){
    (*projetil).colisao.x += (int)(*projetil).velocidade * (*projetil).x;
    (*projetil).colisao.y += (int)(*projetil).velocidade * (*projetil).y;

    if(bateuNaParedeP(grid, (*projetil)) == 1) (*projetil).viva = 0;

    return;
}

void recarregarArmas(bala (*armaPrincipal)[], bala (*armaSecundaria)[], int qntdMaxP, int qntdMaxS, int *balasGastasPrincipal, int *balasGastasSec){
    (*balasGastasPrincipal) = 0;
    (*balasGastasSec) = 0;
    for(int i=0; i<qntdMaxP; i++){
        (*armaPrincipal)[i].viva = 0;
    }
    for(int i=0; i<qntdMaxS; i++){
        (*armaSecundaria)[i].viva = 0;
    }

    return;
}

void CloseAudioDevice(void);
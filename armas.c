#include "raylib.h"
#include "armas.h"
#include "player.h"
#include <math.h>


#define danoRifle 40
#define danoPistola 20
#define miraRadius 120

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
    //Inicializando projetil
    bala projetil;
    //Som do projetil
    PlaySound(som);

    
    double angulo = atan2(jogador.colisao.x - xMira, jogador.colisao.y - yMira);

    projetil.velocidade = 90;
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

void movimentarProjetil(bala *projetil, Texture2D balaAnimation){
    (*projetil).colisao.x += (int)(*projetil).velocidade * (*projetil).x;
    (*projetil).colisao.y += (int)(*projetil).velocidade * (*projetil).y;
    Rectangle frameBala = { 0.0f, 0.0f,(float) balaAnimation.width/4, (float) balaAnimation.height };
    Rectangle frameBalaDest = { (*projetil).colisao.x+15, (*projetil).colisao.y+15, (float) balaAnimation.width/4, (float) balaAnimation.height};
    DrawTexturePro(balaAnimation, frameBala, frameBalaDest, (Vector2) { (float) 0*balaAnimation.width, (float) 0*balaAnimation.height }, 180-(*projetil).angulo, WHITE);  
    if((*projetil).viva = 0) UnloadTexture(balaAnimation);
}

void CloseAudioDevice(void);
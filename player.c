#include "raylib.h"
#include "player.h"
#include <math.h>
#include <stdlib.h>

void inicializaPlayer(nerdola *jogador){
    //Inicializa o player assim que abrir o jogo
    (*jogador).colisao.x = 900;
    (*jogador).colisao.y = 450;
    (*jogador).vida = 50;
    (*jogador).armadura = 0;
    (*jogador).velocidade = 15;

    //Dimensão da hitbox
    (*jogador).colisao.height = 30;
    (*jogador).colisao.width = 30;

    return;
}

void movimentarPlayer(nerdola *jogador){
    //Movimentar para cima
    if(IsKeyDown(KEY_W)){
        if(IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)){
            (*jogador).colisao.x -= (int)((*jogador).velocidade/sqrt(2));
            (*jogador).colisao.y -= (int)((*jogador).velocidade/sqrt(2));
        }
        else if(IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)){
            (*jogador).colisao.x += (int)((*jogador).velocidade/sqrt(2));
            (*jogador).colisao.y -= (int)((*jogador).velocidade/sqrt(2));
        }
        else if(!IsKeyDown(KEY_S)) (*jogador).colisao.y -= (int)((*jogador).velocidade/sqrt(2));
    }

    //Movimentar para baixo
    else if(IsKeyDown(KEY_S)){
        if(IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)){
            (*jogador).colisao.x -= (int)((*jogador).velocidade/sqrt(2));
            (*jogador).colisao.y += (int)((*jogador).velocidade/sqrt(2));
        }
        else if(IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)){
            (*jogador).colisao.x += (int)((*jogador).velocidade/sqrt(2));
            (*jogador).colisao.y += (int)((*jogador).velocidade/sqrt(2));
        }
        else (*jogador).colisao.y += (int)((*jogador).velocidade/sqrt(2));
    }

    //Movimentar para o lado esquerdo
    else if(IsKeyDown(KEY_A)) (*jogador).colisao.x -= (int)((*jogador).velocidade/sqrt(2));

    //Movimentar para o lado esquerdo
    else if (IsKeyDown(KEY_D)) (*jogador).colisao.x += (int)((*jogador).velocidade/sqrt(2));

    return;
}
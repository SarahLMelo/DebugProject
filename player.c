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
    else if(IsKeyDown(KEY_A) && !(IsKeyDown(KEY_D))) (*jogador).colisao.x -= (int)((*jogador).velocidade/sqrt(2));

    //Movimentar para o lado esquerdo
    else if (IsKeyDown(KEY_D)) (*jogador).colisao.x += (int)((*jogador).velocidade/sqrt(2));

    return;
}

bala atirar(int key1, int key2, nerdola jogador){
    //Inicializando projetil
    bala projetil;
    projetil.tempo = 0;
    projetil.dano = jogador.dano;
    projetil.velocidade = 20;
    projetil.x = 0;
    projetil.y = 0;

    //Criando caixa de colisão
    projetil.colisao.height = 10;
    projetil.colisao.width = 10;
    projetil.colisao.x = jogador.colisao.x;
    projetil.colisao.y = jogador.colisao.y;

    //Criando direção
    if(key1 == KEY_UP) projetil.y = -1;
    if(key1 == KEY_LEFT) projetil.x = -1;
    if(key1 == KEY_DOWN) projetil.y = 1;
    if(key1 == KEY_RIGHT) projetil.x = 1;

    if(key2 != 0) projetil.velocidade /= sqrt(2);
    if(key2 == KEY_UP) projetil.y = -1;
    if(key2 == KEY_LEFT) projetil.x = -1;
    if(key2 == KEY_DOWN) projetil.y = 1;
    if(key2 == KEY_RIGHT) projetil.x = 1;

    return projetil;
}

void playerEstaAtirando(bala **vetor, nerdola jogador, int *tamanho){
    //Atirando para cima
    if(IsKeyDown(KEY_UP)){
        if(IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)){
            (*vetor) = (bala*) realloc((*vetor), ((*tamanho)+1)*sizeof(bala));
            (*vetor)[(*tamanho)] = atirar(KEY_UP, KEY_LEFT, jogador);
            (*tamanho)++;
        }
        else if(IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)){
            (*vetor) = (bala*) realloc((*vetor), ((*tamanho)+1)*sizeof(bala));
            (*vetor)[(*tamanho)] = atirar(KEY_UP, KEY_RIGHT, jogador);
            (*tamanho)++;
        }
        else if(!IsKeyDown(KEY_DOWN)){
            (*vetor) = (bala*) realloc((*vetor), ((*tamanho)+1)*sizeof(bala));
            (*vetor)[(*tamanho)] = atirar(KEY_UP, 0, jogador); //O zero indica que só há uma tecla pressionada
            (*tamanho)++;
        }
    }

    //Atirando para baixo
    else if(IsKeyDown(KEY_DOWN)){
        if(IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)){
            (*vetor) = (bala*) realloc((*vetor), ((*tamanho)+1)*sizeof(bala));
            (*vetor)[(*tamanho)] = atirar(KEY_DOWN, KEY_LEFT, jogador);
            (*tamanho)++;
        }
        else if(IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)){
            (*vetor) = (bala*) realloc((*vetor), ((*tamanho)+1)*sizeof(bala));
            (*vetor)[(*tamanho)] = atirar(KEY_DOWN, KEY_RIGHT, jogador);
            (*tamanho)++;
        }
        else {
            (*vetor) = (bala*) realloc((*vetor), ((*tamanho)+1)*sizeof(bala));
            (*vetor)[(*tamanho)] = atirar(KEY_DOWN, 0, jogador); //O zero indica que só há uma tecla pressionada
            (*tamanho)++;
        }
    }

    //Movimentar para o lado esquerdo
    else if(IsKeyDown(KEY_LEFT) && !(IsKeyDown(KEY_RIGHT))){
        (*vetor) = (bala*) realloc((*vetor), ((*tamanho)+1)*sizeof(bala));
        (*vetor)[(*tamanho)] = atirar(KEY_LEFT, 0, jogador); //O zero indica que só há uma tecla pressionada
        (*tamanho)++;
    }

    //Movimentar para o lado esquerdo
    else if (IsKeyDown(KEY_RIGHT)){
        (*vetor) = (bala*) realloc((*vetor), ((*tamanho)+1)*sizeof(bala));
        (*vetor)[(*tamanho)] = atirar(KEY_RIGHT, 0, jogador); //O zero indica que só há uma tecla pressionada
        (*tamanho)++;
    }

    return;
}

void destruirProjetil(bala **vetor, int *tamanho){ //Destroi o projetil que está na frente do vetor

    for(int i=1; i<(*tamanho); i++) (*vetor)[i-1] = (*vetor)[i];
    (*tamanho)--;
    (*vetor) = (bala*) realloc((*vetor), (*tamanho)*sizeof(bala));

    return;
}

void movimentarProjetil(bala *projetil){
    (*projetil).colisao.x += (int)(*projetil).velocidade * (*projetil).x;
    (*projetil).colisao.y += (int)(*projetil).velocidade * (*projetil).y;

    return;
}
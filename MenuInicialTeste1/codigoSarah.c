#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include "raylib.h"

typedef struct{
    int vida, dano, armadura;
    double velocidade;
    Rectangle colisao;
} mob;

typedef struct{
    int vida, armadura;
    double velocidade;
    Rectangle colisao;
    Vector2 posicaoInicial;
} nerdola;

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

//funcoes do player
void inicializaPlayer(nerdola *jogador){
    //carregando o asset do player e do mob
    
    //Inicializa o player assim que abrir o jogo
    (*jogador).colisao.x = 900;
    (*jogador).colisao.y = 450;
    (*jogador).vida = 50;
    (*jogador).armadura = 0;
    (*jogador).velocidade = 15;
    //(*jogador).posicaoInicial={900.0, 450.0};

    //Dimensão da bolinha
    (*jogador).colisao.height = 30;
    (*jogador).colisao.width =30;

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

//funcoes dos mobs
#define SPEED_N 10

void moverCriatura(mob *criatura, int posX, int posY){
    //posição do player
    double playerX = (double) posX, playerY = (double) posY;

    double angulo = atan2(playerX-(*criatura).colisao.x, playerY-(*criatura).colisao.y); //angulação da reta entre o player e o mob

    //alterando posição do mob
    (*criatura).colisao.y += (int)(cos(angulo)*(*criatura).velocidade);
    (*criatura).colisao.x += (int)(sin(angulo)*(*criatura).velocidade);

    return;
}

int main(){
    InitWindow(1800, 900, "teste codigo da sarah");

    //Texture2D caixa=LoadTexture("Assets/medieval/Sprites/Run.png");

    if(!IsWindowReady()){
        printf("Janela com erro na inicializacao\n");
        exit(1);
    }
    SetTargetFPS(60);
    mob umaCriatura;
    nerdola jogador;
    criarCriatura(&umaCriatura, 0, 0);
    inicializaPlayer(&jogador);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        movimentarPlayer(&jogador);
        DrawRectangleRec(umaCriatura.colisao, RED);
        DrawRectangleRec(jogador.colisao, GREEN);
        EndDrawing();

        moverCriatura(&umaCriatura, jogador.colisao.x, jogador.colisao.y);
    }

    CloseWindow();
    return 0;
}
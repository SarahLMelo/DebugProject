#include "raylib.h"
#include "criaturas.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>

bala armaPrincipal[256];

int main(){
    InitWindow(1800, 900, "Janela de Desenvolvimento");

    if(!IsWindowReady()){
        printf("Janela com erro na inicializacao\n");
        exit(1);
    }
    SetTargetFPS(60);
    mob umaCriatura;
    nerdola jogador;
    int balasGastas = 0;
    criarCriatura(&umaCriatura, 0, 0);
    inicializaPlayer(&jogador);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        DrawRectangleRec(umaCriatura.colisao, RED);
        DrawRectangleRec(jogador.colisao, GREEN);
        for(int i=0; i<256; i++) if(armaPrincipal[i].viva==1) DrawRectangleRec(armaPrincipal[i].colisao, PURPLE);
        EndDrawing();

        moverCriatura(&umaCriatura, jogador.colisao.x, jogador.colisao.y);
        movimentarPlayer(&jogador);
        if(balasGastas<256) playerEstaAtirando(&armaPrincipal[balasGastas] , jogador, &balasGastas);
        atingiuOPlayer(&umaCriatura, &jogador);
        for(int i=0; i<256; i++) movimentarProjetil(&armaPrincipal[i]);

        if(jogador.vida <= 0){
            DrawText("VOCE MORREU!", 700, 350, 30, BLUE);
            while(IsKeyUp(KEY_SPACE) && IsKeyUp(KEY_ESCAPE)){
                BeginDrawing();
                DrawText("Pressione espaço para comecar novamente ou esc para sair", 600, 450, 20, BLUE);
                EndDrawing();
                criarCriatura(&umaCriatura, 0, 0);
                inicializaPlayer(&jogador);
            }
        }
    }

    CloseWindow();
    return 0;
}
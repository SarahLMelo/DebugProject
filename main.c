#include "raylib.h"
#include "criaturas.h"
#include "player.h"

#define SPEED_N 10

int main(){
    InitWindow(1800, 900, "Janela de Desenvolvimento");

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
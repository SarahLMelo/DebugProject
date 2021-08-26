#include "raylib.h"

#define larguraTela 800
#define alrutaTela 450

/*
void animacaoAsset(Texture2D nome){

    nome=LoadTexture("Assets/ninja/Run.png");
    posicao={0.0, 0.0};


    int frameAtual=0;
    int countFrames=0;
    int velFrame=8;

    countFrames++;
        if(countFrames>=(60/velFrame)){
            countFrames=0;
            frameAtual++;
            if(frameAtual>7){
                frameAtual=0;
            }
            frameRec.x = (float)frameAtual*(float)nome.width/8;
        }

        BeginDrawing();
            //cor da fundo da tela:
            ClearBackground(BLACK);
            //DrawTexture(ninja, 15, 40, WHITE);
            DrawTextureRec(nome, frameRec, posicao, WHITE); //animacao
        EndDrawing();
}
*/

int main(void) {
    //abrindo a janela:
    InitWindow(larguraTela, alrutaTela, "Animando os personagens");

    //iniciando o asset
    Texture2D ninja=LoadTexture("Assets/ninja/Run.png");;

    //informações do asset carregado
    Vector2 posicao={0.0, 0.0};
    Rectangle frameRec={0.0, 0.0, (float)ninja.width/8, (float)ninja.height };
    int frameAtual=0;
    int countFrames=0;
    int velFrame=8;            

    SetTargetFPS(60);              

    while(!WindowShouldClose()){
        countFrames++;
        if(countFrames>=(60/velFrame)){
            countFrames=0;
            frameAtual++;
            if(frameAtual>7){
                frameAtual=0;
            }
            frameRec.x = (float)frameAtual*(float)ninja.width/8;
        }

        BeginDrawing();
            //cor da fundo da tela:
            ClearBackground(BLACK);
            //DrawTexture(ninja, 15, 40, WHITE);
            DrawTextureRec(ninja, frameRec, posicao, WHITE); //animacao
        EndDrawing();
    }
    //lembrar de liberar o asset
    UnloadTexture(ninja);

    CloseWindow(); 
    return 0;
}
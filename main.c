#include "raylib.h"
#include "criaturas.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>

bala armaPrincipal[256];

int main(){
    InitWindow(1800, 900, "Nosso jogo");
    InitAudioDevice();
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        if(menuInicial()==1){
            mob *Criaturas = NULL;
            nerdola jogador;
            int balasGastas = 0, criaturasVivas = 0, wave = 1;
            Vector2 miraPosicao = {-100.0f, -100.0f};
            Color miraCor = DARKBLUE;
            inicializaPlayer(&jogador);
            HideCursor();

            
            while(IsKeyUp(KEY_ESCAPE)){
                criarWave(wave, &criaturasVivas, &Criaturas);
                criaturasVivas = wave;
                while(criaturasVivas>=0){
                    //Criando a parte de imagem
                    miraPosicao = GetMousePosition();
                    BeginDrawing();
                    ClearBackground(LIGHTGRAY);
                    for(int i=0; i<wave; i++){
                        if(Criaturas[i].vida > 0) DrawRectangleRec(Criaturas[i].colisao, RED);
                    }
                    DrawCircleV(miraPosicao, 15, miraCor);
                    DrawRectangleRec(jogador.colisao, GREEN);
                    for(int i=0; i<256; i++) if(armaPrincipal[i].viva==1) DrawRectangleRec(armaPrincipal[i].colisao, PURPLE);
                    EndDrawing();

                    //Mover tudo
                    for(int i=0; i<wave; i++) if(Criaturas[i].vida > 0) moverCriatura(&Criaturas[i], jogador.colisao.x, jogador.colisao.y);
                    movimentarPlayer(&jogador);

                    if(balasGastas<256) playerEstaAtirando(&armaPrincipal[balasGastas] , jogador, &balasGastas);
                    for(int i=0; i<wave; i++) if(Criaturas[i].vida > 0) atingiuOPlayer(&Criaturas[i], &jogador);
                    for(int i=0; i<256; i++){
                        if(&armaPrincipal[i].viva == 0) continue;
                        movimentarProjetil(&armaPrincipal[i]);
                        criaturasVivas -= acertouACriatura(&armaPrincipal[i], &Criaturas, wave);
                    }
                    if(jogador.vida <= 0){
                        DrawText("VOCE MORREU!", 700, 350, 30, BLUE);
                        while(IsKeyUp(KEY_SPACE) && IsKeyUp(KEY_ESCAPE)){
                            BeginDrawing();
                            DrawText("Pressione espaço para comecar novamente ou esc para sair", 600, 450, 20, BLUE);
                            EndDrawing();
                            wave = 1;
                            criaturasVivas = 0;
                            criarWave(wave, &criaturasVivas, &Criaturas);
                            inicializaPlayer(&jogador);
                        }
                    }
                }
            }
        }
    }


    return 0;
}
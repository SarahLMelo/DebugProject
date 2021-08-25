#include "raylib.h"
#include "criaturas.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "armas.h"

#define miraRaio 5

bala armaPrincipal[256];
Rectangle grid[1];
int qtdDeParedes = 1;

int main(){
    InitWindow(1920, 1080, "Nosso jogo");
    InitAudioDevice();
    Music music = LoadMusicStream("musica/TheBugger2.mp3");
    Sound tiro;
    tiro = LoadSound("sfx/sfxTiro.mp3");
    PlayMusicStream(music);

    //Setando camera
    Camera2D cameraJogador;
    cameraJogador.offset = (Vector2) {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    cameraJogador.target = (Vector2) {0.0f, 0.0f};
    cameraJogador.rotation = 0.0f;
    cameraJogador.zoom = 1.0f;

    //Iniciando o game
    SetTargetFPS(60);

    grid[0].height = 300;
    grid[0].width = 400;
    grid[0].x = 100;
    grid[0].y = 450;

    while (!WindowShouldClose())
    {
        if (menuInicial() == 1)
        {
            mob *Criaturas = NULL;
            nerdola jogador;
            int balasGastas = 0, criaturasVivas = 0, wave = 1, armaAtiva = 0;
            Vector2 miraPosicao = {-100.0f, -100.0f};
            Vector2 miraPosicaoDelta;
            Vector2 circlePosicao;
            double angulo = 0;
            Color miraCor = DARKBLUE;

            inicializaPlayer(&jogador);
            //HideCursor();

            while (IsKeyUp(KEY_ESCAPE))
            {
                //Atualizando a stream da música
                UpdateMusicStream(music);     

                criarWave(wave, &criaturasVivas, &Criaturas);
                criaturasVivas = wave;
                while (criaturasVivas > 0)
                {   
                    //Atualizando a stream da música
                    UpdateMusicStream(music);
                    //Criando a parte de imagem
                    BeginDrawing();
                    //Iniciando a camera
                    BeginMode2D(cameraJogador);
                    ClearBackground(LIGHTGRAY);
                    for (int i = 0; i < wave; i++)
                    {
                        if (Criaturas[i].vida > 0)
                            DrawRectangleRec(Criaturas[i].colisao, RED);
                    }
                    DrawRectangleRec(jogador.colisao, GREEN);
                    for (int i = 0; i < 256; i++)
                        if (armaPrincipal[i].viva == 1)
                            DrawRectangleRec(armaPrincipal[i].colisao, PURPLE);

                    DrawCircleV(circlePosicao, 5, miraCor);
                    for(int i=0; i<qtdDeParedes; i++) DrawRectangleRec(grid[i], YELLOW);
                    
                    

                    //Mover tudo
                    for (int i = 0; i < wave; i++)
                        if (Criaturas[i].vida > 0)
                            moverCriatura(&Criaturas[i], jogador.colisao.x, jogador.colisao.y, grid, qtdDeParedes);
                    movimentarPlayer(&jogador, grid, qtdDeParedes);
                    //Atualizando a camera
                    cameraJogador.target = (Vector2) {jogador.colisao.x, jogador.colisao.y};
                    cameraJogador.zoom = 1.0f;
                    //Atualizando a mira
                    miraPosicao = GetMousePosition();
                    miraPosicao.x += cameraJogador.target.x - cameraJogador.offset.x;
                    miraPosicao.y += cameraJogador.target.y - cameraJogador.offset.y;
                    circlePosicao = circleMira(miraPosicao, cameraJogador.target);
                    //Atualizando os pontos de colisao do mapa
                    
                    if(IsKeyDown(KEY_ONE)) armaAtiva = 1;
                    if(IsKeyDown(KEY_TWO)) armaAtiva = 2;

                    if (balasGastas < 256)
                        playerEstaAtirando(&armaPrincipal[balasGastas], jogador, &balasGastas, tiro, miraPosicao, armaAtiva);
                    for (int i = 0; i < wave; i++)
                        if (Criaturas[i].vida > 0)
                            atingiuOPlayer(&Criaturas[i], &jogador);
                    for (int i = 0; i < 256; i++)
                    {
                        if (&armaPrincipal[i].viva == 0)
                            continue;
                        movimentarProjetil(&armaPrincipal[i]);
                        criaturasVivas -= acertouACriatura(&armaPrincipal[i], &Criaturas, wave);
                    }
                    
                    EndMode2D();
                    EndDrawing();

                    if (jogador.vida <= 0)
                    {
                        while (IsKeyUp(KEY_SPACE))
                        {   
                            ClearBackground(BLACK);
                            DrawText("VOCE MORREU!", 700, 350, 30, BLUE);
                            DrawText("Pressione espaço para comecar novamente para sair", 600, 450, 20, BLUE);
                            EndDrawing();
                            wave = 0;
                            criaturasVivas = 0;
                            criarWave(wave, &criaturasVivas, &Criaturas);
                            inicializaPlayer(&jogador);
                            CloseWindow();
                        }
                    }
                }
                wave++;
            }
            free(Criaturas);
        }
    }

    UnloadMusicStream(music);
    CloseAudioDevice();

    CloseWindow();
    return 0;
}
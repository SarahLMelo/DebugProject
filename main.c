#include "raylib.h"
#include "criaturas.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "armas.h"
#include "mapa.h"
#include "menu.h"
#include "time.h"
#include "animacao.h"
#define miraRaio 5

//P virou a tecla de fechar o programa para S.

bala armaPrincipal[256];
bala armaSecundaria[1024];
Rectangle grid[50];
int qtdDeParedes = 45;

int main(){
  
    InitWindow(1920, 1080, "Nosso jogo");
    ToggleFullscreen();
    InitAudioDevice();
    Music music = LoadMusicStream("musica/TheBugger2.mp3");
    Sound tiro;
    tiro = LoadSound("sfx/sfxTiro.mp3");
    PlayMusicStream(music);
    int acao = 0;
    int acaoAntiga = 1;
    //Loading texturas
    Texture2D mapa = abrirMapa();
    //------Criatura 1
    Texture2D criatura1TexRed = LoadTexture("etc/personagens/principal/criatura1red.png");
    Texture2D criatura1TexYellowMorte = LoadTexture("etc/personagens/principal/criatura1yellowxplosion.png");
    Rectangle criatura1RecMorte = {0.0f, 0.0f, criatura1TexYellowMorte.width/9,criatura1TexYellowMorte.height/2};
    Rectangle criatura1Rec = {0.0f, 0.0f, criatura1TexRed.width/2, criatura1TexRed.height/2};
    //spritesheets load;
    spritesheet player = {
        8,
        0,
        8,
        0,
        LoadTexture("etc/personagens/principal/runrobocolorblue.png"),
        (Rectangle) {0.0f, 0.0f, player.textura.width/player.quantFrames, player.textura.height/4},
        (Vector2) {0.0f, 0.0f}
    };
    //Setando camera
    Camera2D cameraJogador;
    cameraJogador.offset = (Vector2) {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    cameraJogador.target = (Vector2) {0.0f, 0.0f};
    cameraJogador.rotation = 0.0f;
    cameraJogador.zoom = 1.0f;

    //Iniciando o game
    SetTargetFPS(60);
    //Setando os grids do collision map
    ColisionMap(grid, mapa);

    while (!WindowShouldClose())
    {

        //tela de carregamento
        int contadorTempo=0;
        clock_t prevTime = clock();
        int flag=0;

        if (menuInicial() == 1)
        {

            //tela de carregamento (abre uma tela rosa por 20s antes do jogo começar)
            while (contadorTempo < 20000 && flag==0)
            {
                clock_t currentTime = clock() - prevTime;
                contadorTempo = currentTime*1000/CLOCKS_PER_SEC;

                telaCarregamento();

                if(IsKeyPressed(KEY_T)){
                    flag=1;
                }
            }


            mob *Criaturas;

            nerdola jogador;
            int balasGastasPrincipal = 0, balasGastasSecundaria = 0,criaturasVivas = 0, wave = 1, armaAtiva = 1;
            int pontuacao = 0;
            Vector2 miraPosicao = {-100.0f, -100.0f};
            Vector2 circlePosicao;
            Color miraCor = DARKBLUE;
            
            inicializaPlayer(&jogador);
            

            while (IsKeyUp(KEY_P))
            {
                //Atualizando a stream da música
                HideCursor();

                UpdateMusicStream(music);     

                criarWave(wave, &criaturasVivas, &Criaturas, mapa.width, mapa.height);
                criaturasVivas = wave;
                while (criaturasVivas > 0)
                {   
                    //Atualizando a stream da música
                    UpdateMusicStream(music);
                    //Criando a parte de imagem
                    BeginDrawing();
                    //Iniciando a camera
                    BeginMode2D(cameraJogador);
                    ClearBackground(BLACK);
                    //Desenhando o mapa
                    DrawTextureEx(mapa, (Vector2){0.0f, 0.0f}, 0.0f, 3.0f, WHITE);

                    for (int i = 0; i < wave; i++)
                    {
                        if (Criaturas[i].vida > 0)
                            DrawRectangleRec(Criaturas[i].colisao, RED);
                    }
                    //DrawRectangleRec(jogador.colisao, GREEN); //colocando a caixa de colisao transparente
                    //adicionando a textura do nerdola (sem animacao ainda)
                    DrawTextureRec(corpoNerdola, frameRec, jogador.posicaoNerdola, WHITE);

                    //colocando a vida no canto da tela (seguindo a camera)  MUDEI AQUI
                    for (int i = 0; i < jogador.vida; i++)
                    {
                        DrawRectangle(jogador.colisao.x-1450 + 7*i, jogador.colisao.y-700, 20, 20, GREEN);
                    }
                    DrawText(TextFormat("balas restantes na arma secundaria: %i", 1024-balasGastasSecundaria), jogador.colisao.x-1450, jogador.colisao.y-580, 60, YELLOW);
                    DrawText(TextFormat("balas restantes na arma principal: %i", 256-balasGastasPrincipal), jogador.colisao.x-1450, jogador.colisao.y-650, 60, YELLOW);
                    for (int i = 0; i < 256; i++)
                        if (armaPrincipal[i].viva == 1)
                            DrawRectangleRec(armaPrincipal[i].colisao, PURPLE);
                    for (int i = 0; i < 1024; i++)
                        if (armaSecundaria[i].viva == 1)
                            DrawRectangleRec(armaSecundaria[i].colisao, PINK);

                    DrawCircleV(circlePosicao, 5, miraCor);
                    
                    // for(int i=0; i<qtdDeParedes; i++) DrawRectangleRec(grid[i], WHITE);
                    
                    //Mover tudo
                    moverCriatura(&Criaturas, jogador.colisao.x, jogador.colisao.y, grid, qtdDeParedes, wave);
                    //Animacao criatura
                    for (int i = 0; i < wave; i++)
                    {   
                        if (Criaturas[i].vida > 0){
                            DrawRectangleRec(Criaturas[i].colisao, RED);
                            Criaturas[i].anima.frameCounter++;
                            Criaturas[i].anima.position.x = Criaturas[i].colisao.x;
                            Criaturas[i].anima.position.y = Criaturas[i].colisao.y;
                            AnimarCriatura1(&Criaturas[i].anima, &criatura1TexRed, &criatura1Rec, 96, 96);
                            Criaturas[i].anima.oldposition.x = Criaturas[i].anima.position.x;
                            Criaturas[i].anima.oldposition.y = Criaturas[i].anima.position.y;
                            Criaturas[i].animaMorte.position.x = Criaturas[i].anima.position.x;
                            Criaturas[i].animaMorte.position.y = Criaturas[i].anima.position.y;
                        }else if(Criaturas[i].animaMorte.morreu == 1){
                                Criaturas[i].animaMorte.frameCounter++;
                                AnimarCriatura1(&Criaturas[i].animaMorte, &criatura1TexYellowMorte, &criatura1RecMorte, 96, 96);
                        }
                    }
                    acao = movimentarPlayer(&jogador, grid, qtdDeParedes);
                    //Animando player
                    switch(acao){
                        case 0: //Direita
                            acaoAntiga = 0;
                            break;
                        case 1: //Esquerda
                            acaoAntiga = 1;
                            break;
                        case 5: 
                            acao = acaoAntiga;
                            break;
                        case 3:
                            if(acaoAntiga == 0) acao = 3;
                            else acao = 2;
                            break;
                    } 
                    player.frameCounter++;
                    player.position.x = jogador.colisao.x;
                    player.position.y = jogador.colisao.y;
                    AnimarPlayer(&player, acao);

                    //Atualizando a camera
                    cameraJogador.target = (Vector2) {jogador.colisao.x, jogador.colisao.y};
                    cameraJogador.zoom = 0.75f;
                    
                    //Atualizando a mira
                    miraPosicao = GetMousePosition();
                    miraPosicao.x += cameraJogador.target.x - cameraJogador.offset.x;
                    miraPosicao.y += cameraJogador.target.y - cameraJogador.offset.y;
                    circlePosicao = circleMira(miraPosicao, cameraJogador.target);
                    //Atualizando os pontos de colisao do mapa
                    
                    if(IsKeyDown(KEY_ONE)){
                        armaAtiva = 1;
                        jogador.velocidade = 8;
                    }
                    if(IsKeyDown(KEY_TWO)){
                        armaAtiva = 2;
                        jogador.velocidade = 15;
                    }

                    if (balasGastasPrincipal < 256 && armaAtiva == 1)
                        playerEstaAtirando(&armaPrincipal[balasGastasPrincipal], jogador, &balasGastasPrincipal, tiro, miraPosicao, armaAtiva);
                    if (balasGastasSecundaria < 1024 && armaAtiva == 2)
                        playerEstaAtirando(&armaSecundaria[balasGastasSecundaria], jogador, &balasGastasSecundaria, tiro, miraPosicao, armaAtiva);
                    for (int i = 0; i < wave; i++)
                        if (Criaturas[i].vida > 0)
                            atingiuOPlayer(&Criaturas[i], &jogador);
                    for (int i = 0; i < 256; i++)
                    {
                        if (armaPrincipal[i].viva == 0)
                            continue;
                        movimentarProjetil(&armaPrincipal[i], grid);
                        criaturasVivas -= acertouACriatura(&armaPrincipal[i], &Criaturas, wave, &pontuacao);
                    }
                    for (int i = 0; i < 1024; i++)
                    {
                        if (armaSecundaria[i].viva == 0)
                            continue;
                        movimentarProjetil(&armaSecundaria[i], grid);
                        criaturasVivas -= acertouACriatura(&armaSecundaria[i], &Criaturas, wave, &pontuacao);
                    }
                    EndMode2D();
                    EndDrawing();

                    if (jogador.vida <= 0)
                    {
                        
                        while (IsKeyUp(KEY_SPACE))
                        {   
                            ClearBackground(BLACK);
                            DrawText("VOCE MORREU!", 345, 400, 150, RED);  
                            DrawText("Pressione espaço para comecar novamente ou p para sair", 490, 600, 30, LIGHTGRAY);
                            DrawText(TextFormat("pontuação: %i", pontuacao), 600, 700, 90, YELLOW);
                            EndDrawing();
                            wave = 0;
                            criaturasVivas = 0;
                            free(Criaturas);
                            criarWave(wave, &criaturasVivas, &Criaturas, mapa.width, mapa.height);
                            inicializaPlayer(&jogador);
                            if(IsKeyDown(KEY_P)){
                                free(Criaturas);
                                UnloadTexture(mapa);
                                UnloadMusicStream(music);
                                CloseAudioDevice();
                                CloseWindow();
                                return 0;
                            }
                            if(IsKeyDown(KEY_SPACE)) pontuacao = 0;
                        }
                    }
                }
                BeginMode2D(cameraJogador);
                BeginDrawing();
                while(Criaturas[wave-1].animaMorte.morreu == 1){ 
                    AnimarCriatura1(&Criaturas[wave-1].animaMorte, &criatura1TexYellowMorte, &criatura1RecMorte, 64, 64);
                    Criaturas[wave-1].animaMorte.frameCounter++;
                }
                EndDrawing();
                EndMode2D();
                wave+=5;
                free(Criaturas);
                for(int i=0; i<256; i++){
                    armaPrincipal[i].viva = 0;
                }
                for(int i=0; i<1024; i++){
                    armaSecundaria[i].viva = 0;
                }
                balasGastasPrincipal = 0;
                balasGastasSecundaria = 0;

            }
            free(Criaturas);
        }
    }
    UnloadTexture(player.textura);
    UnloadTexture(criatura1TexRed);
    UnloadTexture(criatura1TexYellowMorte);
    //UnloadTexture(criatura1TexYellow);
    UnloadTexture(mapa);
    UnloadMusicStream(music);
    CloseAudioDevice();

    CloseWindow();
    return 0;
}
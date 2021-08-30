#include "raylib.h"
#include "player.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "armas.h"

#define miraRadius 100

//Iniciando e importando áudio
void InitAudioDevice(void);
//Sound tiro = LoadSound("sfx/sfxTiro.mp3");

void inicializaPlayer(nerdola *jogador)
{
    //Inicializa o player assim que abrir o jogo
    (*jogador).colisao.x = 4000;
    (*jogador).colisao.y = 1000;
    (*jogador).vida = 1000;
    (*jogador).armadura = 0;
    (*jogador).posicaoNerdola.x=810;
    (*jogador).posicaoNerdola.y=360;
    (*jogador).velocidade = 8;

    //Dimensão da hitbox
    (*jogador).colisao.height = 30;
    (*jogador).colisao.width = 30;

    return;
}

int acertouAParede(nerdola jogador, Rectangle *grid, int quantidadeDeParedes){
    int acertou = 0;
    for(int i = 0; i<quantidadeDeParedes && acertou==0; i++)
        if(CheckCollisionRecs(jogador.colisao, grid[i]))
            acertou = 1;
    
    return acertou;
}

//adicionei o movimento "da imagem do nerdola"
int movimentarPlayer(nerdola *jogador, Rectangle *grid, int quantidadeDeParedes)
{
    //Movimentar para cima
    if (IsKeyDown(KEY_W))
    {
        if (IsKeyDown(KEY_A) && IsKeyUp(KEY_D))
        {
            (*jogador).colisao.x -= (int)((*jogador).velocidade / sqrt(2));
            (*jogador).colisao.y -= (int)((*jogador).velocidade / sqrt(2));
            (*jogador).posicaoNerdola.x -= (int)((*jogador).velocidade / sqrt(2));
            (*jogador).posicaoNerdola.y -= (int)((*jogador).velocidade / sqrt(2));

            if(acertouAParede((*jogador), grid, quantidadeDeParedes) == 1){ //Se acertar uma parede, fica parado
                (*jogador).colisao.x += (int)((*jogador).velocidade / sqrt(2));
                (*jogador).colisao.y += (int)((*jogador).velocidade / sqrt(2));
                (*jogador).posicaoNerdola.x += (int)((*jogador).velocidade / sqrt(2));
                (*jogador).posicaoNerdola.y += (int)((*jogador).velocidade / sqrt(2));
            }
            return 1;
        }
        else if (IsKeyDown(KEY_D) && IsKeyUp(KEY_A))
        {
            (*jogador).colisao.x += (int)((*jogador).velocidade / sqrt(2));
            (*jogador).colisao.y -= (int)((*jogador).velocidade / sqrt(2));
            (*jogador).posicaoNerdola.x += (int)((*jogador).velocidade / sqrt(2));
            (*jogador).posicaoNerdola.y -= (int)((*jogador).velocidade / sqrt(2));

            if(acertouAParede((*jogador), grid, quantidadeDeParedes) == 1){ //Se acertar uma parede, fica parado
                (*jogador).colisao.x -= (int)((*jogador).velocidade / sqrt(2));
                (*jogador).colisao.y += (int)((*jogador).velocidade / sqrt(2));
                (*jogador).posicaoNerdola.x -= (int)((*jogador).velocidade / sqrt(2));
                (*jogador).posicaoNerdola.y += (int)((*jogador).velocidade / sqrt(2));
            }
            return 0;
        }
        else if (IsKeyUp(KEY_S)){
            (*jogador).colisao.y -= (int)(*jogador).velocidade;
            (*jogador).posicaoNerdola.y -= (int)(*jogador).velocidade;

            if(acertouAParede((*jogador), grid, quantidadeDeParedes) == 1){ //Se acertar uma parede, fica parado
                (*jogador).colisao.y += (int)(*jogador).velocidade;
                (*jogador).posicaoNerdola.y += (int)(*jogador).velocidade;
            }
        }
        return 5;
    }

    //Movimentar para baixo
    else if (IsKeyDown(KEY_S))
    {
        if (IsKeyDown(KEY_A) && IsKeyUp(KEY_D))
        {
            (*jogador).colisao.x -= (int)((*jogador).velocidade / sqrt(2));
            (*jogador).colisao.y += (int)((*jogador).velocidade / sqrt(2));
            (*jogador).posicaoNerdola.x -= (int)((*jogador).velocidade / sqrt(2));
            (*jogador).posicaoNerdola.y += (int)((*jogador).velocidade / sqrt(2));

            if(acertouAParede((*jogador), grid, quantidadeDeParedes) == 1){ //Se acertar uma parede, fica parado
                (*jogador).colisao.x += (int)((*jogador).velocidade / sqrt(2));
                (*jogador).colisao.y -= (int)((*jogador).velocidade / sqrt(2));
                (*jogador).posicaoNerdola.x += (int)((*jogador).velocidade / sqrt(2));
                (*jogador).posicaoNerdola.y -= (int)((*jogador).velocidade / sqrt(2));
            }
            return 1;
        }
        else if (IsKeyDown(KEY_D) && IsKeyUp(KEY_A))
        {
            (*jogador).colisao.x += (int)((*jogador).velocidade / sqrt(2));
            (*jogador).colisao.y += (int)((*jogador).velocidade / sqrt(2));
            (*jogador).posicaoNerdola.x += (int)((*jogador).velocidade / sqrt(2));
            (*jogador).posicaoNerdola.y += (int)((*jogador).velocidade / sqrt(2));

            if(acertouAParede((*jogador), grid, quantidadeDeParedes) == 1){ //Se acertar uma parede, fica parado
                (*jogador).colisao.x -= (int)((*jogador).velocidade / sqrt(2));
                (*jogador).colisao.y -= (int)((*jogador).velocidade / sqrt(2));
                (*jogador).posicaoNerdola.x -= (int)((*jogador).velocidade / sqrt(2));
                (*jogador).posicaoNerdola.y -= (int)((*jogador).velocidade / sqrt(2));
            }
            return 0;
        }
        else{
            (*jogador).colisao.y += (int)(*jogador).velocidade;
            (*jogador).posicaoNerdola.y += (int)(*jogador).velocidade;

            if(acertouAParede((*jogador), grid, quantidadeDeParedes) == 1){ //Se acertar uma parede, fica parado
                (*jogador).colisao.y -= (int)(*jogador).velocidade;
                (*jogador).posicaoNerdola.y -= (int)(*jogador).velocidade;
            }     
        }
        return 5;
    }

    //Movimentar para o lado esquerdo
    else if (IsKeyDown(KEY_A) && IsKeyUp(KEY_D)){
        (*jogador).colisao.x -= (int)(*jogador).velocidade;
        (*jogador).posicaoNerdola.x -= (int)(*jogador).velocidade;

        if(acertouAParede((*jogador), grid, quantidadeDeParedes) == 1){  //Se acertar uma parede, fica parado
            (*jogador).colisao.x += (int)(*jogador).velocidade;
            (*jogador).posicaoNerdola.x += (int)(*jogador).velocidade;
        }
        return 1;  
    }

    //Movimentar para o lado direito
    else if (IsKeyDown(KEY_D)){
        (*jogador).colisao.x += (int)(*jogador).velocidade;
        (*jogador).posicaoNerdola.x += (int)(*jogador).velocidade;

        if(acertouAParede((*jogador), grid, quantidadeDeParedes) == 1){ //Se acertar uma parede, fica parado
            (*jogador).colisao.x -= (int)(*jogador).velocidade;
            (*jogador).posicaoNerdola.x -= (int)(*jogador).velocidade;
        } 
        return 0; 
    }

    return 3;
}

void playerEstaAtirando(bala *vetor, nerdola jogador, int *tamanho, Sound tiro, Vector2 cameraTarget, int armaAtiva, int modRifle, int modPistola)
{
    //Atirando com o mouse
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        (*vetor) = atirarComMouse(cameraTarget.x, cameraTarget.y, jogador, tiro, armaAtiva, modRifle, modPistola);
        (*tamanho)++;
    }

    //Atirando para cima
    /*if (IsKeyDown(KEY_UP))
    {
        if (IsKeyDown(KEY_LEFT) && IsKeyUp(KEY_RIGHT))
        {
            (*vetor) = atirarComTeclado(KEY_UP, KEY_LEFT, jogador, tiro, armaAtiva);
            (*tamanho)++;
        }
        else if (IsKeyDown(KEY_RIGHT) && IsKeyUp(KEY_LEFT))
        {
            (*vetor) = atirarComTeclado(KEY_UP, KEY_RIGHT, jogador, tiro, armaAtiva);
            (*tamanho)++;
        }
        else if (IsKeyUp(KEY_DOWN))
        {
            (*vetor) = atirarComTeclado(KEY_UP, 0, jogador, tiro, armaAtiva); //O zero indica que só há uma tecla pressionada
            (*tamanho)++;
        }
    }

    //Atirando para baixo
    else if (IsKeyDown(KEY_DOWN))
    {
        if (IsKeyDown(KEY_LEFT) && IsKeyUp(KEY_RIGHT))
        {
            (*vetor) = atirarComTeclado(KEY_DOWN, KEY_LEFT, jogador, tiro, armaAtiva);
            (*tamanho)++;
        }
        else if (IsKeyDown(KEY_RIGHT) && IsKeyUp(KEY_LEFT))
        {
            (*vetor) = atirarComTeclado(KEY_DOWN, KEY_RIGHT, jogador, tiro, armaAtiva);
            (*tamanho)++;
        }
        else
        {
            (*vetor) = atirarComTeclado(KEY_DOWN, 0, jogador, tiro, armaAtiva); //O zero indica que só há uma tecla pressionada
            (*tamanho)++;
        }
    }

    //Movimentar para o lado esquerdo
    else if (IsKeyDown(KEY_LEFT) && IsKeyUp(KEY_RIGHT))
    {
        (*vetor) = atirarComTeclado(KEY_LEFT, 0, jogador, tiro, armaAtiva); //O zero indica que só há uma tecla pressionada
        (*tamanho)++;
    }

    //Movimentar para o lado direito
    else if (IsKeyDown(KEY_RIGHT))
    {
        (*vetor) = atirarComTeclado(KEY_RIGHT, 0, jogador, tiro, armaAtiva); //O zero indica que só há uma tecla pressionada
        (*tamanho)++;
    }*/

    return;
}

void CloseAudioDevice(void);

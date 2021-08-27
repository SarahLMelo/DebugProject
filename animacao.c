#include "animacao.h"
#include "raylib.h"

void playAnimation(spritesheet *anim){
    spritesheet aux = *anim;
    if (aux.frameCounter >= (60/aux.frameSpeed))
        {
            aux.frameCounter = 0;
            aux.currentFrame++;

            if (aux.currentFrame > aux.quantFrames) aux.currentFrame = 0;

            aux.frame.x = (float)aux.currentFrame*(float)aux.textura.width/aux.quantFrames;
        }
    DrawTextureRec(aux.textura, aux.frame, aux.position, WHITE);
    *anim = aux;
}

void AnimarPlayer(spritesheet *anim, int acao){
    // acao - >>> parado = 0, direita = 1, esquerda = 2; 3 = cima ou baixo;
    spritesheet aux = *anim;
    Rectangle destRec = {aux.position.x-16*7,aux.position.y-16*12, 256, 256};
    if (aux.frameCounter >= (60/aux.frameSpeed))
        {
            aux.frameCounter = 0;
            aux.currentFrame++;

            if (aux.currentFrame > aux.quantFrames) aux.currentFrame = 0;

            aux.frame.x = (float)aux.currentFrame*(float)aux.textura.width/aux.quantFrames;
            aux.frame.y = acao*(float)aux.textura.height/4;
        }
    DrawTexturePro(aux.textura, aux.frame, destRec, (Vector2) {0.0f, 0.0f},(float) 0, WHITE);
    *anim = aux;
}

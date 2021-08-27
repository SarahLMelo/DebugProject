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
    Rectangle destRec = {aux.position.x-16*7,aux.position.y-16*9, 256, 256};
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

void AnimarCriatura1(spritesheetCreature *anim, Texture2D *textura, Rectangle *frame, int wi, int hi){
    spritesheetCreature aux = *anim; //0 Para direita 1 para esquerda
    Rectangle destRec = {aux.position.x-8,aux.position.y, wi, hi};
    switch(aux.morreu){
        case 0:
            if (aux.frameCounter >= (60/aux.frameSpeed)) {
                    if( aux.oldposition.x > aux.position.x) aux.dirOuEsq = 0;
                    else aux.dirOuEsq = 1;
                    
                    aux.frameCounter = 0;
                    aux.currentFrame++;

                    if (aux.currentFrame > aux.quantFrames) aux.currentFrame = 0;
                    (*frame).y = (float)aux.dirOuEsq*(float)(*textura).height/2;
                    (*frame).x = (float)aux.currentFrame*(float)(*textura).width/aux.quantFrames;
            }
            DrawTexturePro((*textura), (*frame), destRec, (Vector2) {0.0f, 0.0f},(float) 0, WHITE);
            *anim = aux;
            break;
        case 1: 
            if (aux.frameCounter >= (60/aux.frameSpeed)) {
                    aux.frameCounter = 0;
                    aux.currentFrame++;
                    if (aux.currentFrame > aux.quantFrames){
                        aux.flagAnimMorte = 0;
                        aux.morreu = 0;
                        aux.currentFrame = 0;
                        aux.frameCounter = 0;
                    }
                    (*frame).y = (float)aux.dirOuEsq*(float)(*textura).height/2;
                    (*frame).x = (float)aux.currentFrame*(float)(*textura).width/aux.quantFrames;
            }
            DrawTexturePro((*textura), (*frame), destRec, (Vector2) {0.0f, 0.0f},(float) 0, WHITE);
            *anim = aux;
            break;
    }
                
}   
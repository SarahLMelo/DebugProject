#include "animacao.h"
#include <raylib.h>

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
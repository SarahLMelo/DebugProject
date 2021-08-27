#ifndef ANIMACAO
#define ANIMACAO

#include <raylib.h>
typedef struct{
    int quantFrames;
    int frameCounter;
    int frameSpeed;
    int currentFrame;
    Texture2D textura;
    Rectangle frame; 
    Vector2 position;
} spritesheet;

typedef struct{
    int quantFrames;
    int frameCounter;
    int frameSpeed;
    int currentFrame;
    Vector2 position;
    Vector2 oldposition;
} spritesheetCreature;

void playAnimation(spritesheet *anim);

void AnimarPlayer(spritesheet *anim, int acao);

void AnimarCriatura1(spritesheetCreature *anim, Texture2D *textura, Rectangle *frame, int wi, int hi);

#endif
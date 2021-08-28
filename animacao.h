#ifndef ANIMACAO
#define ANIMACAO

#include <raylib.h>
typedef struct{
    int quantFrames;
    int frameCounter;
    int frameSpeed;
    int currentFrame;
    int ativo;
    float angulo;
    Texture2D textura1;
    Texture2D textura2;
    Rectangle frame; 
    Vector2 position;
} spritesheet;

typedef struct{
    int quantFrames;
    int frameCounter;
    int frameSpeed;
    int currentFrame;
    int lrTimer;
    int delta;
    double angulo;
    Vector2 position;
    Vector2 oldposition;
    Rectangle frame;
    int dirOuEsq;
    int flagAnimMorte;
    int morreu;
    int tipo;
    int estaAtacando;
    int atacou;
    int delayAnimacao;
} spritesheetCreature;

void AnimarBala(spritesheet *anim);

void AnimarPlayer(spritesheet *anim, int acao);

void AnimarCriatura1(spritesheetCreature *anim, Texture2D *textura, Rectangle *frame, int wi, int hi);

void AnimarCriatura2(spritesheetCreature *anim, Texture2D *textura, Rectangle *frame, int wi, int hi, int x, int y);

#endif
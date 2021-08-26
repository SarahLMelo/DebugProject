#include <raylib.h>
typedef struct{
    int frameCounter;
    int frameSpeed;
    int currentFrame;
    Texture2D textura;
    Rectangle frame; 
    Vector2 position;
} spritesheet;

void playAnimation(spritesheet *anim);

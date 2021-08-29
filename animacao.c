#include "raylib.h"

int main(void)
{

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 6.0f;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 6.0f;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= 6.0f;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += 6.0f;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

            DrawCircleV(ballPosition, 50, MAROON);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
/*
    //inicialização
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "exemplo de textura");

    Texture2D scarfy = LoadTexture("resources/scarfy.png");

    Vetor2 posicao = { 350.0f, 280.0f };
    Retangulo frameRec = { 0.0f, 0.0f, (float)scarfy.width/6, (float)scarfy.height };
    int currentFrame = 0;

    int framesCounter = 0;
    int framesSpeed = 8;

    SetTargetFPS (60);

    while(!WindowShouldClose())
    {

    }*/
=======
#include "animacao.h"
#include "raylib.h"
#include <math.h>

void AnimarBala(spritesheet *anim){
    spritesheet aux = *anim;
    Rectangle destRec = {aux.position.x+16*sin(aux.angulo),aux.position.y-16*cos(aux.angulo), aux.textura2.width/(aux.quantFrames*5), aux.textura2.height/5};
    if (aux.frameCounter >= (60/aux.frameSpeed))
        {
            aux.frameCounter = 0;
            aux.currentFrame++;
            if (aux.currentFrame > aux.quantFrames) aux.currentFrame = 0;

            aux.frame.x = (float)aux.currentFrame*(float)aux.textura1.width/aux.quantFrames;
        }
    if(aux.ativo == 1) DrawTexturePro(aux.textura1, aux.frame, destRec, (Vector2) {0.0f, 0.0f}, -aux.angulo, WHITE);
    else DrawTexturePro(aux.textura2, aux.frame, destRec, (Vector2) {0.0f, 0.0f}, -aux.angulo, WHITE);
    *anim = aux;
}

void AnimarPlayer(spritesheet *anim, int acao){
    // acao - >>> parado = 0, direita = 1, esquerda = 2; 3 = cima ou baixo;
    spritesheet aux = *anim;
    Rectangle destRec = {aux.position.x-32,aux.position.y-128, 1*(*anim).textura2.width/8, 1*(*anim).textura2.height/4};
    if (aux.frameCounter >= (60/aux.frameSpeed))
        {
            aux.frameCounter = 0;
            aux.currentFrame++;
            if (aux.currentFrame > aux.quantFrames) aux.currentFrame = 0;

            aux.frame.x = (float)aux.currentFrame*(float)aux.textura1.width/aux.quantFrames;
            aux.frame.y = acao*(float)aux.textura1.height/4;
        }
    if(aux.ativo == 1) DrawTexturePro(aux.textura1, aux.frame, destRec, (Vector2) {0.0f, 0.0f},(float) 0, WHITE);
    else DrawTexturePro(aux.textura2, aux.frame, destRec, (Vector2) {1.0f, 0.0f},(float) 0, WHITE);
    *anim = aux;
}

void AnimarCriatura1(spritesheetCreature *anim, Texture2D *textura, int wi, int hi){
    spritesheetCreature aux = *anim; //0 Para direita 1 para esquerda
    Rectangle destRec = {aux.position.x-8,aux.position.y, wi, hi};
    switch(aux.morreu){
        case 0:
            if (aux.frameCounter >= (60/aux.frameSpeed)) {
                    
                    aux.frameCounter = 0;
                    aux.currentFrame++;

                    if (aux.currentFrame > aux.quantFrames){ 
                        aux.currentFrame = 0;            
                        if( aux.delta > 0) aux.dirOuEsq = 0;
                        else aux.dirOuEsq = 1;
                        aux.frame.y = (float)aux.dirOuEsq*(float)(*textura).height/2;
                    }
                    aux.frame.x = (float)aux.currentFrame*(float)(*textura).width/aux.quantFrames;
            }
            DrawTexturePro((*textura), aux.frame, destRec, (Vector2) {0.0f, 0.0f},(float) 0, WHITE);
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
                    aux.frame.y = (float)aux.dirOuEsq*(float)(*textura).height/2;
                    aux.frame.x = (float)aux.currentFrame*(float)(*textura).width/aux.quantFrames;
            }
            DrawTexturePro((*textura), aux.frame, destRec, (Vector2) {0.0f, 0.0f},(float) 0, WHITE);
            *anim = aux;
            break;
    }
                
}   

void AnimarCriatura2(spritesheetCreature *anim, Texture2D *textura, Rectangle *frame, int wi, int hi, int x, int y){
    spritesheetCreature aux = *anim; //0 Para direita 1 para esquerda
    Rectangle destRec = {aux.position.x-x,aux.position.y-y, wi, hi};
    if(aux.morreu == 0){
        if(aux.estaAtacando == 0){
        if (aux.frameCounter >= (60/6)) {
                aux.frameCounter = 0;
                aux.currentFrame++;
                if (aux.currentFrame > aux.quantFrames){
                    aux.currentFrame = 0;            
                    if( aux.delta > 0) aux.dirOuEsq = 1;
                    else aux.dirOuEsq = 0;
                }  
                aux.frame.y = (float)aux.dirOuEsq*(float)(*textura).height/2;
                aux.frame.x = (float)aux.currentFrame*(float)(*textura).width/aux.quantFrames;
        }
        DrawTexturePro((*textura), aux.frame, destRec, (Vector2) {2.0f, 1.0f},(float) 0, WHITE);
        *anim = aux;
        } else {
            if (aux.frameCounter >= (60/aux.frameSpeed)) {
                aux.frameCounter = 0;
                aux.currentFrame++;
                if (aux.currentFrame > aux.quantFrames){
                    aux.atacou = 1;
                    aux.currentFrame = 0;
                    aux.frameCounter = 0;
                    aux.estaAtacando = 0;
                    aux.delayAnimacao = 0;
                }
                if(cos(aux.angulo) > 0) aux.frame.y = 0;
                else (*frame).y = 1*(float)(*textura).height/2;
                (*frame).x = (float)aux.currentFrame*(float)(*textura).width/17;
        }
        DrawTexturePro((*textura), (*frame), destRec, (Vector2) {0.0f, 0.0f},(float) 0, WHITE);
        *anim = aux;
        }
    } else { 
        if (aux.frameCounter >= (60/11)) {
                aux.frameCounter = 0;
                aux.currentFrame++;
                if (aux.currentFrame > 10){
                    aux.flagAnimMorte = 0;
                    aux.morreu = 0;
                    aux.currentFrame = 0;
                    aux.frameCounter = 0;
                }
                aux.frame.y = (float)aux.dirOuEsq*(float)(*textura).height/2;
                aux.frame.x = (float)aux.currentFrame*(float)(*textura).width/12;
        }
        DrawTexturePro((*textura), aux.frame, destRec, (Vector2) {0.0f, 0.0f},(float) 0, WHITE);
        *anim = aux;
    }
                
}   

void AnimarHud(spritesheet *anim, Texture2D textura, int wi, int hi, int x, int y){
    Rectangle destRec = {x,y, wi, hi};
    spritesheet aux = *anim;
    if (aux.frameCounter >= (60/aux.frameSpeed))
        {
            aux.frameCounter = 0;
            aux.currentFrame++;
            if (aux.currentFrame > aux.quantFrames) aux.currentFrame = 0;

            aux.frame.x = (float)aux.currentFrame*(float)aux.textura1.width/aux.quantFrames;
        }
    DrawTexturePro(textura, aux.frame, destRec, (Vector2) {0.0f, 0.0f}, aux.angulo, WHITE);
    *anim = aux;
}
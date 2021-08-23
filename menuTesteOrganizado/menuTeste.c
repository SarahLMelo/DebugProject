#include "raylib.h"

void abrirGlossario(){
    char mensagem[]="teste";

    BeginDrawing();
        ClearBackground(RED);
        DrawText(mensagem, 0 ,0 , 200, WHITE);
    
        
    EndDrawing();
}

void menuInicial(){
    //carregando os botoes
    Texture2D botaoStart=LoadTexture("Assets/Botoes/start.png");
    Texture2D botaoGlossario=LoadTexture("Assets/Botoes/menu.png");

    //carregando o nerdola*
    Texture2D nerdola = LoadTexture("Assets/personagens/medieval/Idle.png");
    Rectangle frameNerdola = { 0.0, 0.0, (float)nerdola.width/8, (float)nerdola.height };
    Rectangle caracNerdola = {1.0, 900/2.0, (nerdola.width/8)*5.5f, nerdola.height*5.5f};
    Vector2 originNerdola = { (float)nerdola.width/8, (float)nerdola.height};

    //carregando monstro da capa
    Texture2D monstro = LoadTexture("Assets/personagens/monstroMenu/Attack3.png");
    Rectangle frameMonstro = { 0.0, 0.0, (float)monstro.width/6, (float)monstro.height };
    Rectangle caracMonstro = {1800/3.0, 900/2.0, (monstro.width/6)*5.5f, monstro.height*5.5f};
    Vector2 originMonstro = { (float)monstro.width/6, (float)monstro.height};

    //carregando a musica do ratinho
    //InitAudioDevice();
    Sound ratinho = LoadSound("Assets/audios/ratinho.wav");

    //mensagem do titulo
    const char titulo[]="TheBugger";

    //variaveis para o mouse e butoes
    Vector2 posicaoMouse={0,0};
    int mouseButaoGlossario=0;
    int mouseButaoStart=0;

    //posicao do mouse:
    posicaoMouse.x=GetMouseX();
    posicaoMouse.y=GetMouseY();

    //checando se o mouse esta nos limites do butao do glossario:
    if(posicaoMouse.x>=1300 && posicaoMouse.x<=1600 && posicaoMouse.y>=730 && posicaoMouse.y<=830){
        //PlaySound(ratinho);
        mouseButaoGlossario=1;
    }
        
    else mouseButaoGlossario=0;

    //para o butao start
    if(posicaoMouse.x>=1300 && posicaoMouse.x<=1600 && posicaoMouse.y>=550 && posicaoMouse.y<=650){
        mouseButaoStart=1;
        //PlaySound(ratinho);
    }
        
    else mouseButaoStart=0;

    //geral:
    int glossario=0;

    BeginDrawing();
        ClearBackground(BLACK);
        
        if(mouseButaoStart){
            DrawTexture(botaoStart, 1300, 550, WHITE);
            DrawTexture(botaoGlossario, 1300, 730, DARKGREEN);
        }
        else if(mouseButaoGlossario){
            DrawTexture(botaoGlossario, 1300, 730, WHITE);
            DrawTexture(botaoStart, 1300, 550, DARKGREEN);
        }
        else{
            DrawTexture(botaoGlossario, 1300, 730, DARKGREEN);
            DrawTexture(botaoStart, 1300, 550, DARKGREEN);
        } 

        DrawTexturePro(nerdola, frameNerdola, caracNerdola, originNerdola, 0.0, WHITE); //sem animacao
        DrawTexturePro(monstro, frameMonstro, caracMonstro, originMonstro, 0.0, WHITE); //sem animacao


        DrawText(titulo, 30, 70, 270, DARKGREEN);

    EndDrawing();

    
    if(mouseButaoGlossario && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
        PlaySound(ratinho);
        glossario=1;
        while(glossario==1){
            abrirGlossario();
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                glossario=0;
            }
        }
    }
    
    //CloseAudioDevice();

    UnloadSound(ratinho);
    UnloadTexture(botaoStart);
    UnloadTexture(botaoGlossario);
    UnloadTexture(nerdola);
    UnloadTexture(monstro);
}



int main(){

    InitWindow(1800, 900, "menu teste");
    InitAudioDevice();
    SetTargetFPS(60);

    while(!WindowShouldClose()){

        menuInicial();

    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
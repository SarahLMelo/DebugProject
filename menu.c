#include "menu.h"
#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include "glossario.h"

void telaCarregamento(){
    Camera2D menu;
    
    menu.zoom = GetScreenWidth()/1920.0f;
    menu.target = (Vector2){0.0f, 0.0f};
    menu.offset = (Vector2){0.0f, 0.0f};
    menu.rotation = 0.0f;
    
    Texture2D teclado=LoadTexture("Assets/Botoes/wasd.png");

        char intro[]="Nas profundezas das cavernas das noites mal dormidas,\nhabita um grande mal que assombra a humanidade, um mal que\nsomente você, Nerdola, será capaz de eliminar.\n\nEssas criaturas monstruosas, capazes de destruir tudo que a humanidade\nconstruiu nos últimos anos, são conhecidas como bugs.\nElas possuem vários tipos e formas, mas não se engane, jovem,\ntodas estão dispostas a destruir a humanidade.";
        char instrucoes[]="Aperte WASD para andar, botão esquerdo do mouse\npara atirar, 1 para mudar para a arma pesada, 2\npara a arma leve, Q para abrir a loja e E para fechar.";
        BeginDrawing();
        BeginMode2D(menu);
            ClearBackground(BLACK);
            DrawText(intro, 200, 200, 40, LIGHTGRAY);
            DrawText(instrucoes, 870, 800, 30, YELLOW);
            DrawTexture(teclado, 360, 730, GRAY);
            DrawText("Para pular aperte T", 1500, 1000, 30, RED);
        EndDrawing();
        EndMode2D();
    UnloadTexture(teclado);
}

int menuInicial(){
    Texture2D botaoStart=LoadTexture("Assets/Botoes/start.png");
    Rectangle botaoStartRec = {1300, 550, botaoStart.width, botaoStart.height};
    Texture2D botaoGlossario=LoadTexture("Assets/Botoes/menu.png");
    Rectangle botaoGlossarioRec = {1300, 730, botaoGlossario.width, botaoGlossario.height};

    //carregando o nerdola*
    Texture2D nerdola = LoadTexture("Assets/personagens/runRobo.png");
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
    Rectangle mouse = {posicaoMouse.x, posicaoMouse.y, 20, 20};
    //checando se o mouse esta nos limites do butao do glossario:
        

    Camera2D menu;
    menu.zoom = GetScreenWidth()/1920.0f;
    menu.target = (Vector2){0.0f, 0.0f};
    menu.offset = (Vector2){0.0f, 0.0f};
    menu.rotation = 0.0f;
        
    //geral:
    int glossario=0;
    BeginDrawing();
    BeginMode2D(menu);


    DrawRectangleRec(botaoStartRec, PINK);
    DrawRectangleRec(botaoGlossarioRec, PINK);
    posicaoMouse.x=GetMouseX();
    posicaoMouse.y=GetMouseY();
    double p = GetScreenWidth()/(double)1920;
    double k = 3.43431*p*p-7.2143*p+3.78134;
    mouse.x = posicaoMouse.x + k*posicaoMouse.x;
    mouse.y = posicaoMouse.y + k*posicaoMouse.y;
    printf(" x = %f\n ", mouse.x);
    printf(" y = %f\n ", mouse.y);
    DrawRectangleRec(mouse, PINK);
    if(CheckCollisionRecs(botaoStartRec, mouse)){
        mouseButaoStart=1;
    }
    else mouseButaoStart=0;
    if(CheckCollisionRecs(mouse, botaoGlossarioRec)){
        mouseButaoGlossario=1;
    }
    else mouseButaoGlossario=0;
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

    
    if(mouseButaoGlossario && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        glossario=1;
        while(glossario==1){
            mostrarGlossario();
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                glossario=0;
        }
    }

    if(mouseButaoStart && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        return 1;
    
    
    //CloseAudioDevice();

    UnloadTexture(botaoStart);
    UnloadTexture(botaoGlossario);
    UnloadTexture(nerdola);
    UnloadTexture(monstro);
    return 0;
}

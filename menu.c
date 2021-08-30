#include "raylib.h"
#include "menu.h"
#include <stdio.h>
#include <math.h>
#include "glossario.h"

void telaCarregamento(){
    Camera2D menu;
    
    menu.zoom = GetScreenWidth()/1920.0f;
    menu.target = (Vector2){0.0f, 0.0f};
    menu.offset = (Vector2){0.0f, 0.0f};
    menu.rotation = 0.0f;
    
    Texture2D teclado = LoadTexture("Assets/Botoes/wasd.png");

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

int menuInicial(Image *menuIm){
    Texture2D menuPng = LoadTextureFromImage((*menuIm));
    Texture2D botaoStart=LoadTexture("Assets/Botoes/start.png");
    Rectangle botaoStartRec = {1300, 550, botaoStart.width, botaoStart.height};
    Texture2D botaoGlossario=LoadTexture("Assets/Botoes/menu.png");
    Rectangle botaoGlossarioRec = {1300, 730, botaoGlossario.width, botaoGlossario.height};

    //carregando a musica do ratinho
    //InitAudioDevice();

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
    
    //DrawRectangleRec(botaoStartRec, PINK);
    //DrawRectangleRec(botaoGlossarioRec, PINK);
    posicaoMouse.x=GetMouseX();
    posicaoMouse.y=GetMouseY();
    double p = GetScreenWidth()/(double)1920;
    SetMouseScale((1/p), (1/p));
    mouse = (Rectangle) {(float) posicaoMouse.x, (float) posicaoMouse.y, 20, 20};
    float k = menuPng.width/(float)GetScreenWidth();
    DrawTexturePro(menuPng, (Rectangle){0.0f, 0.0f,menuPng.width, menuPng.height}, (Rectangle){0.0f,0.0f,(int)((k)*GetScreenWidth())/2,(int)((k)*GetScreenHeight())/2}, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
    //DrawRectangleRec(mouse, PINK);
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

    
    EndMode2D();
    EndDrawing();

    
    if(mouseButaoGlossario && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    glossario=1;
            Texture2D botaoLore=LoadTexture("Assets/Botoes/lore.png");
            Texture2D botaoInimigos=LoadTexture("Assets/Botoes/inimigos.png");
            Texture2D botaoFormas=LoadTexture("Assets/Botoes/formas.png");
            Texture2D botaoVoltar=LoadTexture("Assets/Botoes/voltar.png");
            Texture2D libelulaverde = LoadTexture("Assets/assets/libelulaverde.png");
            Texture2D libelulaamarela = LoadTexture("Assets/assets/libelulaamarela.png");
            Texture2D libelulavermelha = LoadTexture("Assets/assets/libelulavermelha.png");
            Texture2D esqueletoimg = LoadTexture("Assets/assets/esqueleto.png");
            Texture2D formaazul=LoadTexture("Assets/assets/forma_azul.png");
            Texture2D formaamarela=LoadTexture("Assets/assets/forma_amarela.png");
            while(glossario==1){
                mostrarGlossario
            (
            botaoLore,
            botaoInimigos,
            botaoFormas,
            botaoVoltar,
            libelulaverde,
            libelulaamarela,
            libelulavermelha,
            esqueletoimg,
            formaazul,
            formaamarela
            );
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    glossario=0;
            }
            }
            UnloadTexture(menuPng);
            UnloadTexture(botaoLore);
            UnloadTexture(botaoInimigos);
            UnloadTexture(botaoFormas);
            UnloadTexture(botaoVoltar);
            UnloadTexture(libelulaverde);
            UnloadTexture(libelulaamarela);
            UnloadTexture(libelulavermelha);
            UnloadTexture(esqueletoimg);
            UnloadTexture(formaazul);
            UnloadTexture(formaamarela);
    if(mouseButaoStart && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        return 1;
    
    
    //CloseAudioDevice();

    UnloadTexture(botaoStart);
    UnloadTexture(botaoGlossario);
    return 0;
}


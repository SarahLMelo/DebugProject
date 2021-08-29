#include "player.h"
#include "raylib.h"

void aumentoDanoPistola(int *modPistola, int *moeda){
    (*modPistola) += 10;
    (*moeda) -= 40;
    return;
}

void aumentoDanoRifle(int *modRifle, int *moeda){
    (*modRifle) += 10;
    (*moeda) -= 25;
    return;
}

void aumentoArmadura(nerdola *jogador, int *moeda){
    (*jogador).armadura += 1;
    (*moeda) -= 30;
}

void abrirLoja(int *moeda, int *modPistola, int *modRifle, nerdola *jogador, bala (*armaPrincipal)[], bala (*armaSecundaria)[], int qntdMaxP, int qntdMaxS, int *balasGastasPrincipal, int *balasGastasSec){
    while(!IsKeyPressed(KEY_Q))
    {
        Camera2D menu;
        menu.zoom = GetScreenWidth()/1920.0f;
        menu.target = (Vector2){0.0f, 0.0f};
        menu.offset = (Vector2){0.0f, 0.0f};
        menu.rotation = 0.0f;
        
        BeginDrawing();
        BeginMode2D(menu);
        ShowCursor();

        Vector2 posicaoMouse={0,0};
        double p = GetScreenWidth()/(double)1920;
        posicaoMouse.x=GetMouseX();
        posicaoMouse.y=GetMouseY();
        SetMouseScale((1/p), (1/p));
        Rectangle mouse = (Rectangle) {(float) posicaoMouse.x, (float) posicaoMouse.y, 20, 20};

        int compraAzul=0;
        int compraAmarela=0;
        int compraVida=0;
        int recarregar=0;
        Rectangle compraAzulRec = {80, 370, 1700, 70};
        Rectangle compraAmarelaRec = {80, 490, 1700, 70};
        Rectangle compraVidaRec = {80, 610, 1700, 70};
        Rectangle compraRecarregarRec  = {80, 730, 1700, 70};
        Rectangle mouseRec = {mouse.x, mouse.y, 20, 20};
        
        if(CheckCollisionRecs(mouseRec, compraAzulRec))
            compraAzul=1;
        if(CheckCollisionRecs(mouseRec,compraAmarelaRec))
            compraAmarela=1;
        if(CheckCollisionRecs(mouseRec, compraVidaRec))
            compraVida=1;
        if(CheckCollisionRecs(mouseRec, compraRecarregarRec))
            recarregar=1;


        ClearBackground(BLACK);
        DrawText("loja", 750, 50, 200, BLUE);
        DrawText("arma azul ------ +10 dano", 95, 375, 50, WHITE);
        DrawText("40 moedas", 1500, 375, 50, WHITE);
        DrawText("arma amarela ------ +10 dano", 95, 495, 50, WHITE);
        DrawText("25 moedas", 1500, 495, 50, WHITE);
        DrawText("armadura ------ +1", 95, 615, 50, WHITE);
        DrawText("30 moedas", 1500, 615, 50, WHITE);
        DrawText("recarregar", 95, 735, 50, WHITE);
        DrawText("Para SAIR aperte Q", 1450, 1000, 30, WHITE);

        if(compraAzul==1)
        {
            DrawRectangleLines(80, 370, 1700, 70, GRAY);
            if((*moeda)>=40)
            {
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    aumentoDanoPistola(modPistola, moeda);  
            }    
            else DrawRectangleLines(80, 370, 1700, 70, RED);        
        } 
        else DrawRectangleLines(80, 370, 1700, 70, BLUE);
        if(compraAmarela==1)
        {
            DrawRectangleLines(80, 490, 1700, 70, GRAY);
            if((*moeda)>=25)
            {
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    aumentoDanoRifle(modRifle, moeda); 
            }
            else DrawRectangleLines(80, 490, 1700, 70, RED);
        } 
        else DrawRectangleLines(80, 490, 1700, 70, ORANGE);

        if(compraVida==1)
        {
            DrawRectangleLines(80, 610, 1700, 70, GRAY);
            if ((*moeda)>=20)
            {
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    aumentoArmadura(jogador, moeda);
            }     
            else DrawRectangleLines(80, 610, 1700, 70, RED);
        } 
        else DrawRectangleLines(80, 610, 1700, 70, LIME);

        if(recarregar==1)
        {
            DrawRectangleLines(80, 730, 1700, 70, GRAY);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
                recarregarArmas(armaPrincipal, armaSecundaria, qntdMaxP, qntdMaxS, balasGastasPrincipal, balasGastasSec);
        } 
        else DrawRectangleLines(80, 730, 1700, 70, VIOLET);

        DrawText(TextFormat("moedas: %d", (*moeda)), 1500, 60, 50, YELLOW);

        EndDrawing();
        EndMode2D();
        if(IsKeyPressed(KEY_Q))
            HideCursor();
    }
}
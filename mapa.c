#include "raylib.h"
#include "player.h"
#include "criaturas.h"

Texture2D abrirMapa(){
    Image mapaPng = LoadImage("Assets/Mapa/mapa2.5.png");
    Texture2D mapa = LoadTextureFromImage(mapaPng);
    UnloadImage(mapaPng);
    return mapa;
}

bool checarLimiteCamera();

Vector2 spawnPoints();

void ColisionMap(Rectangle grid[], Texture2D mapa){
    //Parede da esquerda do mapa
    grid[0].height = mapa.height*3;
    grid[0].width = 1;
    grid[0].x = 48;
    grid[0].y = 0;
    //Parede de cima do mapa
    grid[1].height = 2;
    grid[1].width = mapa.width*3;
    grid[1].x = 0;
    grid[1].y = 264;
    //Parede da direita do mapa
    grid[2].height = mapa.height*3;
    grid[2].width = 1;
    grid[2].x = (mapa.width*3)-48;
    grid[2].y = 0;
    //Parede de baixo
    grid[3].height = 2;
    grid[3].width = mapa.width*3;
    grid[3].x = 0;
    grid[3].y = mapa.height*3-48;
    //Precipicio Baixo Horizontal 1 
    grid[4].height = 2;
    grid[4].width = 576;
    grid[4].x = 0;
    grid[4].y = mapa.height*3-(16*20*3);
    //Precipicio Baixo Horizontal 2
    grid[5].height = 2;
    grid[5].width = 528;
    grid[5].x = 576;
    grid[5].y = mapa.height*3-(16*16*3);
    //Precipicio Baixo Horizontal 3
    grid[6].height = 2;
    grid[6].width = 528;
    grid[6].x = (528)*2;
    grid[6].y = mapa.height*3-(16*9*3);
    //Precipicio Baixo Vertical 1
    grid[7].height = (16*4*3);
    grid[7].width = 2;
    grid[7].x = 576;
    grid[7].y = mapa.height*3-(16*20*3);
    //Precipicio Baixo Vertical 2
    grid[8].height = (16*6*4);
    grid[8].width = 2;
    grid[8].x = (552)*2;
    grid[8].y = mapa.height*3-(16*16*3);
    //Precipicio Baixo Vertical 3
    grid[9].height = (16*6*4);
    grid[9].width = 2;
    grid[9].x = (528)*3;
    grid[9].y = mapa.height*3-(16*9*3);
    //Caixona boss inside 1
    grid[10].height = 1080;
    grid[10].width = 3*16;
    grid[10].x = 2000;
    grid[10].y = 0;
    //Caixona boss inside 2
    grid[11].height = 1080;
    grid[11].width = 3*16;
    grid[11].x = 3328;
    grid[11].y = 0;
    //Caixona boss inside MEIO
    grid[12].height = 1080;
    grid[12].width = 1328;
    grid[12].x = 2000+3*16;
    grid[12].y = -3*8;
    //Caixa inicio PF
    grid[13].height = 400;
    grid[13].width = 610;
    grid[13].x = 220;
    grid[13].y = 530;
    //Caixa inicio MARC
    grid[14].width = 384;
    grid[14].height = 384;
    grid[14].x = 1440;
    grid[14].y = 1536;
    //Caixa Parede Cima 1
    grid[15].height = 56;
    grid[15].width = 106;
    grid[15].x = 354;
    grid[15].y = 272;
    //Caixa Parede Cima 2
    grid[16].height = 56;
    grid[16].width = 106;
    grid[16].x = 544;
    grid[16].y = 272;
    //Caixa Parede Cima 3
    grid[17].height = 56;
    grid[17].width = 106;
    grid[17].x = 738;
    grid[17].y = 272;
    //Caixa Parede Cima 4
    grid[18].height = 106;
    grid[18].width = 56;
    grid[18].x = 1890;
    grid[18].y = 272;
    //Caixa Parede Cima 5
    grid[19].height = 106;
    grid[19].width = 56;
    grid[19].x = 1800;
    grid[19].y = 272;
    //Ponte Esquerda
    grid[20].height = 106;
    grid[20].width = 56;
    grid[19].x = 1800;
    grid[19].y = 272;


    }
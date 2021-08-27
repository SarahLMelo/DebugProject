#include "raylib.h"
#include "player.h"
#include "criaturas.h"

Texture2D abrirMapa()
{
    Image mapaPng = LoadImage("Assets/Mapa/mapa2.5.1.png");
    Texture2D mapa = LoadTextureFromImage(mapaPng);
    UnloadImage(mapaPng);
    return mapa;
}
bool checarLimiteCamera();

Vector2 spawnPoints(int i, int width, int height)
{
    Vector2 spawnPointMob[7];
    spawnPointMob[0] = (Vector2){48 * 49, height * 3 - 48 * 13}; //Spawnpoint escada esquerda
    spawnPointMob[1] = (Vector2){48 * 35, height * 3 - 48 * 13}; //Spawnpoint escada direita
    spawnPointMob[2] = (Vector2){48, height + 48 * 9};           //Spawnpoint esquerda tunel
    spawnPointMob[3] = (Vector2){48 * 25, 320};                  //Spawnpoint porta entre caixões
    spawnPointMob[4] = (Vector2){width * 3 - 48 * 15, 320};      //Spawnpoint ponte
    spawnPointMob[5] = (Vector2){width * 3 - 128, 48 * 53};      //Spawnpoint burac obaixo direito
    spawnPointMob[6] = (Vector2){48 * 108, height * 3 - 48 * 3}; //Spawnpoint canto inferior
    return spawnPointMob[i];
}

void ColisionMap(Rectangle grid[], Texture2D mapa)
{
    //Parede da esquerda do mapa
    grid[0].height = mapa.height * 3;
    grid[0].width = 1;
    grid[0].x = 48;
    grid[0].y = 0;
    //Parede de cima do mapa
    grid[1].height = 2;
    grid[1].width = mapa.width * 3;
    grid[1].x = 0;
    grid[1].y = 264;
    //Parede da direita do mapa
    grid[2].height = mapa.height * 3;
    grid[2].width = 1;
    grid[2].x = (mapa.width * 3) - 48;
    grid[2].y = 0;
    //Parede de baixo
    grid[3].height = 2;
    grid[3].width = mapa.width * 3;
    grid[3].x = 0;
    grid[3].y = mapa.height * 3 - 48;
    //Precipicio Baixo Horizontal 1
    grid[4].height = 2;
    grid[4].width = 576;
    grid[4].x = 0;
    grid[4].y = mapa.height * 3 - (16 * 20 * 3);
    //Precipicio Baixo Horizontal 2
    grid[5].height = 2;
    grid[5].width = 528;
    grid[5].x = 576;
    grid[5].y = mapa.height * 3 - (16 * 16 * 3);
    //Precipicio Baixo Horizontal 3
    grid[6].height = 2;
    grid[6].width = 528;
    grid[6].x = (528) * 2;
    grid[6].y = mapa.height * 3 - (16 * 9 * 3);
    //Precipicio Baixo Vertical 1
    grid[7].height = (16 * 4 * 3);
    grid[7].width = 2;
    grid[7].x = 576;
    grid[7].y = mapa.height * 3 - (16 * 20 * 3);
    //Precipicio Baixo Vertical 2
    grid[8].height = (16 * 6 * 4);
    grid[8].width = 2;
    grid[8].x = (552) * 2;
    grid[8].y = mapa.height * 3 - (16 * 16 * 3);
    //Precipicio Baixo Vertical 3
    grid[9].height = (16 * 6 * 4);
    grid[9].width = 2;
    grid[9].x = (528) * 3;
    grid[9].y = mapa.height * 3 - (16 * 9 * 3);
    //Caixona boss inside 1
    grid[10].height = 1080;
    grid[10].width = 3 * 16;
    grid[10].x = 2000;
    grid[10].y = 0;
    //Caixona boss inside 2
    grid[11].height = 1080;
    grid[11].width = 3 * 16;
    grid[11].x = 3328;
    grid[11].y = 0;
    //Caixona boss inside MEIO
    grid[12].height = 1080;
    grid[12].width = 1328;
    grid[12].x = 2000 + 3 * 16;
    grid[12].y = -3 * 8;
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
    grid[20].height = 710;
    grid[20].width = 240;
    grid[20].x = (mapa.width * 3) - (1116);
    grid[20].y = 272;
    //Ponte Direita
    grid[21].height = 672;
    grid[21].width = 2;
    grid[21].x = mapa.width * 3 - 416;
    grid[21].y = 264;
    //Ponte Direita Cima 1
    grid[22].height = 242;
    grid[22].width = 144;
    grid[22].x = mapa.width * 3 - 560;
    grid[22].y = 264;
    //Ponte Direita Cima Quadradin
    grid[23].height = 48;
    grid[23].width = 48;
    grid[23].x = mapa.width * 3 - 464;
    grid[23].y = 512;
    //Ponte Direita Baixo
    grid[24].height = 140;
    grid[24].width = 512;
    grid[24].x = mapa.width * 3 - 560;
    grid[24].y = 828;
    //Ponte Direita Baixo Quadradin
    grid[25].height = 48;
    grid[25].width = 48;
    grid[25].x = mapa.width * 3 - 464;
    grid[25].y = 780;
    //Caixao direita 1
    grid[26].height = 56;
    grid[26].width = 106;
    grid[26].x = mapa.width * 3 - 220;
    grid[26].y = 1192;
    //Caixao direita 2
    grid[27].height = 64;
    grid[27].width = 106;
    grid[27].x = mapa.width * 3 - 222;
    grid[27].y = 1320;
    //Caixao direita 3
    grid[28].width = 106;
    grid[28].height = 56;
    grid[28].x = mapa.width * 3 - 220;
    grid[28].y = 1472;
    //Caixao direita 4
    grid[29].height = 64;
    grid[29].width = 106;
    grid[29].x = mapa.width * 3 - 220;
    grid[29].y = 1604;
    //Buraco inferior direito
    grid[30].height = 240;
    grid[30].width = 240;
    grid[30].x = mapa.width * 3 - 242;
    grid[30].y = 2160;
    //Buraco inferior esquerdo
    grid[31].width = 16 * 3 * 15;
    grid[31].height = 16 * 3 * 12;
    grid[31].x = mapa.width * 3 - 1196;
    grid[31].y = 2160;
    //Buraco inferior direito
    grid[32].width = 16 * 3 * 9;
    grid[32].height = 16 * 3 * 12;
    grid[32].x = mapa.width * 3 - 16 * 3 * 9;
    grid[32].y = mapa.height * 3 - 16 * 3 * 13;
    //Buraco inferior mid fino
    grid[33].width = 16 * 3 * 2;
    grid[33].height = 16 * 3 * 2;
    grid[33].x = mapa.width * 3 - 474;
    grid[33].y = mapa.height * 3 - 16 * 3 * 13;
    //Escada meio 2
    grid[34].width = 48 * 2;
    grid[34].height = 48 * 2;
    grid[34].x = 48 * 52;
    grid[34].y = mapa.height * 3 - 16 * 3 * 14;
    //Escada meio 1
    grid[35].width = 48 * 2;
    grid[35].height = 48 * 2;
    grid[35].x = 48 * 32;
    grid[35].y = mapa.height * 3 - 16 * 3 * 14;
    //Buraco é mais embaixo
    grid[36].width = 48 * 14;
    grid[36].height = 48 * 6;
    grid[36].x = 48 * 91;
    grid[36].y = mapa.height * 3 - 16 * 3 * 6;
    //Buraco é mais embaixo/1
    grid[37].width = 48;
    grid[37].height = 48;
    grid[37].x = 48 * 90;
    grid[37].y = mapa.height * 3 - 16 * 3 * 5;
    //Buraco é mais embaixo/2
    grid[38].width = 48;
    grid[38].height = 48;
    grid[38].x = 48 * 89;
    grid[38].y = mapa.height * 3 - 16 * 3 * 4;
    //Buraco é mais embaixo/3
    grid[39].width = 48;
    grid[39].height = 48;
    grid[39].x = 48 * 88;
    grid[39].y = mapa.height * 3 - 16 * 3 * 3;
    //Buraco é mais embaixo/4
    grid[40].width = 48;
    grid[40].height = 48;
    grid[40].x = 48 * 87;
    grid[40].y = mapa.height * 3 - 16 * 3 * 2;
    //Mesa cima
    grid[41].width = 48 * 5;
    grid[41].height = 56;
    grid[41].x = 48 * 78;
    grid[41].y = 48 * 5 + 32;
    //Mesa baixo
    grid[42].width = 48 * 4;
    grid[42].height = 61;
    grid[42].x = 48 * 65;
    grid[42].y = 48 * 61 - 24;
    //Baldezin
    grid[43].width = 48;
    grid[43].height = 48;
    grid[43].x = 48 * 66;
    grid[43].y = 48 * 62 - 10;
    //Baldezin Extremo Esquerda (PT)
    grid[43].width = 48;
    grid[43].height = 48;
    grid[43].x = 48;
    grid[43].y = 48 * 6;
}
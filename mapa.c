#include "raylib.h"
#include "player.h"
#include "criaturas.h"

Texture2D abrirMapa(){
    Image mapaPng = LoadImage("Assets/Mapa/mapa_v2.0.png");
    Texture2D mapa = LoadTextureFromImage(mapaPng);
    UnloadImage(mapaPng);
    return mapa;
}

bool checarLimiteCamera();

Vector2 spawnPoints();

void ColisionMap();

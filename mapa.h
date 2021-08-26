#include "raylib.h"
#include "player.h"
#include "criaturas.h"

Texture2D abrirMapa();
 
bool checarLimiteCamera();

Vector2 spawnPoints(int i, int width, int height);

void ColisionMap(Rectangle grid[], Texture2D mapa);


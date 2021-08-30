#ifndef GLOSSARIO
#define GLOSSARIO

#include "raylib.h"

void inimigos(Texture2D libelulaverde, Texture2D libelulaamarela, Texture2D libelulavermelha, Texture2D esqueletoimg);

void formas(Texture2D formaazul, Texture2D formaamarela);

void lore();

int mostrarGlossario
            (
            Texture2D botaoLore,
            Texture2D botaoInimigos,
            Texture2D botaoFormas,
            Texture2D botaoVoltar,
            Texture2D libelulaverde,
            Texture2D libelulaamarela,
            Texture2D libelulavermelha,
            Texture2D esqueletoimg,
            Texture2D formaazul,
            Texture2D formaamarela
            );

#endif
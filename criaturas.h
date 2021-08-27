#ifndef CRIATURAS
#define CRIATURAS

#include "raylib.h"
#include "player.h"
#include "armas.h"
#include "animacao.h"

typedef struct
{
    spritesheetCreature animaMorte;
    spritesheetCreature anima;
    int vida, dano, armadura, alguemJaChocou;
    double velocidade;
    Rectangle colisao, pequenaColisao;
} mob;

void criarCriatura(mob *criatura, double posX, double posY);

int bateuNaParede(Rectangle *grid, mob criatura, int quantidadeDeParedes);

int bateuEmOutraCriatura(mob criatura, int i, mob **vetorCriatura, int wave);

void moverCriatura(mob **criatura, int posX, int posY, Rectangle *grid, int quantidadeDeParedes, int wave);

void atingiuOPlayer(mob *criatura, nerdola *player);

void criarWave(int wave, int *qtdCriaturasVivas, mob **criaturas, int w, int h);

int acertouACriatura(bala *projetil, mob **Criaturas, int wave, int *pontuacao);

#endif
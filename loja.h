#ifndef LOJA
#define LOJA

#include "player.h"
#include "raylib.h"

void aumentoDanoPistola(int *modPistola, int *moeda);

void aumentoDanoRifle(int *modRifle, int *moeda);

void aumentoArmadura(nerdola *jogador, int *moeda);

void abrirLoja(int *moeda, int *modPistola, int *modRifle, nerdola *jogador, bala (*armaPrincipal)[], bala (*armaSecundaria)[], int qntdMaxP, int qntdMaxS, int *balasGastasPrincipal, int *balasGastasSec);

#endif
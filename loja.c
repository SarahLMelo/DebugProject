#include "player.h"
#include "raylib.h"

void aumentoDanoPistola(int *modPistola, int *moeda){
    (*modPistola) += 5;
    (*moeda) -= 40;
    return;
}

void aumentoDanoRifle(int *modRifle, int *moeda){
    (*modRifle) += 5;
    (*moeda) -= 25;
    return;
}

void aumentoArmadura(nerdola *jogador, int *moeda){
    (*jogador).armadura += 1;
    (*moeda) -= 20;
}
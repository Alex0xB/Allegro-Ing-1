#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H
#include "personnage.h"
#include"stdbool.h"

void nettoyer_chaine(char* str);

void sauvegarder(t_personnage* personnage);

void draw_large_text(BITMAP* dest, FONT* font, const char* text, int x, int y, int color, float scale);

t_personnage charger(bool *peux_jouer);

#endif //SAUVEGARDE_H
//a
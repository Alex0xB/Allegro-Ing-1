#ifndef NIVEAU1_H
#define NIVEAU1_H
#include "personnage.h"
#include <stdbool.h>

void collision(BITMAP* map,t_personnage* perso,int screen_x);
void jouer_niveau1();
void gerer_mort(t_personnage* perso, bool* fin, int screen_x, bool* fin_echec);
void verifier_fin_scrolling(bool* fin_scrol, BITMAP* niveau1_map, int screen_x, t_personnage* perso);
#endif //NIVEAU1_H

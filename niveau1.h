#ifndef NIVEAU1_H
#define NIVEAU1_H
#include "personnage.h"
#include <stdbool.h>

void chargement_joueur();
void collision(t_personnage* perso, bool* fin, BITMAP* niveau1_map, int screen_x);
void jouer_niveau1();

#endif //NIVEAU1_H

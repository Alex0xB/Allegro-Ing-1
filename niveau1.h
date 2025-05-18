#ifndef NIVEAU1_H
#define NIVEAU1_H
#include "personnage.h"
#include <stdbool.h>

void gerer_collisions(BITMAP* map, t_personnage* perso, int screen_x,bool* bloque_droite_ou_bas);

void verifier_fin_scrolling(bool* fin_scrol, BITMAP* niveau1_map, int screen_x, t_personnage* perso);

void gerer_mort(t_personnage* perso, bool* fin, int screen_x, bool* fin_echec);

void gerer_reussite(t_personnage * perso, bool* fin, bool* fin_reussite, int screen_x);

void ecran_fin_jeu(bool victoire, BITMAP* buffer2);

void jouer_niveau1(BITMAP* buffer);
#endif //NIVEAU1_H

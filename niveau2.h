#ifndef NIVEAU2_H
#define NIVEAU2_H
#include "personnage.h"
#include <stdbool.h>

void gerer_collisions2(BITMAP* map, t_personnage* perso, int screen_x,bool* bloque_droite_ou_bas);

void verifier_fin_scrolling2(bool* fin_scrol, BITMAP* niveau1_map, int screen_x, t_personnage* perso);

void gerer_mort2(t_personnage* perso, bool* fin, int screen_x, bool* fin_echec);

void gerer_reussite2(t_personnage * perso, bool* fin, bool* fin_reussite, int screen_x);

void ecran_fin_jeu2(bool victoire, BITMAP* buffer2, t_personnage* perso);

void jouer_niveau2(BITMAP* buffer, t_personnage* perso);
#endif //NIVEAU2_H

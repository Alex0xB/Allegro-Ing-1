#ifndef NIVEAU3_H
#define NIVEAU3_H
#include "personnage.h"
#include <stdbool.h>

void gerer_collisions3(BITMAP* map, t_personnage* perso, int screen_x,bool* bloque_droite_ou_bas);

void verifier_fin_scrolling3(bool* fin_scrol, BITMAP* niveau1_map, int screen_x, t_personnage* perso);

void gerer_mort3(t_personnage* perso, bool* fin, int screen_x, bool* fin_echec);

void gerer_reussite3(t_personnage * perso, bool* fin, bool* fin_reussite, int screen_x);

void ecran_fin_jeu3(bool victoire, BITMAP* buffer2, t_personnage* perso,SAMPLE* music3,int music_volume);

void afficher_vies3(BITMAP *buffer, BITMAP *coeur, int nb_vies);

void jouer_niveau3(BITMAP* buffer, t_personnage* perso,SAMPLE* music3,int music_volume);
int menu_pause3(BITMAP *buffer2);
#endif //NIVEAU3_H

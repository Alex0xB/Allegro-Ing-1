#ifndef menu_h
#define menu_h
#include "personnage.h"

void draw_menu(BITMAP *buffer,BITMAP *background,BITMAP* bouton_image);
void show_difficulty_menu(BITMAP *buffer,BITMAP *background);
void draw_settings(BITMAP *buffer,BITMAP *background);
void menu(BITMAP *buffer,BITMAP *background,SAMPLE *music, t_personnage* personnage);
#endif
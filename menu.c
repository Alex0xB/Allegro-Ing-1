#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "menu.h"
#include "niveau1.h"
#include "niveau2.h"
#include "niveau3.h"
#include "sauvegarde.h"

#define SCREEN_W 1920
#define SCREEN_H 1080

int music_volume = 128;
int in_settings = 0;
int game_started = 0;
int jeux1 = 0;
int jeux2 = 0;
int jeux3 = 0;

void draw_menu(BITMAP *buffer,BITMAP *background,BITMAP* bouton_image) {
    blit(background, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    rectfill(buffer, SCREEN_W / 2 - 100, SCREEN_H/ 2 - 50, SCREEN_W / 2 + 100, SCREEN_H / 2, makecol(0, 0, 0));
    textout_centre_ex(buffer, font, "Jouer", SCREEN_W / 2, SCREEN_H / 2 - 25, makecol(255, 255, 255), -1);
    rectfill(buffer, SCREEN_W / 2 - 100, SCREEN_H / 2 + 50, SCREEN_W / 2 + 100, SCREEN_H/ 2 + 100, makecol(0, 0, 0));
    textout_centre_ex(buffer, font, "Paramètres", SCREEN_W / 2, SCREEN_H / 2 + 75, makecol(255, 255, 255), -1);
}
void show_difficulty_menu(BITMAP *buffer,BITMAP *background) {
    blit(background, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    rectfill(buffer, SCREEN_W / 2-100, 250, SCREEN_W / 2 + 100, 300, makecol(0, 0, 0));
    textout_centre_ex(buffer, font, "Choisir le niveau", SCREEN_W/ 2, 275, makecol(255, 255, 255), -1);
    rectfill(buffer, SCREEN_W / 2 - 100, 500, SCREEN_W / 2 + 100, 550, makecol(0, 0, 0));
    textout_centre_ex(buffer, font, "Facile ", SCREEN_W / 2, 520, makecol(255, 255, 255), -1);
    rectfill(buffer, SCREEN_W / 2 - 100, 600, SCREEN_W/ 2 + 100, 650, makecol(0, 0, 0));
    textout_centre_ex(buffer, font, "Moyen ", SCREEN_W / 2, 620, makecol(255, 255, 255), -1);
    rectfill(buffer, SCREEN_W / 2 - 100, 700, SCREEN_W / 2 + 100, 750, makecol(0, 0, 0));
    textout_centre_ex(buffer, font, "Difficile ", SCREEN_W / 2, 720, makecol(255, 255, 255), -1);
    rectfill(buffer, SCREEN_W / 2 - 100, 900, SCREEN_W / 2 + 100, 950, makecol(0, 0, 0));
    textout_centre_ex(buffer, font, "retour ", SCREEN_W / 2, 920, makecol(255, 255, 255), -1);
}
void draw_settings(BITMAP *buffer,BITMAP *background) {
    blit(background, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    rectfill(buffer, SCREEN_W / 2 - 100, SCREEN_H / 2 - 125, SCREEN_W / 2 + 100, SCREEN_H/ 2 - 75, makecol(0, 0, 0));
    textout_centre_ex(buffer, font, "Réglages du volume", SCREEN_W / 2, SCREEN_H / 2 - 100, makecol(255, 255, 255), -1);
    char volume_text[20];
    sprintf(volume_text, "Volume: %d", music_volume);
    rectfill(buffer, SCREEN_W / 2 - 50, SCREEN_H / 2 - 60, SCREEN_W / 2 + 50, SCREEN_H/ 2 - 40, makecol(0, 0, 0));
    textout_centre_ex(buffer, font, volume_text, SCREEN_W / 2, SCREEN_H / 2 - 50, makecol(255, 255, 255), -1);
    rectfill(buffer, SCREEN_W / 2 - 125, SCREEN_H / 2, SCREEN_W/ 2 - 75, SCREEN_H / 2 + 25, makecol(0, 0, 0));
    textout_centre_ex(buffer, font, "-", SCREEN_W / 2 - 100, SCREEN_H / 2 + 10, makecol(255, 255, 255), -1);
    rectfill(buffer, SCREEN_W / 2 + 75, SCREEN_H/ 2, SCREEN_W / 2 + 125, SCREEN_H / 2 + 25, makecol(0, 0, 0));
    textout_centre_ex(buffer, font, "+", SCREEN_W / 2 + 100, SCREEN_H / 2 + 10, makecol(255, 255, 255), -1);
    rectfill(buffer, SCREEN_W / 2 - 100, SCREEN_H / 2 + 60, SCREEN_W / 2 + 100, SCREEN_H / 2 + 110, makecol(0, 0, 0));
    textout_centre_ex(buffer, font, "Retour", SCREEN_W / 2, SCREEN_H / 2 + 85, makecol(255, 255, 255), -1);
}
void menu(BITMAP *buffer_menu,BITMAP *background,SAMPLE *music, t_personnage* perso) {
    BITMAP *background2 = load_bitmap("fond_menu2.bmp", NULL);
    BITMAP* bouton_image = load_bitmap("bouton.bmp", NULL);
    SAMPLE *music1 = load_sample("Musique mario bros.wav");
    SAMPLE *music2 = load_sample("michou.wav");
    SAMPLE *music3 = load_sample("kaaris.wav");
    bool peux_jouer = false;
    int music_playing = 0;

    if (!bouton_image) {
        allegro_message("Erreur chargement bouton !");
        exit(1);
    }
    if (!background ) {
        allegro_message("Erreur chargement fond!");
         exit(1);
    }
    if (!music) {
        allegro_message("Erreur chargement musique!");
        exit(1);
    }

    while (!key[KEY_ESC]) {
        if (!music_playing) {
            play_sample(music, music_volume, 128, 1000, 1);
            music_playing = 1;
        }
        clear_bitmap(buffer_menu);
        show_mouse(NULL);
        //Dans cette partie on s'occupe uniquement d'afficher
        if (game_started) {
            if(peux_jouer == false) {
                t_personnage temp = charger(&peux_jouer);
                *perso = temp;
            }
            show_difficulty_menu(buffer_menu, background2);
            if (jeux1) {
                stop_sample(music);
                music_playing = 0;
                jouer_niveau1(buffer_menu, perso,music1,music_volume,music2,music3);
                //allegro_message("Fin de jouer_niveau1()");
                jeux1 = 0;
            } else if (jeux2 && perso->niveau1_fini == 1) {
                stop_sample(music);
                music_playing = 0;
                jouer_niveau2(buffer_menu, perso,music2,music_volume,music3);
                //allegro_message("Fin de jouer_niveau2()");
                jeux2 = 0;
            } else if (jeux3 && perso->niveau2_fini == 1) {
                stop_sample(music);
                music_playing = 0;
                jouer_niveau3(buffer_menu, perso,music3,music_volume);
                //allegro_message("Fin de jouer_niveau3()");
                jeux3 = 0;
            }
        } else if (in_settings) {
            draw_settings(buffer_menu, background);
        } else {
            draw_menu(buffer_menu, background, bouton_image);
        }

        //Dans cette partie on s'occupe de la detection de la souris
        if (mouse_b & 1) {
            //Detection clique gauche de la souris
            if (!in_settings && !game_started) {
                //Menu de base
                if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 && mouse_y > SCREEN_H / 2 - 50 &&
                    mouse_y < SCREEN_H / 2) {
                    //Bouton Jouer
                    game_started = 1;
                }
                if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 && mouse_y > SCREEN_H / 2 + 50 &&
                    mouse_y < SCREEN_H / 2 + 100) {
                    //Bouton Parametre
                    in_settings = 1;
                }
            } else if (in_settings) {
                //Menu des parametres
                if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 && mouse_y > SCREEN_H / 2 + 60 &&
                    mouse_y < SCREEN_H / 2 + 110) {
                    //Bouton Retour
                    in_settings = 0;
                }
                if (mouse_x > SCREEN_W / 2 - 125 && mouse_x < SCREEN_W / 2 - 75 && mouse_y > SCREEN_H / 2 && mouse_y <
                    SCREEN_H / 2 + 25) {
                    //Bouton pour retirer du volume
                    music_volume -= 10;
                    if (music_volume < 0) music_volume = 0;
                    adjust_sample(music, music_volume, 128, 1000, 1);
                }
                if (mouse_x > SCREEN_W / 2 + 75 && mouse_x < SCREEN_W / 2 + 125 && mouse_y > SCREEN_H / 2 && mouse_y <
                    SCREEN_H / 2 + 25) {
                    //Bouton pour ajouter du volume
                    music_volume += 10;
                    if (music_volume > 255) music_volume = 255;
                    adjust_sample(music, music_volume, 128, 1000, 1);
                }
            } else if (game_started) {
                //Menu de jeu
                if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 && mouse_y > 900 && mouse_y < 950) {
                    //Retour
                    game_started = 0;
                }
                if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 && mouse_y > 500 && mouse_y < 550) {
                    //Niveau 1
                    jeux1 = 1;
                }
                if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 && mouse_y > 600 && mouse_y < 650) {
                    //Niveau 2
                    jeux2 = 1;
                }
                if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 && mouse_y > 700 && mouse_y < 750) {
                    //Niveau 3
                    jeux3 = 1;
                }
            }
            rest(100);
        }
        show_mouse(buffer_menu);
        blit(buffer_menu, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
}
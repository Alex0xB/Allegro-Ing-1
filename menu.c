#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "menu.h"

#define SCREEN_W 1920
#define SCREEN_H 1080

int music_volume = 128;
int in_settings = 0;
int game_started = 0;

void draw_menu(BITMAP *buffer,BITMAP *background) {
    draw_sprite(buffer, background, 0, 0);
    rectfill(buffer, SCREEN_W / 2 - 100, SCREEN_H/ 2 - 50, SCREEN_W / 2 + 100, SCREEN_H / 2, makecol(0, 0, 0));
    textout_centre_ex(buffer, font, "Jouer", SCREEN_W / 2, SCREEN_H / 2 - 25, makecol(255, 255, 255), -1);
    rectfill(buffer, SCREEN_W / 2 - 100, SCREEN_H / 2 + 50, SCREEN_W / 2 + 100, SCREEN_H/ 2 + 100, makecol(0, 0, 0));
    textout_centre_ex(buffer, font, "Paramètres", SCREEN_W / 2, SCREEN_H / 2 + 75, makecol(255, 255, 255), -1);
}
void show_difficulty_menu(BITMAP *buffer,BITMAP *background) {
    draw_sprite(buffer, background, 0, 0);
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
    draw_sprite(buffer, background, 0, 0);
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
void menu(BITMAP *buffer,BITMAP *background,SAMPLE *music) {
    if (!background ) {
        allegro_message("Erreur chargement fond!");
         exit(1);
    }
    if (!music) {
        allegro_message("Erreur chargement musique!");
        exit(1);
    }
    play_sample(music, music_volume, 128, 1000, 1);

    while (!key[KEY_ESC]) {
        clear_bitmap(buffer);
        show_mouse(NULL);
        if (game_started) {
            show_difficulty_menu(buffer,background);
        } else if (in_settings) {
            draw_settings(buffer,background);
        } else {
            draw_menu(buffer,background);
        }

        if (mouse_b & 1) {
            if (!in_settings && !game_started) {
                if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 && mouse_y > SCREEN_H / 2 - 50 && mouse_y < SCREEN_H/ 2) {
                    game_started = 1;
                }
                if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 && mouse_y > SCREEN_H / 2 + 50 && mouse_y < SCREEN_H / 2 + 100) {
                    in_settings = 1;
                }
            } else if (in_settings) {
                if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 && mouse_y > SCREEN_H / 2 + 60 && mouse_y < SCREEN_H / 2 + 110) {
                    in_settings = 0;
                }
                if (mouse_x > SCREEN_W / 2 - 125 && mouse_x < SCREEN_W / 2 - 75 && mouse_y > SCREEN_H / 2 && mouse_y < SCREEN_H / 2 + 25) {
                    music_volume -= 10;
                    if (music_volume < 0) music_volume = 0;
                    adjust_sample(music, music_volume, 128, 1000, 1);
                }
                if (mouse_x > SCREEN_W / 2 + 75 && mouse_x < SCREEN_W / 2 + 125 && mouse_y > SCREEN_H / 2 && mouse_y < SCREEN_H / 2 + 25) {
                    music_volume += 10;
                    if (music_volume > 255) music_volume = 255;
                    adjust_sample(music, music_volume, 128, 1000, 1);
                }
            }
            else if(game_started) {
                if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 && mouse_y > 900 && mouse_y < 950) {
                    game_started = 0;
                }
                if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 && mouse_y > 500 && mouse_y < 550) {
                    clear_to_color(buffer, makecol(0, 255, 0));
                }
                if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 && mouse_y > 600 && mouse_y < 650) {
                    clear_to_color(buffer, makecol(0, 0, 255));
                }
                if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 && mouse_y > 700 && mouse_y < 750) {
                    clear_to_color(buffer, makecol(255, 0, 0));
                }
            }
            rest(100);
        }
        show_mouse(buffer);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
}
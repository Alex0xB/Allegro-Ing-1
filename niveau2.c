#include "niveau2.h"

#include "niveau3.h"
#include "stdbool.h"
#include "sauvegarde.h"
#include "personnage.h"

#define SCREEN_W 1920
#define SCREEN_H 1080

extern int game_started;
extern int in_settings;
extern int jeux1;
extern int jeux2;
extern int jeux3;

void gerer_collisions2(BITMAP* map, t_personnage* perso, int screen_x, bool* bloque_droite_ou_bas) {
    int noir = makecol(0, 0, 0);
    int mortel = makecol(1, 0, 0);  // rouge mortel

    int x_map = perso->x + screen_x;
    int y_map = perso->y;
    int w = perso->width;
    int h = perso->height;

    int marge_x = 5;
    int marge_y = 5;

    *bloque_droite_ou_bas = false;

    // --- Collision en haut ---
    if (perso->vy < 0) {
        for (int i = marge_x; i < w - marge_x; i++) {
            int pixel = getpixel(map, x_map + i, y_map - 1);
            if (pixel == noir) {
                perso->vy = 0;
                perso->y += 2;
                break;
            }
            if (pixel == mortel) {
                perso->x = -1000; // déclenche mort par scrolling
                break;
            }
        }
    }

    // --- Collision en bas ---
    if (perso->vy > 0) {
        for (int i = marge_x; i < w - marge_x; i++) {
            int pixel = getpixel(map, x_map + i, y_map + h);
            if (pixel == noir) {
                perso->vy = 0;
                perso->y -= 2;
                *bloque_droite_ou_bas = true;
                break;
            }
            if (pixel == mortel) {
                perso->x = -1000;
                break;
            }
        }
    }

    // --- Collision à droite ---
    if (perso->vx > 0) {
        for (int j = marge_y; j < h - marge_y; j++) {
            int pixel = getpixel(map, x_map + w, y_map + j);
            if (pixel == noir) {
                perso->vx = 0;
                perso->x -= 2;
                *bloque_droite_ou_bas = true;
                break;
            }
            if (pixel == mortel) {
                perso->x = -1000;
                break;
            }
        }
    }

    // --- Collision à gauche ---
    if (perso->vx < 0) {
        for (int j = marge_y; j < h - marge_y; j++) {
            int pixel = getpixel(map, x_map - 1, y_map + j);
            if (pixel == noir) {
                perso->vx = 0;
                perso->x += 2;
                break;
            }
            if (pixel == mortel) {
                perso->x = -1000;
                break;
            }
        }
    }
}
int menu_pause2(BITMAP* buffer2) {
    int choix = 0; // 1 = Reprendre, 2 = Quitter
    bool pause_active = true;

    BITMAP* fond = load_bitmap("ecran_pause.bmp", NULL);
    if (!fond) {
        allegro_message("Erreur de chargement du fond de pause !");
        return 1; // Par défaut : Reprendre
    }

    while (pause_active) {
        // Afficher l'image en fond
        blit(fond, buffer2, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


        // Bouton Reprendre
        rectfill(buffer2, SCREEN_W/2 - 100, SCREEN_H/2 - 30, SCREEN_W/2 + 100, SCREEN_H/2 + 20, makecol(0, 0, 0));
        textout_centre_ex(buffer2, font, "Reprendre", SCREEN_W/2, SCREEN_H/2 - 10, makecol(230, 230, 230), -1);

        // Bouton Quitter
        rectfill(buffer2, SCREEN_W/2 - 100, SCREEN_H/2 + 60, SCREEN_W/2 + 100, SCREEN_H/2 + 110, makecol(0, 0, 0));
        textout_centre_ex(buffer2, font, "Quitter", SCREEN_W/2, SCREEN_H/2 + 80, makecol(180, 180, 220), -1);

        show_mouse(buffer2);
        blit(buffer2, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        // Clique souris
        if (mouse_b & 1) {
            if (mouse_x > SCREEN_W/2 - 100 && mouse_x < SCREEN_W/2 + 100) {
                if (mouse_y > SCREEN_H/2 - 30 && mouse_y < SCREEN_H/2 + 20) {
                    choix = 1; // Reprendre
                    pause_active = false;
                }
                if (mouse_y > SCREEN_H/2 + 60 && mouse_y < SCREEN_H/2 + 110) {
                    choix = 2; // Quitter
                    pause_active = false;
                }
            }
        }

        rest(16);
    }

    destroy_bitmap(fond);
    return choix;
}
void verifier_fin_scrolling2(bool* fin_scrol, BITMAP* niveau1_map, int screen_x, t_personnage* perso) {
    //Cette fonctionnalite est temporairement enleve pcq probleme avec detection
    if(niveau1_map->w - screen_x + 10 <= SCREEN_W) { //permet de verifier que si on atteint la fin du bitmap il n'y ai plus de scrolling
        *fin_scrol = true;
    }
}

void gerer_mort2(t_personnage* perso, bool* fin, int screen_x, bool* fin_reussite) {
    //Mort par scrolling
    if (perso->x + perso->width < 0) {
        perso->nb_mort += 1;
        *fin = true;
        *fin_reussite = false;  // échec
    }
}

void gerer_reussite2(t_personnage * perso, bool* fin, bool* fin_reussite, int screen_x) {
    int x_gauche = 9750;
    int y_haut = 216;
    int y_bas = 429;
    if(screen_x + perso->x + perso->width > x_gauche && perso->y + perso->height < y_bas && perso->y > y_haut ) {
        *fin = true;
        *fin_reussite = true;
    }
}

void ecran_fin_jeu2(bool victoire, BITMAP* buffer2, t_personnage* perso,SAMPLE* music2,int music_volume,SAMPLE* music3) {
    BITMAP* fond = load_bitmap(victoire ? "fond_victoire.bmp" : "game_over.bmp", NULL);

    if (!fond || !buffer2) {
        allegro_message("Erreur de chargement image de fin !");
        return;
    }

    bool fin = false;
    int action = 0;  // 1 = rejouer, 2 = retour

    while (!fin) {
        blit(fond, buffer2, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        // --- Bouton REJOUER ---
        rectfill(buffer2, SCREEN_W / 2 - 100, 700, SCREEN_W / 2 + 100, 750, makecol(0, 0, 0));
        textout_centre_ex(buffer2, font, "REJOUER", SCREEN_W / 2, 720, makecol(255, 255, 255), -1);

        // --- Bouton RETOUR ---
        rectfill(buffer2, SCREEN_W / 2 - 100, 900, SCREEN_W / 2 + 100, 950, makecol(0, 0, 0));
        textout_centre_ex(buffer2, font, "RETOUR", SCREEN_W / 2, 920, makecol(255, 255, 255), -1);

        // Gestion clic
        if (mouse_b & 1) {
            if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100) {
                if (mouse_y > 700 && mouse_y < 750) {
                    action = 1;  // REJOUER
                    fin = true;
                }
                if (mouse_y > 900 && mouse_y < 950) {
                    action = 2;  // RETOUR
                    fin = true;
                }
            }
        }

        show_mouse(buffer2);
        blit(buffer2, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(16);
    }

    destroy_bitmap(fond);

    if (action == 1) {
        jouer_niveau2(buffer2, perso,music2,music_volume,music3);  // On rejoue le niveau
    }
    // Sinon, on revient dans le menu des niveaux (rien à faire, ça reprend dans menu())
}

void afficher_vies2(BITMAP *buffer, BITMAP *coeur, int nb_vies) {
    if (nb_vies > 3) nb_vies = 3;

    for (int i = 0; i < nb_vies; i++) {
        draw_sprite(buffer, coeur, SCREEN_W - 60 - i * 50, 20);
    }
}

void jouer_niveau2(BITMAP* buffer2, t_personnage* perso,SAMPLE* music2,int music_volume,SAMPLE* music3) {
    bool fin = false;
    bool fin_scrol = false;
    int screen_x = 0;
    int screen_y = 0;
    int pause_action;
    int touche_appuyer = 0;
    bool bloque_droite_ou_bas = false;

    bool fin_reussite = false;
    int x_accel_niveau2 = 1667; //3
    int y_accel_niveau2 = 241;
    int bonus_accel_touche = 0;
    play_sample(music2, music_volume, 128, 1000, 1);
    // Initialisation personnage
    initialiserPersonnage(perso, 100, 300, 0.6); // Position fixe x = 100
    if (perso->nb_vies > 3 || perso->nb_vies < 1) perso->nb_vies = 3;
    chargerSprites(perso);

    // Chargement de la map et du buffer
    BITMAP *niveau2_map = load_bitmap("decor2.bmp", NULL);
    BITMAP *coeur = load_bitmap("coeur.bmp", NULL);

    //Objet speciaux
    chargerObjetsSpeciaux();
    afficherObjetsSpeciaux_niveau2(niveau2_map);

    // Boucle de jeu
    while (!fin) {
        // --- Début du jeu après appui sur espace ---
        if (touche_appuyer == 1) {
            if (!key[KEY_SPACE]) {
                // Gravité naturelle
                perso->vy = 10;
                //perso.vx = 0;
            }

            // Animation du personnage
            animerPersonnage(perso);
        }

        // Dessin du décor
        blit(niveau2_map, buffer2, screen_x, screen_y, 0, 0, SCREEN_W, SCREEN_H);

        // Dessin du personnage
        dessinerPersonnage(perso, buffer2);

        //Dessin coeur
        afficher_vies2(buffer2, coeur, perso->nb_vies);

        // Affichage du buffer à l’écran
        blit(buffer2, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        // Gestion clavier
        if (key[KEY_SPACE]) {
            touche_appuyer = 1;
            perso->vy = -10;
            //perso.vx = 0;
        }

        // Gestion du scrolling : il avance TOUJOURS
        if (touche_appuyer == 1 && !fin_scrol) {
            screen_x += 5;

            if (bloque_droite_ou_bas) {
                perso->vx = -5; // le scrolling avance, on compense
            } else if (bonus_accel_touche == 0) {
                perso->vx = 0; // pas de compensation
            }
        }

        if (bonus_accel_touche == 0 &&
            screen_x + perso->x + perso->width > x_accel_niveau2 &&
            screen_x + perso->x + perso->width < x_accel_niveau2 + 80 &&
            perso->y + perso->height > y_accel_niveau2 &&
            perso->y < y_accel_niveau2 + 78) {
            activerMalusAcceleration(perso);
            bonus_accel_touche = 1;
        }
        if (screen_x + perso->x + perso->width > 2100) {
            //fin acceleration
            bonus_accel_touche = 0;
        }

        if (fin_scrol) {
            perso->vx = 5; // ou 0 si tu veux qu'il reste immobile
        }

        // Gestion des collisions
        gerer_collisions2(niveau2_map, perso, screen_x, &bloque_droite_ou_bas);
        gerer_mort2(perso, &fin, screen_x, &fin_reussite);
        gerer_reussite2(perso, &fin, &fin_reussite, screen_x);
        // Pause : clic droit ou touche P
        if (key[KEY_ESC]) {
            pause_action = menu_pause2(buffer2);

            if (pause_action == 2) {
                fin = true;
            }

            rest(200); // anti double-clic
        }
        // Mise à jour de la position
        perso->x += perso->vx;
        perso->y += perso->vy;

        // Gestion souris (pause future)
        if (mouse_b & 1) {
            // Pause ou autre fonctionnalité
        }

        // Cadence
        rest(16);
    }

    // Nettoyage
    libererSprites(perso);
    libererObjetsSpeciaux();
    destroy_bitmap(niveau2_map);
    destroy_bitmap(coeur);

    if (fin_reussite) {
        perso->niveau1_fini = 1;
        perso->nb_niveau += 1;
        sauvegarder(perso);
        stop_sample(music2);
        jouer_niveau3(buffer2, perso,music3,music_volume);
    } else {
        perso->nb_vies--;

        if (perso->nb_vies <= 0) {
            stop_sample(music2);
            ecran_fin_jeu2(false, buffer2, perso,music2,music_volume,music3);
        }else if(pause_action == 2) {
            stop_sample(music2);
        }
        else {
            stop_sample(music2);
            jouer_niveau2(buffer2, perso,music2,music_volume,music3); // relancer avec une vie en moins
        }
    }

}

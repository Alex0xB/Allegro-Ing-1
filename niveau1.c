#include "niveau1.h"
#include "stdbool.h"
#include "sauvegarde.h"
#include "personnage.h"

#define SCREEN_W 1920
#define SCREEN_H 1080

void chargement_joueur() {
    //Afficher une interface pour recuperer ou creer un compte

}

void gerer_collisions(BITMAP* map, t_personnage* perso, int screen_x,
                      bool* bloque_droite_ou_bas) {
    int noir = makecol(0, 0, 0);
    int x_map = perso->x + screen_x;
    int y_map = perso->y;
    int w = perso->width;
    int h = perso->height;

    *bloque_droite_ou_bas = false;

    // Collision en haut (bloque uniquement la montée)
    if (perso->vy < 0) {
        for (int i = 0; i < w; i++) {
            if (getpixel(map, x_map + i, y_map) == noir) {
                perso->vy = 0;
                break;
            }
        }
    }

    // Collision en bas (bloque uniquement la descente)
    if (perso->vy > 0) {
        for (int i = 0; i < w; i++) {
            if (getpixel(map, x_map + i, y_map + h - 1) == noir) {
                perso->vy = 0;
                *bloque_droite_ou_bas = true;
                break;
            }
        }
    }

    // Collision à droite (bloque tout)
    for (int j = 0; j < h; j++) {
        if (getpixel(map, x_map + w - 1, y_map + j) == noir) {
            perso->vx = 0;
            perso->vy = 0;
            *bloque_droite_ou_bas = true;
            break;
        }
    }
}







void verifier_fin_scrolling(bool* fin_scrol, BITMAP* niveau1_map, int screen_x, t_personnage* perso) {
    if(niveau1_map->w - screen_x + 10 <= SCREEN_W) { //permet de verifier que si on atteint la fin du bitmap il n'y ai plus de scrolling
        *fin_scrol = true;
    }
}

void jouer_niveau1() {
    bool fin = false;
    bool fin_scrol = false;
    t_personnage perso;
    int screen_x = 0;
    int screen_y = 0;
    int touche_appuyer = 0;
    bool bloque_droite_ou_bas = false;


    // Chargement joueur
    chargement_joueur();

    // Initialisation personnage
    initialiserPersonnage(&perso, 100, 300, 0.6);  // Position fixe x = 100
    chargerSprites(&perso);

    // Chargement de la map et du buffer
    BITMAP* niveau1_map = load_bitmap("decor1.bmp", NULL);
    BITMAP* buffer2 = create_bitmap(SCREEN_W, SCREEN_H);

    //Objet speciaux
    chargerObjetsSpeciaux();
    afficherObjetsSpeciaux(niveau1_map);

    // Boucle de jeu
    while (!fin) {
        // --- Début du jeu après appui sur espace ---
        if (touche_appuyer == 1) {
            if (!key[KEY_SPACE]) {
                // Gravité naturelle
                perso.vy = 10;
                perso.vx = 0;
            }

            // Animation du personnage
            animerPersonnage(&perso);
        }

        // Vérifie la fin du scrolling
        verifier_fin_scrolling(&fin_scrol, niveau1_map, screen_x, &perso);

        // Dessin du décor
        blit(niveau1_map, buffer2, screen_x, screen_y, 0, 0, SCREEN_W, SCREEN_H);

        // Dessin du personnage
        dessinerPersonnage(&perso, buffer2);

        // Affichage du buffer à l’écran
        blit(buffer2, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        // Gestion clavier
        if (key[KEY_SPACE]) {
            touche_appuyer = 1;
            perso.vy = -10;
            perso.vx = 0;
        }

        // Gestion du scrolling : il avance TOUJOURS
        if (touche_appuyer == 1 && !fin_scrol) {
            screen_x += 5;

            if (bloque_droite_ou_bas) {
                perso.vx = -5; // le scrolling avance, on compense
            } else {
                perso.vx = 0;  // pas de compensation
            }
        }

        if (fin_scrol) {
            perso.vx = 5; // ou 0 si tu veux qu'il reste immobile
        }

        // Gestion des collisions
        gerer_collisions(niveau1_map, &perso, screen_x, &bloque_droite_ou_bas);

        // Mise à jour de la position
        perso.x += perso.vx;
        perso.y += perso.vy;

        // Gestion souris (pause future)
        if (mouse_b & 1) {
            // Pause ou autre fonctionnalité
        }

        // Cadence
        rest(16);
    }

    // Nettoyage
    libererSprites(&perso);
    libererObjetsSpeciaux();
    destroy_bitmap(niveau1_map);
    destroy_bitmap(buffer2);
}

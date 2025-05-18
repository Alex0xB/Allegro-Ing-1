#include <allegro.h>
#include "decor.h"

static BITMAP *decor = NULL;

// Chemins relatifs à cmake-build-debug (pas besoin de "images/")
#define FICHIER_DECOR1 "decor1.bmp"
#define FICHIER_DECOR2 "decor2.bmp"
#define FICHIER_DECOR3 "decor3.bmp"

void charger_decor1() {
    decor = load_bitmap(FICHIER_DECOR1, NULL);
    if (!decor) {
        allegro_message("Erreur : impossible de charger decor1.bmp !");
        exit(EXIT_FAILURE);
    }
}

void charger_decor2() {
    decor = load_bitmap(FICHIER_DECOR2, NULL);
    if (!decor) {
        allegro_message("Erreur : impossible de charger decor2.bmp !");
        exit(EXIT_FAILURE);
    }
}

void charger_decor3() {
    decor = load_bitmap(FICHIER_DECOR3, NULL);
    if (!decor) {
        allegro_message("Erreur : impossible de charger decor3.bmp !");
        exit(EXIT_FAILURE);
    }
}

void afficher_decor() {
    if (decor) {
        blit(decor, screen, 0, 0, 0, 0, decor->w, decor->h);
    }
}

void detruire_decor() {
    if (decor) {
        destroy_bitmap(decor);
        decor = NULL;
    }
}

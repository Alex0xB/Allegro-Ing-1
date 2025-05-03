 #include <allegro.h>
#include "decor.h"

static BITMAP *decor = NULL;

#define FICHIER_DECOR "decor1.bmp"

void charger_decor() {
    decor = load_bitmap(FICHIER_DECOR, NULL);
    if (!decor) {
        allegro_message("Erreur : impossible de charger le décor !");
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

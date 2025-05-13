#include <allegro.h>
#include "decor.h"

static BITMAP *decor = NULL;

void charger_decor(int numero) {
    const char *fichier = NULL;

    if (numero == 1) {
        fichier = "images/decor1.bmp";
    } else if (numero == 2) {
        fichier = "images/decor2.bmp";
    } else {
        allegro_message("Numéro de décor invalide !");
        exit(EXIT_FAILURE);
    }

    decor = load_bitmap(fichier, NULL);
    if (!decor) {
        allegro_message("Erreur : échec du chargement du décor !");
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

#include "personnage.h"
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>

void initialiserPersonnage(t_personnage *p, float x, float y, float lift) {
    p->x = x;
    p->y = y;
    p->vy = 0;
    p->lift = lift;
    p->width = 0;
    p->height = 0;
    p->isAlive = 1;
    p->spriteIndex = 0;
    p->animationTimer = 0;
    p->animationSpeed = 5; // 5 frames entre chaque sprite
}

void chargerSprites(t_personnage *p, int nombre) {
    p->spriteCount = nombre;

    for (int i = 0; i < nombre; i++) {
        char nomFichier[100];
        sprintf(nomFichier, "spritevol%d.bmp", i);
        p->sprites[i] = load_bitmap(nomFichier, NULL);

        if (p->sprites[i] == NULL) {
            allegro_message("Erreur de chargement du sprite : %s", nomFichier);
            exit(EXIT_FAILURE);
        }
    }

    p->width = p->sprites[0]->w;
    p->height = p->sprites[0]->h;
}

void animerPersonnage(t_personnage *p) {
    p->animationTimer++;
    if (p->animationTimer >= p->animationSpeed) {
        p->spriteIndex = (p->spriteIndex + 1) % p->spriteCount;
        p->animationTimer = 0;
    }
}

void dessinerPersonnage(t_personnage *p, BITMAP *buffer) {
    draw_sprite(buffer, p->sprites[p->spriteIndex], p->x, p->y);
}

void libererSprites(t_personnage *p) {
    for (int i = 0; i < p->spriteCount; i++) {
        destroy_bitmap(p->sprites[i]);
    }
}

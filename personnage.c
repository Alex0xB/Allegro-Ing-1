#include "personnage.h"
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>

BITMAP *objetsSpeciaux[4];


void initialiserPersonnage(t_personnage *p, float x, float y, float lift) {
    p->x = x;
    p->y = y;
    p->vx = 0;
    p->vy = 0;
    p->lift = lift;
    p->width = 0;
    p->height = 0;
    p->spriteIndex = 0;
    p->animationTimer = 0;
    p->animationSpeed = 5; // 5 frames entre chaque sprite
}

void chargerSprites(t_personnage *p) {
    p->spriteCount = 4;
    const char *nomsFichiers[4] = {
        "spritevol1.bmp",
        "spritevol2.bmp",
        "spritevol3.bmp",
        "spritevol4.bmp"
    };

    for (int i = 0; i < p->spriteCount; i++) {
        p->sprites[i] = load_bitmap(nomsFichiers[i], NULL);
        if (p->sprites[i] == NULL) {
            allegro_message("Erreur de chargement du sprite : %s", nomsFichiers[i]);
            exit(EXIT_FAILURE);
        }
    }

    // On suppose que tous les sprites ont la même taille
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

BITMAP *objetsSpeciaux[4];

void chargerObjetsSpeciaux() {
    const char *nomsObjets[4] = {
        "sprite clonage magenta .bmp",
        "sprite gravite bmp.bmp",
        "sprite ralenti bmp.bmp",
        "sprite accel bmp2.bmp"
    };

    for (int i = 0; i < 4; i++) {
        objetsSpeciaux[i] = load_bitmap(nomsObjets[i], NULL);
        if (objetsSpeciaux[i] == NULL) {
            allegro_message("Erreur de chargement du sprite : %s", nomsObjets[i]);
            exit(EXIT_FAILURE);
        }
    }
}
void afficherObjetsSpeciaux_niveau2(BITMAP *buffer) {
    int x_accel_niveau2 = 1667; //3
    int y_accel_niveau2 = 241;

    draw_sprite(buffer, objetsSpeciaux[3], x_accel_niveau2, y_accel_niveau2);
}
void afficherObjetsSpeciaux_niveau3(BITMAP *buffer) {

    int x_gravite_niveau3 = 1638;//1
    int y_gravite_niveau3 = 236;

    int x_ralenti_niveau3 = 5525;//2
    int y_ralenti_niveau3 = 262;

    draw_sprite(buffer, objetsSpeciaux[1], x_gravite_niveau3, y_gravite_niveau3); //gravite

    draw_sprite(buffer, objetsSpeciaux[2], x_ralenti_niveau3, y_ralenti_niveau3);//ralenti
}

void libererObjetsSpeciaux() {
    for (int i = 0; i < 4; i++) {
        destroy_bitmap(objetsSpeciaux[i]);
    }
}

void activerBonusRalentissement(t_personnage *p) {
    p->vx = -3; // Compense plus fort le scroll (ralenti perçu)
}

void activerMalusAcceleration(t_personnage *p) {
    p->vx = 10; // Compensation moins forte → scroll paraît plus rapide
}

void activerMalusGravite(int* valeur) {
    *valeur = 3; // Tombe plus vite
}
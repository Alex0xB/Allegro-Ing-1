#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <allegro.h>

typedef struct {
    float x, y;              // Position du personnage
    float vy;                // Vitesse verticale (vol / chute)
    float lift;              // Force vers le haut quand on appuie sur espace
    int width, height;       // Dimensions du sprite

    int isAlive;             // 1 = vivant, 0 = mort
    int spriteIndex;         // Frame actuelle de l’animation
    int spriteCount;         // Nombre de sprites utilisés
    int animationTimer;      // Pour gérer l’animation

    BITMAP *sprites[10];     // Tableau simple de sprites (max 10)
} Personnage;

#endif //PERSONNAGE_H

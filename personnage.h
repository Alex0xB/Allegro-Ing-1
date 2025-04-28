#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <allegro.h>

typedef struct {
    float x, y;              // Position
    float vy;                // Vitesse verticale
    float lift;              // Force vers le haut (espace)
    int width, height;       // Dimensions du sprite

    int isAlive;             // 1 = vivant, 0 = mort
    int spriteIndex;         // Index de l’image actuelle
    int spriteCount;         // Nombre total de sprites
    int animationTimer;      // Compteur pour animation
    int animationSpeed;      // Frames entre chaque image
    char nom[100];
    int nb_mort;
    int nb_niveau;

    BITMAP *sprites[10];     // Tableau de sprites (max 10)
} t_personnage;

// Fonctions
void initialiserPersonnage(t_personnage *p, float x, float y, float lift);
void chargerSprites(t_personnage *p);
void animerPersonnage(t_personnage *p);
void dessinerPersonnage(t_personnage *p, BITMAP *buffer);
void libererSprites(t_personnage *p);
#endif //PERSONNAGE_H

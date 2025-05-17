#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <allegro.h>
#include <stdbool.h>

typedef struct {
    int x, y;              // Position
    float vx,vy;                // Vitesse verticale
    float lift;              // Force vers le haut (espace)
    int width, height;       // Dimensions du sprite

    int spriteIndex;         // Index de l’image actuelle
    int spriteCount;         // Nombre total de sprites
    int animationTimer;      // Compteur pour animation
    int animationSpeed;      // Frames entre chaque image
    char nom[100];
    int nb_mort;
    int nb_niveau;
    int niveau1_fini;
    int niveau2_fini;
    int niveau3_fini;

    BITMAP *sprites[10];     // Tableau de sprites (max 10)
} t_personnage;

// Fonctions
void chargerObjetsSpeciaux();
void afficherObjetsSpeciaux(BITMAP *buffer);
void libererObjetsSpeciaux();
void initialiserPersonnage(t_personnage *p, float x, float y, float lift);
void chargerSprites(t_personnage *p);
void animerPersonnage(t_personnage *p);
void dessinerPersonnage(t_personnage *p, BITMAP *buffer);
void libererSprites(t_personnage *p);
#endif //PERSONNAGE_H

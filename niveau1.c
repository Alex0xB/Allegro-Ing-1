#include "niveau1.h"
#include "stdbool.h"
#include "sauvegarde.h"
#include "personnage.h"

#define SCREEN_W 1920
#define SCREEN_H 1080

void chargement_joueur() {
    //Afficher une interface pour recuperer ou creer un compte

}

void collision(BITMAP* map,t_personnage* perso,int screen_x) {
    int noir = makecol(0, 0, 0); // couleur noire

    // Position du personnage dans la MAP complète (pas l'écran)
    int x_map = perso->x + screen_x;
    int y_map = perso->y;

    // Taille du sprite
    int w = perso->width;
    int h = perso->height;

    // On vérifie les 4 coins du sprite
    int points[4][2] = {
        {x_map, y_map},                   // Haut gauche
        {x_map + w - 1, y_map},           // Haut droit
        {x_map, y_map + h - 1},           // Bas gauche
        {x_map + w - 1, y_map + h - 1}    // Bas droit
    };

    for (int i = 0; i < 4; i++) {
        int px = points[i][0];
        int py = points[i][1];

        if (px >= 0 && px < map->w && py >= 0 && py < map->h) {
            int color = getpixel(map, px, py);
            if (color == noir) {
                // Collision détectée
                perso->vx = 0;  // Bloque le mouvement horizontal
                perso->vy = 0;
                return;
            }
        }
    }
}


void verifier_fin_scrolling(bool* fin_scrol, BITMAP* niveau1_map, int screen_x, t_personnage* perso) {
    if(niveau1_map->w - screen_x + 10 <= SCREEN_W) { //permet de verifier que si on atteint la fin du bitmap il n'y ai plus de scrolling
        *fin_scrol = true;
        perso->x += 5;
    }
}

void jouer_niveau1() {
    //variable
    bool fin = false;
    bool fin_scrol = false;;
    t_personnage perso;
    int screen_x= 0;
    int screen_y = 0;
    int touche_appuyer = 0; //permet de s'assurer que le jeu se lance lorsque l'utilisateur appui sur la touche espace

    //Partie sur le chargement du joueur
    chargement_joueur();

    //Partie sur l'initialisation du personnage
    initialiserPersonnage(&perso, 100, 300, 0.6);
    chargerSprites(&perso);

    //Chargement de la map
    BITMAP* niveau1_map = load_bitmap("decor1.bmp", NULL);
    BITMAP* buffer2 = create_bitmap(SCREEN_W, SCREEN_H);

    //Debut du jeux
    while(fin == false) {

        //On fait bouger notre personnage
        if(touche_appuyer == 1) {
            if(!key[KEY_SPACE]) {
                //1- Deplacer notre personnage
                perso.vy = 10; //Le personnage chute quand on n'appui pas sur la touche espace
                perso.vx = 0;
                //2- On fait bouger le perso
                perso.x += perso.vx;
                perso.y += perso.vy;
                collision(niveau1_map,&perso,screen_x);
            }

            //4- Animer le personnage
            animerPersonnage(&perso);
        }

        //5- Fin scrolling
        verifier_fin_scrolling(&fin_scrol, niveau1_map, screen_x, &perso);

        //6- Copier la portion visible du décor dans le buffer
        blit(niveau1_map, buffer2, screen_x, screen_y, 0, 0, SCREEN_W, SCREEN_H);
        animerPersonnage(&perso);
        //7- Dessiner le personnage dans le buffer (par-dessus le décor)
        dessinerPersonnage(&perso,buffer2);

        //8- Copier le buffer vers l'écran
        blit(buffer2, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        //Partie sur la detection au clavier
        if(key[KEY_SPACE]) {
            touche_appuyer = 1;
            perso.vy = 10;
            perso.vx = 0;
            perso.x += perso.vx;
            perso.y -= perso.vy;
            collision(niveau1_map,&perso,screen_x);
        }
        //Partie sur la detection a la souris
        if (mouse_b & 1) {
            //Verifier si on appui sur le bouton pour mettre en pause le jeux
        }
        if(touche_appuyer == 1 && fin_scrol == false) { //Le scrolling ne se lance que si le joueur a appuyer sur la touche espace au debut
            screen_x += 5;
        }
        rest(16);
    }
    libererSprites(&perso);
}
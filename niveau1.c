#include "niveau1.h"
#include "stdbool.h"
#include "sauvegarde.h"
#include "personnage.h"

#define SCREEN_W 1920
#define SCREEN_H 1080

void chargement_joueur() {
    //Afficher une interface pour recuperer ou creer un compte

}

void collision(t_personnage* perso, bool* fin, BITMAP* niveau1_map, int screen_x) {
    // Obtenir les coordonnées des coins du personnage (haut, bas, gauche, droite)
    int x_gauche = perso->x;
    int x_droite = perso->x + perso->width; // Largeur du personnage
    int y_haut = perso->y;
    int y_bas = perso->y + perso->height;  // Hauteur du personnage

    // Variables pour vérifier les conditions de collision sur chaque côté du personnage
    bool collision_haut = false;
    bool collision_bas = false;

    // Vérification de la collision avec l'image (niveau1_map)
    for (int y = y_haut; y < y_bas; y++) {
        for (int x = x_gauche; x < x_droite; x++) {
            // Vérifier la couleur des pixels
            int pixel = getpixel(niveau1_map, x, y);  // Fonction qui récupère la couleur d'un pixel
            int r = (pixel >> 16) & 0xFF;
            int g = (pixel >> 8) & 0xFF;
            int b = pixel & 0xFF;

            // Condition 1 : Si on touche la couleur RGB(0, 0, 0) (obstacle)
            if (r == 0 && g == 0 && b == 0) {
                // Si la tête du personnage touche l'obstacle (partie supérieure)
                if (y == y_haut) {
                    collision_haut = true;
                }
                // Si le bas du personnage touche l'obstacle (partie inférieure)
                if (y == y_bas - 1) {
                    collision_bas = true;
                }
                // Si on touche un obstacle sur les bords, on arrête le mouvement
                perso->vx = 0;
                perso->vy = 0;  // Le personnage ne peut plus se déplacer
            }

            // Condition 2 : Si on touche la couleur RGB(1, 1, 1) (zone mortelle)
            if (r == 1 && g == 1 && b == 1) {
                fin = true;  // Le personnage meurt
            }

            // Condition 4 : Si on touche la couleur RGB(255, 255, 255) (fin du niveau)
            if (r == 255 && g == 255 && b == 255) {
                fin = true;  // Le niveau est terminé
            }
        }
    }

    // Condition 3 : Si le personnage sort du décor (gauche)
    if (perso->x < screen_x) {
        fin = true;  // Le personnage meurt s'il sort à gauche
    }

    // Si la tête ou le bas du personnage touche un obstacle, il s'arrête
    if (collision_haut || collision_bas) {
        perso->vx = 0;
        perso->vy = 0;  // Empêche toute avancée ou chute supplémentaire
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

                //2- On fait bouger le perso
                perso.x += perso.vx;
                perso.y += perso.vy;
            }

            //3- Verifier la collision
            collision(&perso, &fin, niveau1_map, screen_x);

            //4- Animer le personnage
            animerPersonnage(&perso);
        }

        //5- Fin scrolling
        verifier_fin_scrolling(&fin_scrol, niveau1_map, screen_x, &perso);

        //6- Copier la portion visible du décor dans le buffer
        blit(niveau1_map, buffer2, screen_x, screen_y, 0, 0, SCREEN_W, SCREEN_H);

        //7- Dessiner le personnage dans le buffer (par-dessus le décor)
        draw_sprite(buffer2, perso.sprites[perso.spriteIndex], perso.x, perso.y);

        //8- Copier le buffer vers l'écran
        blit(buffer2, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        //Partie sur la detection au clavier
        if(key[KEY_SPACE]) {
            touche_appuyer = 1;
            perso.vy = 10;

            //2- On fait bouger le perso
            perso.x += perso.vx;
            perso.y -= perso.vy;
        }
        //Partie sur la detection a la souris
        if (mouse_b & 1) {
            //Verifier si on appui sur le bouton pour mettre en pause le jeux
        }
        if(touche_appuyer == 1 && fin_scrol == false) { //Le scrolling ne se lance que si le joueur a appuyer sur la touche espace au debut
            screen_x += 50;
        }
        rest(16);
    }
    libererSprites(&perso);
}
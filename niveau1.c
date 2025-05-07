#include "niveau1.h"
#include "stdbool.h"
#include "sauvegarde.h"
#include "personnage.h"

#define SCREEN_W 1920
#define SCREEN_H 1080

void chargement_joueur() {
    //Afficher une interface pour recuperer ou creer un compte

}

void collision(t_personnage* perso) {
    /**
    if() { //Plafond

    }
    else if() { //Sol

    }
    else if() { //Bordure du scrolling

    }
    else if() { //Si je touche la fin du jeu

    }
    else if() { //Si je touche un objet mortel

    }
    else if() { //Si je touche un bonus

    }
    else if() { //Si je touche un malus

    }
    **/
}

void verifier_fin_scrolling(bool* fin_scrol, BITMAP* niveau1_map, int screen_x) {
    if(niveau1_map->w - screen_x + 10 <= SCREEN_W) { //permet de verifier que si on atteint la fin du bitmap il n'y ai plus de scrolling
        *fin_scrol = true;
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
            //1- Deplacer notre personnage
            perso.vx = 1; //Le personage continue d'avancer meme quand il n'a plus de vitesse
            perso.vy = 10; //Le personnage chute quand on n'appui pas sur la touche espace

            perso.x += perso.vx;
            perso.y += perso.vy;

            //2- Verifier la collision
            collision(&perso);

            //3- Animer le personnage
            animerPersonnage(&perso);
        }

        //4- Afficher le personnage
        dessinerPersonnage(&perso, niveau1_map);

        //5- Fin scrolling
        verifier_fin_scrolling(&fin_scrol, niveau1_map, screen_x);

        //On affiche notre map
        blit(niveau1_map, buffer2,screen_x,screen_y,0,0,niveau1_map->w, niveau1_map->h );
        blit(buffer2, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
        clear_to_color(screen, makecol(0, 0, 0));

        //Partie sur la detection au clavier
        if(key[KEY_SPACE]) {
            touche_appuyer = 1;
            perso.vx = 7;
            perso.vy = 15;
            perso.x += perso.vx;
            perso.y -= perso.vy;
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
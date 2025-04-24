#include <stdio.h>
#include <allegro.h>
#include "sauvegarde.h"
#include "personnage.h"
#define SCREEN_W 1920
#define SCREEN_H 1080

t_personnage perso;


void initialisation_allegro() {
    allegro_init(); // appel obligatoire (var.globales, recup. infos syst me ...)
    install_keyboard(); //pour utiliser le clavier
    install_mouse(); //pour utiliser la souris
    //pour choisir la profondeur de couleurs (8,16,24 ou 32 bits)
    set_color_depth(desktop_color_depth()); //ici : identique à celle du bureau

    //sélection du mode graphique
    // avec choix d'un driver+mode+résolution de l'écran
    /// si échec, le programme s'arrête
    if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,SCREEN_W,SCREEN_H,0,0)!=0)
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

int main() {
    initialisation_allegro();  // ← Ici !

    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    if (exists("spritevol1.bmp")) {
        allegro_message("Le fichier spritevol1.bmp est bien trouvé !");
    } else {
        allegro_message("Fichier introuvable : spritevol1.bmp");
    }

    initialiserPersonnage(&perso, 100, 300, 0.6);

    chargerSprites(&perso);

    while (!key[KEY_ESC]) {
        if (key[KEY_SPACE]) {
            perso.vy -= perso.lift;
        }
        perso.vy += 0.3;
        perso.y += perso.vy;

        animerPersonnage(&perso);

        clear(buffer);
        dessinerPersonnage(&perso, buffer);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(20);
    }

    libererSprites(&perso);
    destroy_bitmap(buffer);
    return 0;
}END_OF_MAIN();
//oueoeue
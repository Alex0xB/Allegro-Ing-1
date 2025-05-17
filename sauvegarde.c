#include <stdio.h>
#include "sauvegarde.h"
#include "personnage.h"
#include <stdbool.h>
#include <string.h>

void sauvegarder(t_personnage* personnage) {
    char nom_txt[100];
    strcpy(nom_txt, personnage->nom);
    strcat(nom_txt, ".txt");

    FILE* pt = fopen(nom_txt, "w"); //on ouvre notre ficher avec le nom du personnage avec un .txt

    fprintf(pt, "%s\n", personnage->nom);
    fprintf(pt, "%d\n", personnage->nb_mort);
    fprintf(pt, "%d\n", personnage->nb_niveau);
    fprintf(pt, "%d\n", personnage->niveau1_fini);
    fprintf(pt, "%d\n", personnage->niveau2_fini);
    fprintf(pt, "%d\n", personnage->niveau3_fini);
    fclose(pt);
}

void draw_large_text(BITMAP* dest, FONT* font, const char* text, int x, int y, int color, float scale) {
    int text_w = text_length(font, text);
    int text_h = text_height(font);

    BITMAP* temp = create_bitmap(text_w, text_h);
    clear_to_color(temp, makecol(255, 0, 255)); // magenta utilisé comme couleur transparente

    // Dessin du texte avec fond magenta
    textout_ex(temp, font, text, 0, 0, color, makecol(255, 0, 255));

    int w = text_w * scale;
    int h = text_h * scale;

    BITMAP* scaled = create_bitmap(w, h);
    clear_to_color(scaled, makecol(255, 0, 255)); // fond transparent aussi

    stretch_blit(temp, scaled, 0, 0, text_w, text_h, 0, 0, w, h);

    // Rendre le magenta transparent
    set_trans_blender(0, 0, 0, 255);
    draw_sprite(dest, scaled, x - w / 2, y);

    destroy_bitmap(temp);
    destroy_bitmap(scaled);
}

t_personnage charger(bool *peux_jouer) {// On fait charger le joueur si il y a une sauvegarde a charger sinon faire directement initialiser joueur
    t_personnage personnage;
    char nom[100][100];

    //On recupere tous nos nom
    FILE* pt= fopen("nom.txt", "r");
    int j = 0;
    while(fscanf(pt, "%s", nom[j]) == 1) {
        j++;
    }
    fclose(pt);

    //Afficher tous les nom (Code avec menu Allegro a integre ici)
    char nom2[100]; //=>correspond au pseudo qu'on recupere
    char nom2_txt[100]; //=>on lui rajoute .txt
    char bufferSaisie[100] = "";
    int index = 0;
    int touche = 0;
    BITMAP* fond = load_bitmap("charger_menu.bmp", NULL);
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

    while (*peux_jouer == false) {
        blit(fond, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        // --- Titre ---
        draw_large_text(buffer, font, "SELECTION DE JOUEUR", SCREEN_W / 2, 140, makecol(255, 215, 0), 9);

        // --- Liste des sauvegardes ---
        draw_large_text(buffer, font, "Sauvegardes disponibles :", SCREEN_W / 2, 220, makecol(240, 240, 240), 5);
        for (int i = 0; i < j; i++) {
            textout_centre_ex(buffer, font, nom[i], SCREEN_W / 2, 250 + i * 30, makecol(255, 255, 255), -1);
        }

        // --- Champ de pseudo ---
        textout_centre_ex(buffer, font, "Entrez votre pseudo :", SCREEN_W / 2, 380, makecol(255, 200, 0), -1);

        int box_width = 400;
        int box_height = 30;
        int box_x = SCREEN_W / 2 - box_width / 2;
        int box_y = 410;

        rect(buffer, box_x, box_y, box_x + box_width, box_y + box_height, makecol(255, 255, 255));
        textout_ex(buffer, font, bufferSaisie, box_x + 10, box_y + 8, makecol(255, 255, 0), -1);

        // Curseur clignotant
        if ((clock() / 500) % 2 == 0 && index < 99) {
            int cursor_x = box_x + 10 + text_length(font, bufferSaisie);
            rectfill(buffer, cursor_x, box_y + 7, cursor_x + 2, box_y + box_height - 7, makecol(255, 255, 0));
        }

        // Gestion clavier
        if (keypressed()) {
            touche = readkey() & 0xff;
            if (touche == 13) {
                strcpy(nom2, bufferSaisie);
                *peux_jouer = true;
            } else if (touche == 8 && index > 0) {
                index--;
                bufferSaisie[index] = '\0';
            } else if (touche >= 32 && touche <= 126 && index < 99) {
                bufferSaisie[index++] = (char)touche;
                bufferSaisie[index] = '\0';
            }
        }

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(16);
    }
    destroy_bitmap(buffer);
    destroy_bitmap(fond);


    //on  rajoute .txt a la fin de nom2[100] pour pouvoir lire le fichier
    strcpy(nom2_txt, nom2);
    strcat(nom2_txt, ".txt");

    //On sauvegarde le nom si il est nouveau dans notre fichier nom.txt
    int compteur = 0;
    for(int i = 0; i < j; i++) {
        if(strcmp(nom[i], nom2) != 0) {//si le nom ne correspond pas on incremente de 1 le compteur
            compteur++;
        }
    }
    if(compteur == j) { //Si mon compteur vaut le nombre de pseudo enregistrer cela signifie que le nom n'existe pas
        FILE* pt4= fopen("nom.txt", "a");
        fprintf(pt4, "%s\n", nom2);//On ne sauvegarde que des noms et pas des noms avec des .txt a la fin
        fclose(pt4);
    }

    //On recupere les informations si le compte existe sinon on lui en cree
    if(compteur != j) {
        FILE* pt2 = fopen(nom2_txt, "r"); //J'ouvre mon fichier .txt

        fscanf(pt2, "%s", personnage.nom);
        fscanf(pt2, "%d", &personnage.nb_mort);
        fscanf(pt2, "%d", &personnage.nb_niveau);
        fscanf(pt2, "%d", &personnage.niveau1_fini);
        fscanf(pt2, "%d", &personnage.niveau2_fini);
        fscanf(pt2, "%d", &personnage.niveau3_fini);
        fclose(pt2);
    }
    else {
        strcpy(personnage.nom, nom2);
        personnage.nb_mort = 0;
        personnage.nb_niveau = 0;
        personnage.niveau1_fini = 0;
        personnage.niveau2_fini = 0;
        personnage.niveau3_fini = 0;
    }
    return personnage;
}

//commentairea
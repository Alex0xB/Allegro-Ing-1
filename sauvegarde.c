#include <stdio.h>
#include "sauvegarde.h"
#include "personnage.h"
#include <stdbool.h>
#include <string.h>

void nettoyer_chaine(char* str) {
    // Supprimer les espaces au début
    while (*str == ' ' || *str == '\t' || *str == '\n') {
        memmove(str, str + 1, strlen(str));
    }

    // Supprimer les espaces en fin
    int len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
}

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
    int debut_affichage = 0; // index de début de la fenêtre visible
    const int max_affiches = 8; // max de pseudos affichés à la fois
    // Pseudos
    int base_y = 270; //Pseudo position
    int espace = 40;
    BITMAP* fond = load_bitmap("charger_menu.bmp", NULL);
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

    while (*peux_jouer == false) {
        blit(fond, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        // --- TITRE PRINCIPAL ---
        draw_large_text(buffer, font, "SELECTION DE JOUEUR", SCREEN_W / 2, 100, makecol(255, 200, 0), 2.5);

        // --- LISTE DES SAUVEGARDES ---
        draw_large_text(buffer, font, "Sauvegardes disponibles :", SCREEN_W / 2, 200, makecol(255, 180, 0), 1.6);

        // Affichage de la liste défilable

        for (int i = 0; i < max_affiches && (debut_affichage + i) < j; i++) {
            draw_large_text(
                buffer,
                font,
                nom[debut_affichage + i],
                SCREEN_W / 2,
                base_y + i * espace,
                makecol(255, 255, 255),
                1.6
            );
        }


        // Affiche flèche haut si possible
        if (debut_affichage > 0) {
            textout_centre_ex(buffer, font, "^", SCREEN_W / 2, base_y - 30, makecol(200, 200, 200), -1);
        }

        // Affiche flèche bas si encore des noms à afficher
        if (debut_affichage + max_affiches < j) {
            textout_centre_ex(buffer, font, "v", SCREEN_W / 2, base_y + max_affiches * espace, makecol(200, 200, 200), -1);
        }

        // --- CHAMP DE PSEUDO ---
        draw_large_text(buffer, font, "Entrez votre pseudo :", SCREEN_W / 2, 700, makecol(255, 190, 0), 1.6);

        int box_width = 500;
        int box_height = 45;
        int box_x = SCREEN_W / 2 - box_width / 2;
        int box_y = 750;

        rect(buffer, box_x, box_y, box_x + box_width, box_y + box_height, makecol(255, 200, 0));
        draw_large_text(buffer, font, bufferSaisie, SCREEN_W / 2, box_y + 8, makecol(255, 255, 0), 1.8);

        // Curseur clignotant
        if ((clock() / 500) % 2 == 0 && index < 99) {
            int cursor_x = SCREEN_W / 2 + (text_length(font, bufferSaisie) * 1.8 / 2);
            rectfill(buffer, cursor_x, box_y + 12, cursor_x + 3, box_y + box_height - 12, makecol(255, 255, 0));
        }

        if (keypressed()) {
            int k = readkey();
            touche = k & 0xff;
            int scancode = k >> 8;

            if (touche == 13) {
                nettoyer_chaine(bufferSaisie);
                strcpy(nom2, bufferSaisie);
                *peux_jouer = true;
            } else if (touche == 8 && index > 0) {
                index--;
                bufferSaisie[index] = '\0';
            } else if (touche >= 32 && touche <= 126 && index < 99) {
                bufferSaisie[index++] = (char)touche;
                bufferSaisie[index] = '\0';
            } else if (scancode == KEY_UP && debut_affichage > 0) {
                debut_affichage--;
            } else if (scancode == KEY_DOWN && (debut_affichage + max_affiches) < j) {
                debut_affichage++;
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
        nettoyer_chaine(nom2);
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
        fscanf(pt2, "%d", &personnage.nb_vies);
        fclose(pt2);
    }
    else {
        strcpy(personnage.nom, nom2);
        personnage.nb_mort = 0;
        personnage.nb_niveau = 0;
        personnage.niveau1_fini = 0;
        personnage.niveau2_fini = 0;
        personnage.niveau3_fini = 0;
        personnage.nb_vies = 3;
    }
    return personnage;
}

//commentairea
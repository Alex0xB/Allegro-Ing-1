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

t_personnage* charger(bool **peux_jouer) {// On fait charger le joueur si il y a une sauvegarde a charger sinon faire directement initialiser joueur
    t_personnage* personnage;
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
    while(peux_jouer == false) {
        **peux_jouer = true;
    }

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
        FILE* pt= fopen("nom.txt", "r");
        fprintf(pt, "%s\n", nom2);//On ne sauvegarde que des noms et pas des noms avec des .txt a la fin
        fclose(pt);
    }

    //On recupere les informations si le compte existe sinon on lui en cree
    if(compteur == j) {
        FILE* pt2 = fopen(nom2_txt, "r"); //J'ouvre mon fichier .txt

        fscanf(pt2, "%s", personnage->nom);
        fscanf(pt2, "%d", personnage->nb_mort);
        fscanf(pt2, "%d", personnage->nb_niveau);
        fscanf(pt2, "%d", personnage->niveau1_fini);
        fscanf(pt2, "%d", personnage->niveau2_fini);
        fscanf(pt2, "%d", personnage->niveau3_fini);
        fclose(pt2);
    }
    else {
        strcmp(personnage->nom, nom2);
        personnage->nb_mort = 0;
        personnage->nb_niveau = 0;
        personnage->niveau1_fini = 0;
        personnage->niveau2_fini = 0;
        personnage->niveau3_fini = 0;
    }
    return personnage;
}

bool verification_nom(char nom[100]) {
    int a = strlen(nom);
    if(nom[a-1] != 't' || nom[a-2] != 'x' || nom[a-3] != 't') {
        return false;
    }
    return true;
}

//commentairea
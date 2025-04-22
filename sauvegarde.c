#include <stdio.h>
#include "sauvegarde.h"
#include <stdbool.h>
#include <string.h>

void sauvegarder(t_personnage* personnage) {
    FILE* liste_nom = fopen("nom.txt", "r"); //On verifie si le joueur existe deja
    bool nom_existant = false;
    char nom_lu[100];
    char nom_txt[100];
    while(fscanf(liste_nom, "%s", nom_lu) == 1) {
        if(strcmp(personnage->nom, nom_lu) == 0) {
            nom_existant = true;
            break;
        }
    }
    fclose(liste_nom);
    strcpy(nom_txt, personnage->nom);
    strcat(nom_txt, ".txt");
    if(nom_existant) {
        FILE* pt = fopen(nom_txt, "w");
        if (pt == NULL) {
            printf("Erreur d'ouvrir le fichier\n");
        }
        fprintf(pt, "%s\n", personnage->nom);
        fprintf(pt, "%d\n", personnage->nb_mort);
        fprintf(pt, "%d\n", personnage->nb_niveau);
        fclose(pt);
    }
    else {
        FILE* pt2 = fopen("%s.txt", personnage->nom, "w"); //Je cree un nouveau fichier
        if (pt2 == NULL) {
            printf("Erreur d'ouvrir le fichier\n");
        }
        fprintf(pt2, "%s\n", personnage->nom);
        fprintf(pt2, "%d\n", personnage->nb_mort);
        fprintf(pt2, "%d\n", personnage->nb_niveau);
        fclose(pt2);

        FILE* pt3 = fopen("nom.txt", "a"); //Je rajoute le nom du joueur dans la liste
        fprintf(pt3, "%s\n", personnage->nom);
        fclose(pt3);
    }
}

void charger(t_personnage* personnage) {// On fait charger le joueur si il y a une sauvegarde a charger sinon faire directement initialiser joueur
    char nom[100];
    FILE* pt= fopen("nom.txt", "r");
    printf("Sauvegardes disponibles :\n");
    while(fscanf(pt, "%s", nom) == 1) { //J'affiche toute les sauvegardes
        printf("- %s\n", nom);
    }
    fclose(pt);

    char nom2[100];
    do {
        printf("Nom de la sauvegarde avec le .txt\n");
        scanf("%s", nom2);
    }while(!verification_nom(nom2));

    FILE* pt2 = fopen(nom2, "r");
    if(pt2 == NULL) {
        printf("Erreur d'ouvrir le fichier ou impossible d'ouvrir le fichier avec le joueur\n");
    }
    fscanf(pt2, "%s", personnage->nom);
    fscanf(pt2, "%d", personnage->nb_mort);
    fscanf(pt2, "%d", personnage->nb_niveau);
    fclose(pt2);
}

bool verification_nom(char nom[100]) {
    int a = strlen(nom);
    if(nom[a-1] != 't' || nom[a-2] != 'x' || nom[a-3] != 't') {
        return false;
    }
    return true;
}

//commentaire
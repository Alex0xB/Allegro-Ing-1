#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H
#include "personnage.h"
#include"stdbool.h"

void sauvegarder(t_personnage* personnage);

void charger(t_personnage* personnage);

bool verification_nom(char nom[100]);
#endif //SAUVEGARDE_H

#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H
#include "personnage.h"
#include"stdbool.h"

void sauvegarder(t_personnage* personnage);

t_personnage* charger();

bool verification_nom(char nom[100]);

#endif //SAUVEGARDE_H
//a
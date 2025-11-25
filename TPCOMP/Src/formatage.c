/*
 * formatage.c
 *
 *  Created on: Nov 25, 2025
 *      Author: user
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "formatage.h"

// Fonction pour afficher un titre avec une ligne de séparation avant et après
void afficherTitreAvecSeparateur(const char* titre) {
    int longueurTitre = strlen(titre);
    int longueurLigne = 80; // Longueur de la ligne de séparation


	printf("\r \n");
	printf("\r \n");
    // Affichage du séparateur avant
    printf("|%.*s|\r\n", longueurLigne, "------------------------------------------------------------------------------------");

    // Affichage du titre centré
    printf("|%*s%s%*s|\r\n", (longueurLigne - longueurTitre - 2) / 2, "", titre, (longueurLigne - longueurTitre - 2) / 2, "");

    // Affichage du séparateur après
    printf("|%.*s|\r\n", longueurLigne, "------------------------------------------------------------------------------------");

    // Saut de ligne
    printf("\r\n");
}


/*
 * compression.c
 *
 *  Created on: Oct 14, 2025
 *      Author: user
 */
#include <stdint.h>
#include <stm32f446xx.h>
#include <string.h>
#include "compression.h"
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "util.h"
void occurence (uint8_t* chaine , uint32_t tab[256]){
	uint16_t i =0;
	while(chaine[i]!='\0'){

		tab[chaine[i]]++;
		i++;

	}

	afficheOccurence(tab);

}

void afficheOccurence (uint32_t tab[256]){

	for(uint16_t i=0;i<256;i++){
		if(tab[i]!=0){

		printf("Le nombre d'occurence de char %c = %ld \r\n ",i,tab[i]);

		}
	}

}
void creerFeuille(struct noeud *arbre[256], uint32_t tab[256]){
	uint16_t compt =0;
	for(uint16_t i=0;i<256;i++){

		if(tab[i]!= 0){
			struct noeud *temp=malloc(sizeof(struct noeud));
			temp->c = (uint16_t)i;
			temp ->code = 0;
			temp->tailleCode = 0;
			temp ->droite = NULL;
			temp ->gauche = NULL;
			temp ->occurence = tab[i];
			arbre[compt++]=temp;

		}
	}
}



void AfficherTabArbreHuffman(struct noeud* arbre[256], uint32_t taille)
{
    for (uint16_t i = 0; i < taille; i++) {
        if (arbre[i] != NULL) {  // Vérifie que le pointeur n'est pas NULL
            printf("Nbre d'occurence du char '%c' = %ld \r\n", (char)arbre[i]->c, arbre[i]->occurence);
        }
    }
}


























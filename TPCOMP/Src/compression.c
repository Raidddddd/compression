/*
 * compression.c
 *
 *  Created on: Oct 14, 2025
 *      Author: ABADOU Raid, ALIA Amine
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

/*-----------------------------------------| Occurence |-----------------------------------------*/
/* R : Parcours la chaine de caractère pour calculer le nombre d'occurence d'un caractère
 * E : Un pointeur vers une chaine de caractère, un tableau d'entier
 * S : Vide
 */
void occurence (uint8_t* chaine , uint32_t tab[256]){
	uint16_t i =0;
	while(chaine[i]!='\0'){

		tab[chaine[i]]++;
		i++;

	}

	afficheOccurence(tab);

}
/*------------------------------------------------------------------------------------------------*/



/*-----------------------------------------| Afficher Occurence |-----------------------------------------*/
/* R : Cette fonction à pour but d'afficher notre occurence, notre chaine de caractère
 * E : Un tableau d'entier qui contient notre chaine de caractères
 * S : Vide
 */
void afficheOccurence (uint32_t tab[256]){
	printf("\r \n");
	printf("|-------------------------------| AFFICHAGE OCCURENCE |-------------------------------| \r\n");
	for(uint16_t i=0;i<256;i++){
		if(tab[i]!=0){

			printf("Le nombre d'occurence de char %c = %ld \r\n ",i,tab[i]);

		}
	}
	/*------------| SEPARATEUR |------------*/
	printf("|-----------------------------------------------------------------------------------|\r\n");
	printf("\r \n");

}

/*--------------------------------------------------------------------------------------------------------*/


/*-----------------------------------------| Créer une Feuille |-----------------------------------------*/
/* R : Créer des feuilles pour l'arbre de Huffman en fonction des occurrences des caractères et les ajouter dans un tableau.
 * E : Un tableau de pointeur vers des structures noeud où chaque élément correspond à une feuille d'arbre de Huffman
 *     Un tableau contenant les occurences des caractères
 * S : Vide
 */
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
/*--------------------------------------------------------------------------------------------------------*/



/*-----------------------------------------| Créer une Feuille |-----------------------------------------*/
/* R :
 * E :
 * S : Vide
 */
void AfficherTabArbreHuffman(struct noeud* arbre[256], uint32_t taille) {
	printf("|-------------------------------| AFFICHAGE ARBRE DE HUFFMAN |-------------------------------| \r\n");

	for (uint16_t i = 0; i < taille; i++) {
		if (arbre[i] != NULL) {  //Vérifie que le pointeur est valide
			printf("Nbre d'occurence du char '%c' = %ld \r\n", (char)arbre[i]->c, arbre[i]->occurence);
		}
	}
	/*------------| SEPARATEUR |------------*/

	printf("|-----------------------------------------------------------------------------------|\r\n");
	printf("\r \n");

}

/* R : Fait le tri de notre arbre avec un tris à bulle
 * E : Le pointeur vers un arbre, un entier qui est la taille
 * S : Vide
 */
void triArbre(struct noeud* arbre[256], uint32_t taille) {
	struct noeud *tempp;

	/*/!\-------| LE TRI A BULLE DOIT PRENDRE EN COMPTE UNIQUEMENT LES ELEMENTS VALIDES |-------/!\*/
	for (uint32_t i = 0; i < taille - 1; i++) {
		for (uint32_t j = 0; j < taille - i - 1; j++) {
			if (arbre[j] != NULL && arbre[j+1] != NULL) {  // Vérifier que les éléments sont valides
				if ((arbre[j]->occurence) > (arbre[j + 1]->occurence)) {
					tempp = arbre[j];
					arbre[j] = arbre[j + 1];
					arbre[j + 1] = tempp;
				}
			}
		}
	}
}
struct noeud* racine(struct noeud* arbre[256], uint32_t taille) {
	uint32_t nbNoeuds = taille;
	printf("|-------------------------------||| PARCOURS ARBRE |||-------------------------------| \r\n");

	while (nbNoeuds > 1) {
		struct noeud* gauche = arbre[0];
		struct noeud* droite = arbre[1];

		struct noeud *parent = malloc(sizeof(struct noeud));

		parent->c = 0;
		parent->occurence = gauche->occurence + droite->occurence;
		parent->gauche = gauche;
		parent->droite = droite;
		parent->code = 0;
		parent->tailleCode = 0;

		arbre[0] = parent;

		arbre[1] = arbre[nbNoeuds - 1];

		nbNoeuds--;
		triArbre(arbre, nbNoeuds);
		parcourirArbre(arbre[0]);
	}
	printf("|-----------------------------------------------------------------------------------|\r\n");
	printf("\r \n");

	return arbre[0];
}
void parcourirArbre(struct noeud* ptrNoeud){

	if(ptrNoeud->droite==NULL && ptrNoeud->gauche==NULL){
		printf("je suis une feuille \r\n");
	}else{
		printf("je suis un noeud \r\n");
		parcourirArbre(ptrNoeud->droite);
		parcourirArbre(ptrNoeud->gauche);
	}


}

void free_mem(struct noeud* racine){
	free(racine->droite);
	free(racine->gauche);
	free(racine);

}


void creercode(struct noeud* ptrNoeud,uint32_t code,uint32_t taille){

	if(ptrNoeud->droite==NULL && ptrNoeud->gauche==NULL){

		ptrNoeud->tailleCode=taille;
		ptrNoeud->code=code;
		printf("%c\tcode : %ld taille : %ld \r\n ",ptrNoeud->c,ptrNoeud->code,ptrNoeud->tailleCode);
	}else {
		creercode(ptrNoeud->droite,code<<1,taille+1);
		creercode(ptrNoeud->gauche,(code<<1)+1,taille+1);
	}

}


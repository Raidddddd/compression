/*
 * compression.c
 *
 *  Created on: Oct 14, 2025
 *      Author: ABADOU Raid, ALIA Amine
 *      TP DE PROGRAMATION C
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
#include "formatage.h"

uint8_t texteCompress[TAILLE_MAX_COMPRESS];
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

	/*-- Affichage Occurence --*/
	afficherTitreAvecSeparateur("AFFICHAGE OCCURENCE");
	afficheOccurence(tab);
	/*-------------------------*/

}
/*------------------------------------------------------------------------------------------------*/



/*-----------------------------------------| Afficher Occurence |-----------------------------------------*/
/* R : Cette fonction à pour but d'afficher notre occurence, notre chaine de caractère
 * E : Un tableau d'entier qui contient notre chaine de caractères
 * S : Vide
 */
void afficheOccurence (uint32_t tab[256]){

	for(uint16_t i=0;i<256;i++){
		if(tab[i]!=0){

			printf("Le nombre d'occurence de char %c = %ld \r\n ",i,tab[i]);

		}
	}

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



/*-----------------------------------------| Afficher Tableau de Huffman |-----------------------------------------*/
/* R : Afficher chaque noeud du tableau
 * E : Un arbre de type tableau, la taille de notre
 * S : Vide
 */
void AfficherTabArbreHuffman(struct noeud* arbre[256], uint32_t taille) {

	for (uint16_t i = 0; i < taille; i++) {
		if (arbre[i] != NULL) {  //Vérifie que le pointeur est valide
			printf("Nbre d'occurence du char '%c' = %ld \r\n", (char)arbre[i]->c, arbre[i]->occurence);
		}
	}
}
/*--------------------------------------------------------------------------------------------------------*/


/*-----------------------------------------| Tri Arbre de Huffman |-----------------------------------------*/
/* R : Fait le tri de notre arbre selon un ordre croissant avec un tris à bulle
 * E : Le pointeur vers un arbre, un entier qui est le nombre d'élément à trier
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
/*--------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------| Racine |-----------------------------------------*/
/* R : Construit l'arbre de Huffman complet en fusionnant les deux plus petits noeuds jusqu'à obtenir la racine
 * E : Notre tableau de feuille (ordonnées de préférence)
 * 	   taille : Un entier qui représente le nombre de feuille initiale de l'arbre entré
 * S : Retourne le pointeur vers la racine de l'arbre final
 */
struct noeud* racine(struct noeud* arbre[256], uint32_t taille) {
	uint32_t nbNoeuds = taille;
	afficherTitreAvecSeparateur("Parcours Arbre");

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

	return arbre[0];
}
/*--------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------| Parcourir Arbre |-----------------------------------------*/
/* R : Parcours notre arbre (droite puis gauche) et affiche si le noeud est une feuille ou un noeud interne
 * E : Pointeur vers un noeud
 * S : Vide
 */
void parcourirArbre(struct noeud* ptrNoeud){

	if(ptrNoeud->droite==NULL && ptrNoeud->gauche==NULL){
		printf("je suis une feuille \r\n");
	}else{
		printf("je suis un noeud \r\n");
		parcourirArbre(ptrNoeud->droite);
		parcourirArbre(ptrNoeud->gauche);
	}


}


/*-----------------------------------------| Free Memory |-----------------------------------------*/
/* R : Libère un noeud et ses deux enfants directs
 * E : Pointeur vers un noeud
 * S : Vide
 */
void free_mem(struct noeud* racine){
	free(racine->droite);
	free(racine->gauche);
	free(racine);

}
/*--------------------------------------------------------------------------------------------------------*/

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
struct noeud* getAddress(struct noeud* ptrNoeud, uint8_t caractere) {
    // 1. Cas de base : Arbre vide ou fin de branche
    if (ptrNoeud == NULL) {
        return NULL;
    }

    // 2. Si c'est une feuille (pas d'enfant gauche ni droite)
    if (ptrNoeud->gauche == NULL && ptrNoeud->droite == NULL) {
        // On vérifie si c'est le caractère que l'on cherche
        // (Cast en uint8_t pour comparer proprement avec le paramètre)
        if ((uint8_t)ptrNoeud->c == caractere) {
            return ptrNoeud;
        }
        return NULL; // C'est une feuille, mais pas la bonne
    }

    // 3. Si c'est un noeud interne, on cherche récursivement

    // D'abord à gauche
    struct noeud* resultat = getAddress(ptrNoeud->gauche, caractere);
    if (resultat != NULL) {
        return resultat; // Trouvé à gauche !
    }

    // Sinon, on cherche à droite (et on retourne le résultat, trouvé ou non)
    return getAddress(ptrNoeud->droite, caractere);
}
void compresser(uint8_t *texte, struct noeud *racine)
{
    uint32_t indexOctet = 0;
    uint8_t bitPos = 0;
    uint8_t octetCourant = 0;

    uint32_t i = 0;
    while (texte[i] != '\0')
    {

        struct noeud *n = getAddress(racine, texte[i]);

        uint32_t code = n->code;
        uint32_t taille = n->tailleCode;


        for (int b = taille - 1; b >= 0; b--)
        {
            uint8_t bit = (code >> b) & 1;


            octetCourant |= bit << (7 - bitPos);
            bitPos++;


            if (bitPos == 8)
            {
                texteCompress[indexOctet++] = octetCourant;



                octetCourant = 0;
                bitPos = 0;
            }
        }

        i++;
    }


    if (bitPos != 0)
    {
        texteCompress[indexOctet++] = octetCourant;
    }

    printf("Compression terminée : %lu octets\r\n", indexOctet);
}

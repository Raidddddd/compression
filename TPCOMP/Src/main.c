#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "util.h"
#include "compression.h"
#include "formatage.h"

int main(void) {
	FPU_Init();
	GPIO_Init();
	USART2_Init();
	SYSTICK_Init();

	uint32_t tab[256] = {0};
	struct noeud* arbre[256] = {0};  // Initialisation du tableau

	/*-- Chaine de caractère original --*/
	uint8_t chaine[] = "aaaabbbccd";

	occurence(chaine, tab);   // Calcul du nombre d'occurence de notre chaine de caractère

	creerFeuille(arbre, tab); // Création des feuilles à partir du tableau d'occurence

	/*-- Calcul du nombre de feuilles créées --*/
	uint16_t tailleArbre = 0;
	for (uint16_t i = 0; i < 256; i++) {
		if (arbre[i] != NULL) {
			tailleArbre++;
		}
	}
	/*--                                     --*/


	/*-------------------------------------------------------------| ARBRE AVANT TRI |-------------------------------------------------------------*/
	afficherTitreAvecSeparateur("ARBRBE NON TRIE"); // Formatage pour la console

	AfficherTabArbreHuffman(arbre, tailleArbre);
	printf("|-----------------------------------------------------------------------------------|\r\n");
		printf("\r \n");
		/*---------------------------------------------------------------------------------------------------------------------------------------------*/


		/*-------------------------------------------------------------| ARBRE APRES TRI |-------------------------------------------------------------*/
			triArbre(arbre, tailleArbre); // Tri de l'arbre de Huffman

			afficherTitreAvecSeparateur("ARBRE TRIE"); // Formatage pour la console

			AfficherTabArbreHuffman(arbre, tailleArbre);
			/*---------------------------------------------------------------------------------------------------------------------------------------------*/


			/*-------------------------------------------------------------| CONSTRUCTION ARBRE DU HUFFMAN FINAL |-------------------------------------------------------------*/
				racine(arbre,tailleArbre);
				/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	struct noeud* test;
	test = getAddress(arbre[0], 'e');

	while(1) {
		SYSTICK_Delay(1000);
		GPIOA->ODR ^= 1 << 5;  // Test
	}

	return 0;
}

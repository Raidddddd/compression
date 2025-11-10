#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "util.h"
#include "compression.h"

int main(void) {
    FPU_Init();
    GPIO_Init();
    USART2_Init();
    SYSTICK_Init();

    uint32_t tab[256] = {0};
    struct noeud* arbre[256] = {0};  // Initialisation du tableau

    uint8_t chaine[] = "aaaabbbccd";
    printf("Hello\r\n");

    occurence(chaine, tab);
    creerFeuille(arbre, tab);

    // Calcul du nombre de feuilles créées
    uint16_t tailleArbre = 0;
    for (uint16_t i = 0; i < 256; i++) {
        if (arbre[i] != NULL) {
            tailleArbre++;
        }
    }

    // Affichage des résultats avant et après tri
    AfficherTabArbreHuffman(arbre, tailleArbre);

    triArbre(arbre, tailleArbre);
    printf("Arbre trié!!!!!\r\n");
    AfficherTabArbreHuffman(arbre, tailleArbre);
    printf("--------------\r\n");
    racine(arbre,tailleArbre);
   //parcourirArbre(arbre[0]);
   //creercode(arbre[0],0,0);
    while(1) {
        SYSTICK_Delay(1000);
        GPIOA->ODR ^= 1 << 5;  // Test
    }

    return 0;
}

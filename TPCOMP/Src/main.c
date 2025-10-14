#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "util.h"
#include "compression.h"

int main(void)
{
	FPU_Init();
	GPIO_Init();
	USART2_Init();
	SYSTICK_Init();
	uint32_t tab[256]={0};
	struct noeud* arbre[256];
	uint8_t chaine[] = "banane";
	printf("Hello\r\n");
	occurence(chaine, tab);
	creerFeuille(arbre, tab);
	AfficherTabArbreHuffman(arbre, 10);



	while(1){
		SYSTICK_Delay(1000);
		//Fonction de test de hello word avec MaJ README encore
		GPIOA->ODR ^= 1<<5;

	}
	return 0;
}

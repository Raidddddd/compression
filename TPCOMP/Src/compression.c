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
for(uint16_t i=0;i<256;i++){

	printf("Le nombre d'occurence de char %c = %ld \r\n ",i,tab[i]);
	tab[i]=0;
	}
}

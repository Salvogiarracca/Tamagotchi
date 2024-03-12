/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_button.c
** Descriptions:        functions to manage INT0, KEY1 and KEY2 interrupts
** Correlated files:    button.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#include "button.h"
#include "lpc17xx.h"
#include "../led/led.h"
#include "../RIT/RIT.h"
#include "../timer/timer.h"
#include "../utils/utils.h"

extern uint8_t int0;
extern uint8_t key1;
extern uint8_t key2;

void handleButtons(void) {
	if(int0 > 1){
		if((LPC_GPIO2->FIOPIN & (1 << 10)) == 0){ // INT0 is pressed
			switch(int0){
				case 2:{
				// serve Int0
				}break;
				default: break;
			}
			int0++;
		} else {
			int0 = 0;
			NVIC_EnableIRQ(EINT0_IRQn);
			LPC_PINCON->PINSEL4 |= (1 << 20);
		}
	} else if(int0 == 1) int0++;
	if(key1 > 1){
		if((LPC_GPIO2->FIOPIN & (1 << 11)) == 0){ // KEY1 is pressed
			switch(key1){
				case 2:{
				// serve Key1
				}break;
				default: break;
			}
			key1++;
		} else {
			key1 = 0;
			NVIC_EnableIRQ(EINT1_IRQn);
			LPC_PINCON->PINSEL4 |= (1 << 22);
		}
	} else if(key1 == 1) key1++;
	if(key2 > 1){
		if((LPC_GPIO2->FIOPIN & (1 << 12)) == 0){ // KEY2 is pressed
			switch(key2){
				case 2:{
				// serve Key2
				}break;
				default: break;
			}
			key2++;
		} else {
			key2 = 0;
			NVIC_EnableIRQ(EINT2_IRQn);
			LPC_PINCON->PINSEL4 |= (1 << 24);
		}
	} else if(key2 == 1) key2++;
}

/*****************************************************************************
**                            End Of File
******************************************************************************/

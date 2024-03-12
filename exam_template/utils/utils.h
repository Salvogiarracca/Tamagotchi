/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           utils.h
** Descriptions:        Prototypes of functions included in the utils.c, utils.s files
** Correlated files:    utils.c, utils.s
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef __UTILS_H
#define __UTILS_H

#include "LPC17XX.h"

/* VARS */
enum{ 
	ON,
	OFF,
	HOLD_ON,
	HOLD_OFF,
	NONE
}; /* USED TO MANAGE DUTY CYCLE FOR LED BLINKING */
extern uint8_t ledStatus;
extern uint8_t buttons[]; /* REMEMBER: buttons[] IS AN ARRAY OF 3 ELEMENTS EACH FOR ONE BUTTON (pos=0 -> int0..). USE IT WHEN YOU HAVE TO MANAGE PARTICULAR EVENTS */

/* utils.s */
extern int divisible(int, int);  /* THIS FUNCTION PERFORM n1 % n2 END RETURN THE REMAINDER */
extern unsigned int count_bits_to_1(unsigned int);  /* THIS FUNCTION COUNTS THE ONES CONTAIN IN n1 AND RETURN THIS VALUE */
extern int search_in_pool(unsigned int); /* THIS FUNCTION SEARCH IF A VALUE n1 IS PRESENT IN A DEFINED LITERAL POOL; RETURN POSITION IF FOUND OR -1 IF NOT FOUND */
extern unsigned int increasing_monotone(unsigned char VETT[], unsigned int num);  /*THIS FUNCTION RETURN 0XFF IF VALUES SEQUENCE IN VETT[] IS INCREASING MONOTONE (NOT STRICTLY), RETURN 0X55 ELSE*/
extern int count_negative_and_odd(int* VETT, unsigned int n);  /* THIS FUNCTION COUNTS HOW MANY NUMBERS ARE BOTH NEGATIVE AND ODD */
extern unsigned char get_and_sort(unsigned char* VETT, unsigned char VAL, int n);  /* THIS FUNCTION RECEIVE A NUMBER AND INSERT IT INTO AN ARRAY ORDINATELY (DESCENDING ORDER) */
extern void bubble_sort(int *VETT, int lenght); /* THIS FUNCTION PERFORMS THE BUBBLE SORT (ASCENDING) OF AN ARRAY IN LOCO */
extern char diff_pos_neg(int *buffer, unsigned int size, unsigned int *overflow); /* THIS FUNCTION RETURN THE DIFFERENCE BETWEEN POSITIVE AND NEGATIVE ITEMS IN AN ARRAY (overflow set to 1 if positive_numbers==size) */
extern unsigned int avg_press_with_filter(unsigned int VETT[], unsigned int numero_misure, unsigned int REMOVE); /* THIS FUNCTION PERFORM AN AVERAGE OF ARRAY ELEMENTS WITHOUT "BORDERS"("REMOVE" MAYOR AND MINOR ITEMS(sort is needed a priori)) */
extern unsigned int calcola_somma_prodotto(unsigned int VETT[], unsigned int N, char *alarm); /* THIS FUNCTION PERFORM MULTIPLICATION WITH ACCUMULATION OF ELEMENTS IN AN ARRAY (TURNO 1 APPELLO DEL 6 FEBBRAIO 2023) */
extern int differenza_media_positivi_negativi(int V[], unsigned int num, char* over); /* THIS FUNCTION PERFORM AVERAGE OF POS AND NEG IN AN ARRAY AND RETURN THE DIFFERNCE (TURNO 3 APPELLO DEL 6 FEBBRAIO 2023)*/

/* utils.c*/
uint32_t getTicks(float seconds, float Hz);
float getSecByFreq(float freq);
void LED_All_blink(void);  /* ALL LED BLINK */
void LED_blink_bybutton(void); 	/* PARTICULAR, BE CAREFUL */
void LED_blink(uint8_t lednum); /* SIMPLE LED BLINK */
void LED_blink_Diff_Time(uint8_t num, int Ticks1, int Ticks2);  /* THIS FUNCTION PERMITS TO BLINK A LED BUT STAY ON FOR TICKS1, STAY OFF FOR TICKS2 (RIT 0.05sec ) */

/*EXAMPLES FOR BUTTONS AND JOYSTICK*/

/*BOTTONE PREMUTO PER UN CERTO TEMPO
############################## VERSIONE 1 #########################
if(key1 > 1){
	if(!displaying){   																										--> per inibire la pressione del key1 durante la visualizzazione! displaying e' definito in sample.c
		if((LPC_GPIO2->FIOPIN & (1 << 11)) == 0){ // KEY1 is pressed
			key1++;																														--> se il bottone e' premuto allora incremento il contatore delle pressioni 
		} else {																														--> nell'else sta tutta la logica 
			time = key1*0.05;																									--> time e' una variabile statica che viene creata moltiplicando il numero di pressioni per il tempo di polling del rit (0.05 secondi)
			if(time < 2){
				VAR1 += 2;
			}else if(time > 2 && time < 3){
				VAR1 += 3;
			}else{
				//assembly launch
				result = calcola_somma_prodotto(VETT, pos, &alarm);
				acquisition = 0;
				displaying = 1;
			}
			key1 = 0;
			NVIC_EnableIRQ(EINT1_IRQn);
			LPC_PINCON->PINSEL4 |= (1 << 22);
		}
	}else if((LPC_GPIO2->FIOPIN & (1 << 11)) == 0){ // KEY1 is pressed
		switch(key1){
			case 2:{
				// serve Key1
				VAR1 = 0;
				VAR2 = 0;
				displaying = 0;
				acquisition = 1;
				for(i=0;i<N;i++)VETT[i]=0;
				alarm = 0;
				pos = 0;
				result = 0;
			}break;
			default: break;
		}
		key1++;
		} else {
			key1 = 0;
			NVIC_EnableIRQ(EINT1_IRQn);
			LPC_PINCON->PINSEL4 |= (1 << 22);
		}
############################# VERSIONE 2 ########################### PREFERRED
static int i;
if(int0 > 1){
	if((LPC_GPIO2->FIOPIN & (1 << 10)) == 0){ // INT0 is pressed
		switch(int0){
			case 2:{
			// serve Int0
				if(!displaying){
					result = differenza_media_positivi_negativi(VETT, N, &over);
					acquisition = 0;
					displaying = 1;
					LED_All_Off();
					init_timer(0, getTicks(getSecByFreq(3), 25));
					enable_timer(0);
				}
				else{
					for(i=0;i<N;i++) VETT[i] = 0;
					LED_All_Off();
					acquisition = 1;
					displaying = 0;
					overflow = 0;
					pos = 0;
					over = 0;
					times_filled = 0;
					disable_timer(0);
					reset_timer(0);
					reset_timer(2);
				}
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
*/

/*JOYSTICK PREMUTO PER UN CERTO TEMPO
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
		// Joytick up pressed 
		up++;																																--> se il joystick e' premuto allora incremento il contatore delle pressioni del joystick
	} else{																																--> nell'else sta tutta la logica
		if(up!=0){																													--> solo se il contatore e' diverso da zero!! altrimenti esegue l'else sempre!!
			time = 0.05 * up;																									--> time e' una variabile statica che viene creata moltiplicando il numero di pressioni per il tempo di polling del rit (0.05 secondi)
			if(time < 1)
				VAR++;
			else{
				VAR += 2*(int)time;
			}
			LED_Out(VAR);
			up = 0;
		}		
	} 
*/

/*LOGIC USED IN IRQ_RIT.c IF I WANT TO BLINK DIFFERENT SECTION OF LEDS!
	ACQUISITION PHASE
if(pos != 0){
	if(acquisition){
		if(!var1overflow){
			LED_Out_byIndexes(VETT[pos-2], 7, 4);
		}
		else{
			if(count1 == 4){
				if(blinkvar1 == 0){
					LPC_GPIO2->FIOSET |= 0x000000F0;
					blinkvar1 = 1;
				}
				else{
					LPC_GPIO2->FIOCLR |= 0x000000F0;
					blinkvar1 = 0;
				}
				count1 = 0;
			}
			else count1++;
		}
				
		if(!var2overflow){
			LED_Out_byIndexes(VETT[pos-1], 3, 0);
		}
		else{
			if(count2 == 4){
				if(blinkvar2 == 0){
					LPC_GPIO2->FIOSET |= 0x0000000F;
					blinkvar2 = 1;
				}
				else{
					LPC_GPIO2->FIOCLR |= 0x0000000F;
					blinkvar2 = 0;
				}
				count2 = 0;
			}
			else count2++;
		}			
	}
}
	DISPLAYING PHASE
if(displaying){
	if(alarm == -1){
		LED_Out(result);
	}
	else{
		if(countv == 5){
			if(blinkvis == 0){
				LED_Out(result);
				blinkvis = 1;
			}
			else {
				LED_All_Off();
				blinkvis = 0;
			}
			countv = 0;
		}
		else countv++;
	}
}

*/


#endif /* end __UTILS_H */

/*****************************************************************************
**                            End Of File
******************************************************************************/

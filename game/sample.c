/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: to control led through debounced buttons and Joystick
 *        	- key1 switches on the led at the left of the current led on, 
 *					- it implements a circular led effect,
 * 					- joystick UP function returns to initial configuration (led11 on) .
 * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Paolo BERNARDI - PoliTO - last modified 15/12/2020
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <stdio.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"
#include "GLCD/GLCD.h"
#include "TouchPanel/TouchPanel.h"
#include "ProjectFunctions/myfunctions.h"
#include "Images/Img.h"
#include "adc/adc.h"
#include "music/audio.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/

//extern int C_ASM_func(int, int); // declared in startup_LPC17xx.s

uint16_t BgColor=Grey;
uint8_t hh=0,mm=0,ss=0;
uint8_t happiness=100,satiety=100;
uint8_t volume = 0;
uint8_t currentSong = S_NONE;

int main (void) {
  	
	SystemInit();  												/* System Initialization (i.e., PLL) */
	LCD_Initialization();
	TP_Init();
	TouchPanel_Calibrate();
	LCD_Clear(BgColor);
	assingPointers();
	drawAgeWidget();
	drawHappinessAndSatiety();
	drawActionButtons();
	joystick_init();	/* Joystick Initialization           */
	ADC_init();
	
	#ifdef SIMULATOR
	init_timer(0, 0x4C4B40);		//0.2sec for slowiness of simulator
	init_timer(1, 0x4C4B40);
	//init_timer(2, 0xC8 ); 						    /* 8us * 25MHz = 200 ~= 0xC8 */
	#else
	init_timer(0, 0x17D7840);		//1sec at 25MHz for board
	init_timer(1, 0x17D7840);
	//init_timer(2, 0xC8 );
	#endif
//	init_timer(3,0x000100);
	
//	currentSong = S_MEAL;
//	playCurrentSong();

	enable_timer(0);						//age management
	enable_timer(1);
	//enable_timer(2);
	init_RIT(0x004C4B40);				//RIT Initialization 50 msec  rit freq = 100 MHz, 1 s = 100M tick
	enable_RIT();								//joystick
	changeStatus(0);
	
	
	
	
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode									 */
	LPC_SC->PCON &= ~(0x2);			
	
	
		
  while (1) {                           /* Loop forever                   	 */	
		__ASM("wfi");
  }

}

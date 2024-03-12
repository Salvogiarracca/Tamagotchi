/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: ASE EXAM
 * Note(s): this version supports the LANDTIGER Emulator
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 *----------------------------------------------------------------------------*/
                  
#include <stdio.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "../led/led.h"
#include "../button_EXINT/button.h"
#include "../timer/timer.h"
#include "../RIT/RIT.h"
#include "../joystick/joystick.h"
#include "../adc/adc.h"
#include "../utils/utils.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
uint8_t ledStatus = ON; /* CHANGE THIS VALUE SOMEWERE IF YOU WANT TO BLINK A LED WITH A DIFFERENT FREQ (CHANGE THE FUNCTION IN utils.c/h) */
uint8_t buttons[3] = {0, 0, 0};  /* REMEMBER: buttons[] IS AN ARRAY OF 3 ELEMENTS EACH FOR ONE BUTTON (pos=0 -> int0..). USE IT WHEN YOU HAVE TO MANAGE PARTICULAR EVENTS */
extern int C_ASM_func(int, int); // declared in startup_LPC17xx.s

int main (void) {
  	
	SystemInit();  												/* System Initialization (i.e., PLL) */
  LED_init();                           /* LED Initialization                */
  BUTTON_init();												/* BUTTON Initialization             */
	joystick_init();											/* Joystick Initialization           */
	//ADC_init();                           /* ADC initialization 					  	 */
	//init_timer(0, 0);											/* Timer N initialization						 */
	init_RIT(getTicks(0.05, 100));									/* RIT Initialization 50 msec        */ // rit freq = 100 MHz, 1 s = 100M tick
	enable_RIT();													/* RIT enabled											 */
	
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode									 */
	LPC_SC->PCON &= ~(0x2);						
		
  while(1) {                           /* Loop forever                   	 */	
		__ASM("wfi");
  }

}

/*****************************************************************************
**                            End Of File
******************************************************************************/

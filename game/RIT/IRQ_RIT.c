/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../ProjectFunctions/myfunctions.h"
#include "../TouchPanel/TouchPanel.h"
#include "../adc/adc.h"
#include "../music/music.h"
#include "../timer/timer.h"
#include "../music/audio.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern uint8_t happiness_count;
extern uint8_t satiety_count;
extern uint8_t currentSong;


enum DOG_STATE{
	WALKING = 0,
	EATING_L = 1,
	EATING_R = 2,
	RUNNING = 3,
	RESET = 4,
	CUDDLES = 5
};



void handleJoystick() {
	static int select = 0;
	static int left = 0;
	static int right = 0;
	
	extern int selected;
	
	switch(selected){
		case 0: {
			if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
				/* Joytick Select pressed */
				select++;
				if(select == 1){
					changeStatus(EATING_L);
					currentSong = S_CLICK;
			    playCurrentSong();
				}
			} else select = 0;
			break;
		}
		case 1: {
			if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
				/* Joytick Select pressed */
				select++;
				if(select == 1){
					changeStatus(EATING_R);
					currentSong = S_CLICK;
					playCurrentSong();
				}
			} else select = 0;
			break;
		}
		case 2: {
			if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
				/* Joytick Select pressed */
				select++;
				if(select == 1){
					changeStatus(RUNNING);
					selected = 3;
				}
			} else select = 0;

			break;
		}
		case 3: {
			if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
				/* Joytick Select pressed */
				select++;
				if(select == 1){
					currentSong = S_CLICK;
			    playCurrentSong();
					resetScreen();
					// serve Select;
				}
			} else select = 0;

			break;
		}		
		default: break;
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	
		/* Joytick left pressed */
		left++;
		if(left == 1){
			selected = 0;
		}
	} else left = 0;
	
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	
		/* Joytick down pressed */
		right++;
		if(right == 1){
			selected = 1;
		}
	} else right = 0;
	selectFood(&selected);
}


void handleTouchScreen(){
	Coordinate *Screen_Ptr , *Display_Ptr;
	Screen_Ptr = Read_Ads7846();
	Display_Ptr = &display;
	if ( Screen_Ptr == (void *)0) return;
	getDisplayPoint( Display_Ptr, Screen_Ptr, &matrix);
	
	if( Display_Ptr->x >= 50 && Display_Ptr->x < 190 &&
			Display_Ptr->y >= 120 && Display_Ptr->y < 250)
	{
		changeStatus(CUDDLES);
	}
}


void RIT_IRQHandler (void)
{			
	handleJoystick();
	handleTouchScreen();
	ADC_start_conversion();
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_joystick.h
** Descriptions:        High level joystick management functions
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "joystick.h"
#include "../led/led.h"
#include "../timer/timer.h"
#include "../utils/utils.h"


void handleJoystick(void) {
	static int select = 0;
	static int down = 0;
	static int left = 0;
	static int right = 0;
	static int up = 0;
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
		/* Joytick Select pressed */
		select++;
		if(select == 1){
			// serve Select
		}
	} else select = 0;

	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
		/* Joytick down pressed */
		down++;
		if(down == 1){
			// serve Down
		}
	} else down = 0;
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	
		/* Joytick left pressed */
		left++;
		if(left == 1){
			// serve Left
		}
	} else left = 0;
	
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	
		/* Joytick down pressed */
		right++;
		if(right == 1){
			// serve Right
		}
	} else right = 0;

	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
		/* Joytick up pressed */
		up++;
		if(up == 1){
			// serve Up
		}
	} else up = 0;
}

/*****************************************************************************
**                            End Of File
******************************************************************************/

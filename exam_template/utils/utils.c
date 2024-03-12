/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           utils.c
** Descriptions:        atomic functions to be used by higher sw levels
** Correlated files:    utils.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include "utils.h"
#include <stdlib.h>
#include "../led/led.h"

/*useful vars*/
//extern uint8_t buttons[]; /* REMEMBER: buttons[] IS AN ARRAY OF 3 ELEMENTS EACH FOR ONE BUTTON (pos=0 -> int0..). USE IT WHEN YOU HAVE TO MANAGE PARTICULAR EVENTS */

uint32_t getTicks(float seconds, float Hz){
	return seconds * Hz * 1000000;
}

float getSecByFreq(float freq){
	return 1/(2*freq);   /* FREQUENCY MULTIPLIED BY 2 ( IF A FREQ IS GIVEN 1/FREQ IS THE PERIOD AND DUTY CYCLE = 0.5) BEWARE */
}

void LED_blink_bybutton(void){   /* BLINK WITH TIMER FREQ ONLY LED0 IF KEY1 IS NOT PRESSED, BOTH LED0 AND LED1 IF KEY1 IS PRESSED*/
	static uint8_t count = 0;
	if(count == 0){
		count ++;
			if(buttons[1] == 0){
				LED_Off(1);
				LED_On(0);
			}else{
				if(buttons[1] > 0 && buttons[2] == 0){
					LED_On(0);
					LED_On(1);		
				}
			}
	}
	else{
		count--;
		LED_Off(0);
		LED_Off(1);
	}	
}

void LED_blink(uint8_t lednum){
	static uint8_t count = 0;
	
	if(count == 0){
		LED_On(lednum);
		count ++;
	}
	else{
		count--;
		LED_Off(lednum);
	}	
}

void LED_All_blink(void){
	static uint8_t count = 0;
	
	if(count == 0){
		LED_All_On();
		count ++;
	}
	else{
		count--;
		LED_All_Off();
	}	
}

void LED_blink_Diff_Time(uint8_t num, int Ticks1, int Ticks2){
	static int stayOff;
	static int stayOn;
	
	switch(ledStatus){
		
		case ON:{
			LED_On(num);
			ledStatus = HOLD_ON;
		}break;
		
		case OFF:{
			LED_Off(num);
			ledStatus = HOLD_OFF;
		}break;
		
		case HOLD_ON:{
			stayOn++;
			if(stayOn == Ticks1){ /*led on for time1= TimerPeriod * Ticks1 */
				stayOn = 0;
				ledStatus = OFF;
			}
		}break;
		
		case HOLD_OFF:{
			stayOff++;
			if(stayOff == Ticks2){ /*led off for time2= TimerPeriod * Ticks2 */
				stayOff = 0;
				ledStatus = ON;
			}
		}break;
		
		case NONE: break;
	}
}
/*****************************************************************************
**                            End Of File
******************************************************************************/

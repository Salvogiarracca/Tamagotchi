/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Descriptions:        functions to manage polling and button debouncing
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../adc/adc.h"
#include "../led/led.h"
#include "../button_EXINT/button.h"
#include "../joystick/joystick.h"
#include "../utils/utils.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/





void RIT_IRQHandler (void)
{			
	handleJoystick();
	handleButtons();
	//LED_blink_Diff_Time(0, 100, 50);   /* USAGE EXAMPLE OF THIS FUNCTION (ON FOR 100 TICKS (5 secs with 0.05 period) AN OFF FOR 50 TICKS) */
	//ADC_start_conversion();
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

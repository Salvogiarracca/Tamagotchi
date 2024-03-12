/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_joystick.c
** Descriptions:        Atomic joystick init functions
** Correlated files:    joystick.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "joystick.h"

/*----------------------------------------------------------------------------
  Function that initializes joysticks and switch them off
 *----------------------------------------------------------------------------*/

void joystick_init(void) {
	/* joystick select functionality */

  LPC_PINCON->PINSEL3 &= ~(3<<18);	//PIN mode GPIO (00b value per P1.25) SELECT
	LPC_GPIO1->FIODIR   &= ~(1<<25);	//P1.25 Input (joysticks on PORT1 defined as Input)
	
	LPC_PINCON->PINSEL3 &= ~(3<<20);	//PIN mode GPIO (00b value per P1.26) DOWN
	LPC_GPIO1->FIODIR   &= ~(1<<26);	//P1.26 Input (joysticks on PORT1 defined as Input)

	LPC_PINCON->PINSEL3 &= ~(3<<22);	//PIN mode GPIO (00b value per P1.27) LEFT
	LPC_GPIO1->FIODIR   &= ~(1<<27);	//P1.27 Input (joysticks on PORT1 defined as Input)

	LPC_PINCON->PINSEL3 &= ~(3<<24);	//PIN mode GPIO (00b value per P1.28) RIGHT
	LPC_GPIO1->FIODIR   &= ~(1<<28);	//P1.28 Input (joysticks on PORT1 defined as Input)
	
	LPC_PINCON->PINSEL3 &= ~(3<<26);	//PIN mode GPIO (00b value per P1.29) UP
	LPC_GPIO1->FIODIR   &= ~(1<<29);	//P1.29 Input (joysticks on PORT1 defined as Input)
}

/*****************************************************************************
**                            End Of File
******************************************************************************/

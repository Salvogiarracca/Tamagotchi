/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_led.c
** Descriptions:        High level led management functions
** Correlated files:    led.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "led.h"

#define LED_NUM     8                   /* Number of user LEDs                */

const unsigned long led_mask[] = { 1UL<<0, 1UL<<1, 1UL<<2, 1UL<< 3, 1UL<< 4, 1UL<< 5, 1UL<< 6, 1UL<< 7 };	/*from right to left*/
const unsigned long led_mask_schematic[] = { 1UL<<7, 1UL<<6, 1UL<<5, 1UL<< 4, 1UL<< 3, 1UL<< 2, 1UL<< 1, 1UL<< 0 };	/*from left to right*/

extern unsigned char led_value;

/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void LED_On(unsigned int num) {
 
  LPC_GPIO2->FIOPIN |= led_mask[num];
	led_value = LPC_GPIO2->FIOPIN;
}

/*----------------------------------------------------------------------------
  Function that turns on requested LED according to the schematic (from 4 to 11)
 *----------------------------------------------------------------------------*/
void LED_On_Schematic(unsigned int num) {
 
  LPC_GPIO2->FIOPIN |= led_mask_schematic[num-4];
	led_value = LPC_GPIO2->FIOPIN;
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED_Off(unsigned int num) {

  LPC_GPIO2->FIOPIN &= ~led_mask[num];
	led_value = LPC_GPIO2->FIOPIN;
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED_Off_Schematic(unsigned int num) {

  LPC_GPIO2->FIOPIN &= ~led_mask_schematic[num-4];
	led_value = LPC_GPIO2->FIOPIN;
}

/*----------------------------------------------------------------------------
  Function that outputs value to LEDs
 *----------------------------------------------------------------------------*/
void LED_Out(unsigned int value) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (value & (1<<i)) {
      LED_On (i);
    } else {
      LED_Off(i);
    }
  }
	led_value = value;
}

/*----------------------------------------------------------------------------
  Function that outputs value to LEDs in right position without change other leds
 *----------------------------------------------------------------------------*/
void LED_Out_byIndexes(unsigned int value, unsigned int leftBound, unsigned int rightBound) {
  int i;
	char tmp_value;

	tmp_value = value << rightBound;
  for (i = rightBound; i < leftBound + 1; i++) {
    if (tmp_value & (1<<i)) {
      LED_On (i);
    }
		else
			LED_Off(i);
  }
	led_value = value;
}

/*----------------------------------------------------------------------------
  Function that turn off LEDs switched on by previously LED_Out(val)
 *----------------------------------------------------------------------------*/
void LED_Out_inv(unsigned int value) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (value & (1<<i)) {
      LED_Off (i);
    }
  }
	led_value = value;
}

/*----------------------------------------------------------------------------
  All LEDs ON
 *----------------------------------------------------------------------------*/
void LED_All_On(void){
	LPC_GPIO2->FIOSET = 0x000000FF;
}

/*----------------------------------------------------------------------------
  All LEDs OFF
 *----------------------------------------------------------------------------*/
void LED_All_Off(void){
	LPC_GPIO2->FIOCLR = 0x000000FF;
}
/*****************************************************************************
**                            End Of File
******************************************************************************/

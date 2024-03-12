/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           led.h
** Descriptions:        Prototypes of functions included in the lib_led, funct_led .c files
** Correlated files:    lib_led.c, funct_led.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#ifndef __LED_H
#define __LED_H

/* lib_led */
void LED_init(void);
void LED_deinit(void);

/* funct_led */
void LED_On (unsigned int num);
void LED_On_Schematic(unsigned int num);
void LED_Off (unsigned int num);
void LED_Off_Schematic (unsigned int num);
void LED_Out(unsigned int value);
void LED_Out_byIndexes(unsigned int value, unsigned int leftBound, unsigned int rightBound); /* leftBound and rightBound are the boundaries of the value (example: 9 in the Most Significant Nibble 1001XXXX) leftBound = 7 and rightBound = 4 */
void LED_Out_inv(unsigned int value); /* Function that turn off LEDs switched on by previously LED_Out(val) */
void LED_All_On(void);
void LED_All_Off(void);

#endif
/*****************************************************************************
**                            End Of File
******************************************************************************/

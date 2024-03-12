/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           button.h
** Descriptions:        Prototypes of functions included in the lib_button.c, IRQ_button.c files
** Correlated files:    lib_button.c, IRQ_button.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#ifndef __BUTTON_H
#define __BUTTON_H

/* lib_button */
void BUTTON_init(void);

/* IRQ_button */
void EINT0_IRQHandler(void);
void EINT1_IRQHandler(void);
void EINT2_IRQHandler(void);

/* func_button */
void handleButtons(void);

#endif
/*****************************************************************************
**                            End Of File
******************************************************************************/

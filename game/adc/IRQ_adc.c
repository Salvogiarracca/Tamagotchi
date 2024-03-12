/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#include "../timer/timer.h"
#include "lpc17xx.h"
#include "adc.h"
#include "../Images/Img.h"

#define AD_max  0xFFF
#define AD_half 0x7FF

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/
 enum VOLUME{
	MUTE,
	LOW,
	MEDIUM,
	HIGH
 };

unsigned short AD_val;   
unsigned short AD_last;     /* Last converted value               */
extern uint8_t volume;

void ADC_IRQHandler(void) {
	static uint8_t currentVolume;
	AD_val = ((LPC_ADC->ADGDR>>4) & AD_max); /* Read Conversion Result */
	if(AD_val != AD_last){	
		currentVolume = AD_val*4/AD_max;
		getVol(currentVolume);
		switch (currentVolume){
			case MUTE: {
				volume = 0;
				break;
			}
			case LOW: {
				volume = 33;
				break;
			}
			case MEDIUM: {
				volume = 66;
				break;
			}
			case HIGH: {
				volume = 100;
				break;
			}
			default: break;
		}

		AD_last = AD_val;
	}
}

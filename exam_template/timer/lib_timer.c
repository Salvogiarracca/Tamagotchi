/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_timer.c
** Descriptions:        atomic functions to be used by higher sw levels
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1 or 2 or 3
** Returned value:		None
**
******************************************************************************/
void enable_timer( uint8_t timer_num )
{
  switch(timer_num){
		case 0: LPC_TIM0->TCR = 1; break;
		case 1: LPC_TIM1->TCR = 1; break;
		case 2: LPC_TIM2->TCR = 1; break;
		case 3: LPC_TIM3->TCR = 1; break;
		default: break;
	}
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1 or 2 or 3
** Returned value:		None
**
******************************************************************************/
void disable_timer( uint8_t timer_num )
{
  switch(timer_num){
		case 0: LPC_TIM0->TCR = 0; break;
		case 1: LPC_TIM1->TCR = 0; break;
		case 2: LPC_TIM2->TCR = 0; break;
		case 3: LPC_TIM3->TCR = 0; break;
		default: break;
	}
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1 or 2 or 3
** Returned value:		None
**
******************************************************************************/
void reset_timer( uint8_t timer_num )
{
  uint32_t regVal;
	switch(timer_num){
		case 0:
			regVal = LPC_TIM0->TCR;
			regVal |= 0x02;
			LPC_TIM0->TCR = regVal;
		break;
		case 1: 
			regVal = LPC_TIM1->TCR;
			regVal |= 0x02;
			LPC_TIM1->TCR = regVal;
		break;
		case 2:
			regVal = LPC_TIM2->TCR;
			regVal |= 0x02;
			LPC_TIM2->TCR = regVal;
		break;
		case 3:
			regVal = LPC_TIM3->TCR;
			regVal |= 0x02;
			LPC_TIM3->TCR = regVal;
		break;
		default: break;
	}
}

/******************************************************************************
** Function name:		init_timer
**
** Descriptions:		Init Timer
**
** parameters:			timer number: 0 or 1 or 2 or 3
** Returned value:		uint32_t 1 or 0
**
******************************************************************************/
uint32_t init_timer ( uint8_t timer_num, uint32_t TimerInterval )
{
//*** <<< Use Configuration Wizard in Context Menu >>> ***
  if ( timer_num == 0 )
	{
	LPC_TIM0->MR0 = TimerInterval;
// <h> timer0 MCR
//   <e.0> MR0I
//	 <i> 1 Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC. 0
//	 <i> 0 This interrupt is disabled
//   </e>
//   <e.1> MR0R
//	 <i> 1 Reset on MR0: the TC will be reset if MR0 matches it.
//	 <i> 0 Feature disabled.
//   </e>
//   <e.2> MR0S
//	 <i> 1 Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC
//	 <i> 0 Feature disabled.
//   </e>
	LPC_TIM0->MCR = 0;				/* Interrupt and Reset on MR0 */
// </h>
	NVIC_EnableIRQ(TIMER0_IRQn);
	NVIC_SetPriority(TIMER0_IRQn, 0); 
	return (1);
	}
	else if ( timer_num == 1 )
	{
	LPC_TIM1->MR0 = TimerInterval;
// <h> timer1 MCR
//   <e.0> MR0I
//	 <i> 1 Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC. 0
//	 <i> 0 This interrupt is disabled
//   </e>
//   <e.1> MR0R
//	 <i> 1 Reset on MR0: the TC will be reset if MR0 matches it.
//	 <i> 0 Feature disabled.
//   </e>
//   <e.2> MR0S
//	 <i> 1 Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC
//	 <i> 0 Feature disabled.
//   </e>
	LPC_TIM1->MCR = 0;				/* Interrupt and Reset on MR0 */
// </h>
	NVIC_EnableIRQ(TIMER1_IRQn);
	NVIC_SetPriority(TIMER1_IRQn, 0); 
	return (1);
	}
	else if ( timer_num == 2 )
	{
	LPC_TIM2->MR0 = TimerInterval;
// <h> timer2 MCR
//   <e.0> MR0I
//	 <i> 1 Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC. 0
//	 <i> 0 This interrupt is disabled
//   </e>
//   <e.1> MR0R
//	 <i> 1 Reset on MR0: the TC will be reset if MR0 matches it.
//	 <i> 0 Feature disabled.
//   </e>
//   <e.2> MR0S
//	 <i> 1 Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC
//	 <i> 0 Feature disabled.
//   </e>
	LPC_TIM2->MCR = 0;				/* Interrupt and Reset on MR0 */
// </h>
	NVIC_EnableIRQ(TIMER2_IRQn);
	NVIC_SetPriority(TIMER2_IRQn, 0);  
	return (1);
	}
	else if ( timer_num == 3 )
	{
	LPC_TIM3->MR0 = TimerInterval;
// <h> timer3 MCR
//   <e.0> MR0I
//	 <i> 1 Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC. 0
//	 <i> 0 This interrupt is disabled
//   </e>
//   <e.1> MR0R
//	 <i> 1 Reset on MR0: the TC will be reset if MR0 matches it.
//	 <i> 0 Feature disabled.
//   </e>
//   <e.2> MR0S
//	 <i> 1 Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC
//	 <i> 0 Feature disabled.
//   </e>
	LPC_TIM3->MCR = 0;				/* Interrupt and Reset on MR0 */
// </h>
	NVIC_EnableIRQ(TIMER3_IRQn);
	NVIC_SetPriority(TIMER3_IRQn, 0);  
	return (1);
	}
	return (0);
}
//*** <<< end of configuration section >>>    ***
/******************************************************************************
**                            End Of File
******************************************************************************/

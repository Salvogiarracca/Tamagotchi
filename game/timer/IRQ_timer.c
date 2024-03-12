/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"
#include "../RIT/RIT.h"
#include "../ProjectFunctions/myfunctions.h"
#include "../GLCD/GLCD.h"
#include "../TouchPanel/TouchPanel.h"
#include "../Images/Img.h"
#include "../adc/adc.h"
#include "../music/audio.h"
#include <stdio.h>

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern uint8_t hh,mm,ss;
extern uint8_t tamagotchi_STATUS;
extern uint8_t prevStatus;
uint8_t happiness_count;
uint8_t satiety_count;
static uint8_t imgWalkNum;
static uint8_t imgEatNum;
static uint8_t imgRunNum;
static uint8_t imgCudNum;
static uint8_t repeater;
static uint8_t revYell;
extern uint16_t BgColor;
extern uint8_t currentSong;
extern uint8_t volume;
int number;

uint16_t SinTable[45] =                                       
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};

enum DOG_STATE{
	WALKING = 0,
	EATING_L = 1,
	EATING_R = 2,
	RUNNING = 3,
	RESET = 4,
	CUDDLES = 5
};

/*TIMER0 HANDLER FOR AGE*/

extern uint8_t volume;


void TIMER0_IRQHandler (void)
{
	ss++;
	if(ss==60){
		ss=0;
		mm++;
		if(mm==60){
			mm=0;
			hh++;}
	}
	updateAge();
	happiness_count++;
	satiety_count++;
	
	if(happiness_count==5){
		updateBattery("HAPPINESS", '-');
		happiness_count=0;
	}
	if(satiety_count==5){
		updateBattery("SATIETY", '-');
		satiety_count=0;
	}

  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
/*TIMER1 ANIMATION HANDLER*/
void TIMER1_IRQHandler (void)
{
	static uint8_t eating_count;
	static uint8_t running_count;
	
  switch(tamagotchi_STATUS){
		case WALKING:{
			currentSong = S_NONE;
			number = 0;
			if(prevStatus != RUNNING || prevStatus != RESET){
				imgWalkNum++;
				if(imgWalkNum > 2){
					imgWalkNum = 1;
					getImage(&imgWalkNum, 'w');
				}
				else{
					getImage(&imgWalkNum, 'w');
				}
			}
			break;
		}
		
		case EATING_L:{
			disable_timer(0);
			number++;
			if(number == 1){
				currentSong = S_MEAL;
				playCurrentSong();		
			}
			imgEatNum++;
			if(imgEatNum == 4){
				getImageRev(&imgEatNum, 'e');
				imgEatNum=0;
			}
			else
				getImageRev(&imgEatNum, 'e');
			eating_count++;
			if(eating_count == 4){
				updateBattery("SATIETY", '+');
				eating_count = 0;
				satiety_count=0;
				changeStatus(WALKING);
				enable_timer(0);
			}
			break;
		}
		
		case EATING_R:{
			disable_timer(0);
			number++;
			if(number == 1){
			  currentSong = S_SNACK;
				playCurrentSong();
			}
			imgEatNum++;
			if(imgEatNum == 4){
				getImage(&imgEatNum, 'e');
				imgEatNum=0;
			}
			else
				getImage(&imgEatNum, 'e');
			eating_count++;
			if(eating_count == 4){
				updateBattery("HAPPINESS", '+');
				eating_count = 0;
				happiness_count = 0;
				changeStatus(WALKING);
				enable_timer(0);
			}
			break;
		}
		
		case RUNNING:{
			disable_timer(0);
			disable_RIT();
			imgRunNum++;
			if(imgRunNum == 4){
				getImage(&imgRunNum, 'r');
				imgRunNum=0;
			}
			else{
				if(imgRunNum == 2 && !revYell){
					imgRunNum--;
					getImageRev(&imgRunNum, 'r');
					revYell=1;
				}
				else	
					getImage(&imgRunNum, 'r');
			}
			running_count++;
			if(running_count == 5){
				currentSong = S_ESCAPE;
				playCurrentSong();
				running_count = 0;
				changeStatus(RESET);
				LCD_DrawRectangle(0,120, 240, 200, BgColor);
				drawEmptyRectangle(0,270,240,50,Red); 
				GUI_Text(23, 140, (uint8_t *)"Courage the Cowardly dog", Black, BgColor);
				GUI_Text(23, 160, (uint8_t *)"has escaped. Take better", Black, BgColor);
				GUI_Text(23, 180, (uint8_t *)"care of him next time!", Black, BgColor);
				GUI_Text(100,284,(uint8_t *)"RESET",Black,BgColor);
				enable_RIT();
				disable_timer(1);
			}
			break;
		}
		
		case CUDDLES:{
			if(prevStatus != RUNNING || prevStatus != RESET){
				
				number++;
			  if(number == 1){
					currentSong = S_CUDDLE;
				  playCurrentSong();
				}
				if(repeater < 2 ){
					imgCudNum++;
					if(imgCudNum == 2){
						getImage(&imgCudNum, 'c');
						imgCudNum = 0;
						repeater++;
					}
					else
						getImage(&imgCudNum, 'c');
				}
				else{
					repeater = 0 ;
					updateBattery("HAPPINESS", '+');
					happiness_count = 0;
					changeStatus(WALKING);
				}
			}
			break;
		}
		
		default: break;
	}
	
	
	LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 2 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
/*SINUSOIDAL WAVE*/
void TIMER2_IRQHandler (void)
{	
	static int sineticks = 0;
	static int currentValue; 
	
	/* DAC management */	
	currentValue = SinTable[sineticks];
	
	LPC_DAC->DACR = ((uint32_t)((currentValue*1024/819 )*volume/100))<< 6;	
	sineticks++;
	if(sineticks==45) sineticks=0;
  
	LPC_TIM2->IR |= 1;			/* clear interrupt flag */ 
}

/******************************************************************************
** Function name:		Timer3_IRQHandler
**
** Descriptions:		Timer/Counter 3 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
/*NOTE TIMER*/
void TIMER3_IRQHandler (void)
{
	disable_timer(2);
	if(currentSong != S_NONE){
		playCurrentSong();
	}
  LPC_TIM3->IR |= 1;			/* clear interrupt flag */
}
/******************************************************************************
**                            End Of File
******************************************************************************/

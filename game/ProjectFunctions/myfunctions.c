#include "LPC17xx.h"
#include "../GLCD/GLCD.h"
#include "../TouchPanel/TouchPanel.h"
#include "../timer/timer.h"
#include "../RIT/RIT.h"
#include "myfunctions.h"
#include "../music/music.h"
#include "../music/audio.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define Warning_Red 	 0xC980
#define Warning_Pink   0xFCCC
#define Warning_Yellow 0xFE60
#define Warning_LGreen 0x9E66
#define Warning_Green  0x34C0
#define UPTICKS 1

int selected=-1;
extern uint16_t BgColor;
extern uint8_t hh,mm,ss;
extern uint8_t happiness,satiety;
static char timeString[15];
static uint8_t HAPPINESS_STATUS;
static uint8_t SATIETY_STATUS;
uint8_t tamagotchi_STATUS;
uint8_t prevStatus = 0;
const int freqs[8]={2120,1890,1684,1592,1417,1263,1125,1062};
extern uint8_t currentSong;
static int currentNote = 0;

NOTE song[] = 
{
	// 1
	{d3, time_semicroma},
	{d3, time_semicroma},
	{d4, time_croma},
	{a3, time_croma},
	{pause, time_semicroma},
	{a3b, time_semicroma},
	{pause, time_semicroma},
	{g3, time_croma},
	{f3, time_semicroma},
	{d3, time_semicroma},
	{f3, time_semicroma},
	{g3, time_semicroma}
};


enum BATTERY_VALUES {
	FULL=100,M_HIGH=75,M_LOW=50,LOW=25,EMPTY=0,
};

enum COLOR_STATUS {
	S_FULL=Warning_Green,
	S_M_HIGH=Warning_LGreen,
	S_M_LOW=Warning_Yellow,
	S_LOW=Warning_Pink,
	S_EMPTY=Warning_Red,
};

enum BATTERY_TYPE{
	HAPPINESS=0,
	SATIETY=1
};



enum DOG_STATE{
	WALKING = 0,
	EATING_L = 1,
	EATING_R = 2,
	RUNNING = 3,
	RESET = 4,
	CUDDLES = 5
};
void drawEmptyRectangle(uint16_t X_pos,uint16_t Y_pos, uint16_t width, uint16_t height, uint16_t color){
	uint16_t i,j;
	for(i=0;i<height;i++){
		if(i==0||i==(height-1)){
			j = i==(height-1)?Y_pos+height-1:Y_pos;
			LCD_DrawLine(X_pos,j,X_pos+width-1,j,color);
		}else{
			LCD_SetPoint(X_pos,Y_pos+i,color);
			LCD_SetPoint(X_pos+width-1,Y_pos+i,color);
		}
	}
}


void drawAgeWidget(){
	snprintf(timeString,15*(sizeof(char)),"Age: %02d:%02d:%02d",hh,mm,ss);
	GUI_Text(70,16,(uint8_t*)timeString,Black,BgColor);
}
void drawBattery(uint16_t X_pos,uint16_t Y_pos,uint16_t width,uint16_t height, uint16_t color){
	drawEmptyRectangle(X_pos,Y_pos,width,height,color);
	LCD_DrawRectangle(X_pos+width,Y_pos+4,2,height-8,color);
}
void drawBarLevels(uint8_t type,uint8_t value){
	uint16_t x=0,y=0,i=0,color;
	uint8_t rectNum;
	
	switch(value){
		case FULL:{
			rectNum=4;
			color=S_FULL;
			break;
		}
		case M_HIGH:{
			rectNum=3;
			color=S_M_HIGH;
			break;
		}
		case M_LOW:{
			rectNum=2;
			color=S_M_LOW;
			break;
		}
		case LOW:{
			rectNum=1;
			color=S_LOW;
			break;
		}
		case EMPTY:{
			rectNum=0;
			color=S_EMPTY;
			break;
		}
	}
	if(type==HAPPINESS){
		x=28;
		y=67;
	}else{
		x=148;
		y=67;
	}
	
	if(rectNum==0){
		if(type==HAPPINESS){
			drawBattery(25,65,60,30,color);
		}else{
			drawBattery(145,65,60,30,color);
		}
	
	}
	for(;i<4;i++){
		LCD_DrawRectangle(x,y,12,26,(i+1>rectNum)?BgColor:color);
		x+=14;
	}
}


void drawHappinessAndSatiety(){
	GUI_Text(22,40,(uint8_t*)"Happiness",Black,BgColor);
	GUI_Text(150,40,(uint8_t*)"Satiety",Black,BgColor);

	drawBattery(25,65,60,30,Black);
	drawBattery(145,65,60,30,Black);
	
	HAPPINESS_STATUS = FULL;
	SATIETY_STATUS = FULL;
	drawBarLevels(HAPPINESS,HAPPINESS_STATUS);
	drawBarLevels(SATIETY,SATIETY_STATUS);
}
void drawActionButtons(){
	drawEmptyRectangle(0,270,120,50,Black);
	drawEmptyRectangle(120,270,120,50,Black);
	GUI_Text(10,284,(uint8_t*)"MEAL",Black,BgColor);
	GUI_Text(130,284,(uint8_t*)"SNACK",Black,BgColor);
}


void selectFood(int *food){
	if(*food==0){
		drawEmptyRectangle(0,270,120,50,Red);
		drawEmptyRectangle(120,270,120,50,Black);
	}
	if(*food==1){
		drawEmptyRectangle(120,270,120,50,Red);
		drawEmptyRectangle(0,270,120,50,Black);
	}
	selected = *food;
}
void updateAge(){
	snprintf(timeString,15*(sizeof(char)),"Age: %02d:%02d:%02d",hh,mm,ss);
	GUI_Text(70,16,(uint8_t*)timeString,Black,BgColor);
}
void resetScreen(){
	disable_RIT();
	LCD_Clear(BgColor);
	ss=mm=hh=0;
	drawAgeWidget();
	selected = -1;
	drawHappinessAndSatiety();
	drawActionButtons();
	reset_timer(0);
	enable_timer(0);
	reset_timer(1);
	enable_timer(1);
	reset_RIT();
	enable_RIT();
	changeStatus(0);
}

void updateBattery(char *battID, char mode){
	
	if(strcmp(battID, "HAPPINESS")==0){
		if(mode=='-' && HAPPINESS_STATUS!=EMPTY){
			HAPPINESS_STATUS -= 25;
			drawBarLevels(HAPPINESS,HAPPINESS_STATUS);
		}

		if(mode=='+' && HAPPINESS_STATUS!=FULL){
			HAPPINESS_STATUS += 25;
			drawBarLevels(HAPPINESS,HAPPINESS_STATUS);
		}
	}
	if(strcmp(battID, "SATIETY")==0){
		if(mode=='-' && SATIETY_STATUS!=EMPTY){
			SATIETY_STATUS -= 25;
			drawBarLevels(SATIETY,SATIETY_STATUS);
		}

		if(mode=='+' && SATIETY_STATUS!=FULL){
			SATIETY_STATUS += 25;
			drawBarLevels(SATIETY,SATIETY_STATUS);
		}		
	}
	
	if(HAPPINESS_STATUS == 0 || SATIETY_STATUS == 0){
		changeStatus(RUNNING);
		selected = 2;
	}	
}
void changeStatus(uint8_t status){
	prevStatus = tamagotchi_STATUS;
	tamagotchi_STATUS = status;
}

void playCurrentSong(){
	
	static SONG_t *song = NULL;

	if(song == NULL){ 
		song = getSong(currentSong);
		if(song == NULL) return;
	}
	
	if(currentNote == (song->length)){
		currentSong = S_NONE;
		currentNote = 0;
		song = NULL;
		
		disable_timer(2); 
		LPC_TIM2->IR = 0;
		
		reset_timer(3);
		disable_timer(3);

		return;
	}
	disable_timer(3);
	if(!isNotePlaying()){
		playNote(song->notes[ currentNote++ ]);
	}
	return;
}


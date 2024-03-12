#include "LPC17xx.h"



void drawEmptyRectangle(uint16_t X_pos,uint16_t Y_pos, uint16_t width, uint16_t height, uint16_t color);
void drawAgeWidget(void);
void drawHappinessAndSatiety(void);
void drawActionButtons(void);
void changeStatus(uint8_t status);
void updateAge(void);
void updateBattery(char *battID, char mode);
void selectFood(int *food);
void resetScreen(void);
//void playsong(void);
void playCurrentSong(void);

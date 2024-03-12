#include "audio.h"
#include <stdlib.h>

//MEAL
const NOTE s_meal_notes[]={
	{ c4, time_semicroma },
	{ d4, time_semicroma },
	{ f4, time_semicroma },
	{ d4, time_semicroma },
	{ a4, time_croma },
	{ a4, time_semicroma },
	{ a4, time_semicroma }
};
const SONG_t s_meal = {(NOTE *)s_meal_notes, 7};

//SNACK 
const NOTE s_snack_notes[]={
	{ c4, time_semicroma },
	{ d4, time_semicroma },
	{ f4, time_semicroma },
	{ d4, time_semicroma },
	{ a4, time_croma },
	{ a4, time_semicroma },
	{ a4, time_semicroma }
};
const SONG_t s_snack = {(NOTE *)s_snack_notes, 7};

//CLICK
const NOTE s_click_notes[]={
	{f4,time_semiminima}
};
const SONG_t s_click = {(NOTE *)s_click_notes, 1};

//CUDDLE
const NOTE s_cuddle_notes[]={
	{ c4, time_semicroma },
	{ d4, time_semicroma },
	{ f4, time_semicroma },
	{ d4, time_semicroma },
	{ g4, time_croma },
	{ g4, time_semicroma },
	{ g4, time_semicroma },
	{ g4, time_croma }
};
const SONG_t s_cuddle = {(NOTE *)s_cuddle_notes, 8};

//ESCAPE
const NOTE s_escape_notes[]={
	{ c4, time_semicroma },
	{ d4, time_semicroma },
	{ f4, time_semicroma },
	{ d4, time_semicroma },
	{ a4, time_croma },
	{ a4, time_semicroma },
	{ a4, time_semicroma },
	{ a4, time_croma },
	{ g4, time_croma },
	{ g4, time_semiminima },
	{ c4, time_semicroma },
	{ d4, time_semicroma },
	{ f4, time_semicroma },
	{ d4, time_semicroma },
	{ g4, time_croma },
	{ g4, time_semicroma },
	{ g4, time_semicroma },
	{ g4, time_croma },
	{ f4, time_croma },
	{ f4, time_semicroma },
	{ e4, time_semicroma },
	{ d4, time_croma },
	{ c4, time_semicroma },
	{ d4, time_semicroma },
	{ f4, time_semicroma },
	{ d4, time_semicroma },
	{ f4, time_semiminima },
	{ g4, time_croma },
	{ e4, time_croma },
	{ e4, time_semicroma },
	{ d4, time_semicroma },
	{ c4, time_semiminima },
	{ c4, time_croma },
	{ g4, time_semiminima },
	{ f4, time_minima }
};
const SONG_t s_escape = {(NOTE *)s_escape_notes, 35};

SONG_t *getSong(uint8_t songEnum){
	switch(songEnum){
		case S_MEAL:{
			return (SONG_t *) & s_meal;
		}
		case S_SNACK:{
			return (SONG_t *) & s_snack;
		}
		case S_CLICK:{
			return (SONG_t *) & s_click;
		}
		case S_CUDDLE:{
			return (SONG_t *) & s_cuddle;
		}
		case S_ESCAPE:{
			return (SONG_t *) & s_escape;
		}
	}
	return NULL;
}

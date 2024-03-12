#ifndef AUDIO_H
#define AUDIO_H

#include "LPC17XX.h"
#include "../music/music.h"

enum SONGS_E{
	S_NONE,
	S_MEAL,
	S_SNACK,
	S_CUDDLE,
	S_CLICK,
	S_ESCAPE
};

typedef struct {
	NOTE *notes;
	uint32_t length;
} SONG_t;

SONG_t* getSong(uint8_t songEnum);

#endif

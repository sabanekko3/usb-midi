#ifndef _TONES_CONTROL_H_
#define _TONES_CONTROL_H_

#include "pwm_tone.h"

#define TONES_N 8

typedef enum tone_pin{
    TONE0,
    TONE1,
    TONE2,
    TONE3,
    TONE4,
    TONE5,
    TONE6,
    TONE7,
    tone_pin_n,
}tone_pin_t;

typedef struct tone_state{
    bool is_playing;
    uint32_t tone;
}tone_state_t;

void tones_init(void);

bool tones_delete(uint32_t tone);

bool tones_new(uint32_t tone,uint32_t velocity);

void tones_all_delete(void);

#endif //_TONES_CONTROL_H_
#pragma once

#include "pwm_tone.h"

#include "bsp/board.h"
#include "tusb.h"

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

const uint32_t tone_out_pin[tone_pin_n] = {
    16,
    18,
    20,
    22,
    8,
    26,
    28,
    14,
};

typedef struct tone_state{
    bool is_playing;
    uint32_t tone;
}tone_state_t;

void tones_init(void);

bool tones_delete(uint32_t tone);

bool tones_new(uint32_t tone,uint32_t velocity);

void tones_all_delete(void);
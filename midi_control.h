#pragma once

#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"

#define MIDI_BUFF_N 16

typedef enum midi_event{
    NOTE_OFF = 8,
    NOTE_ON = 9,
}midi_event_t;

typedef struct midi_message{
    midi_event_t event;
    uint32_t ch;
    uint32_t tone;
    uint32_t velocity;
}midi_message_t;

void midi_init(void);

void midi_task(void);

uint32_t midi_message_available(void);

midi_message_t midi_get_message(void);


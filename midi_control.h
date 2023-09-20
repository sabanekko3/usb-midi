#pragma once

#include "bsp/board.h"
#include "tusb.h"

#include "pwm_tone.h"

bool print_midi_event(const uint8_t msg[3]);

void dump_message(const uint8_t msg[3], int n_data);

void midi_task(void);
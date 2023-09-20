#pragma once

#include "hardware/pwm.h"
#include "pico/stdlib.h"

#include <math.h>

#define PWM_TIMER_CLOCK 2.0e6

void tone_init(uint32_t GPIO_num);
bool set_tone(uint32_t GPIO_num,uint32_t tone_num);
bool set_freq(uint32_t GPIO_num,float freq);
void tone_stop(uint32_t GPIO_num);

#ifndef _PWM_TONE_H_
#define _PWM_TONE_H_

#include "hardware/pwm.h"
#include "pico/stdlib.h"

#include <math.h>

#define PWM_TIMER_CLOCK 2.0e6

void tone_init(uint32_t GPIO_num);
bool set_tone(uint32_t GPIO_num,uint32_t tone_num,uint32_t velocity);
bool set_freq(uint32_t GPIO_num,float freq,uint32_t velocity);
void tone_stop(uint32_t GPIO_num);

#endif //_PWM_TONE_H_
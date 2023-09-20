#include "pwm_tone.h"


void tone_init(uint32_t GPIO_num){
    uint32_t slice_num = pwm_gpio_to_slice_num(GPIO_num);
    uint32_t ch_num = pwm_gpio_to_channel(GPIO_num);

    gpio_set_function(GPIO_num, GPIO_FUNC_PWM);
    //pwm clock = 2MHz
    pwm_set_clkdiv(slice_num, 125/2);
    pwm_set_enabled(slice_num, false);
}
bool set_tone(uint32_t GPIO_num,uint32_t tone_num){
    uint32_t slice_num = pwm_gpio_to_slice_num(GPIO_num);
    uint32_t ch_num = pwm_gpio_to_channel(GPIO_num);

    float freq = 0.0f;
    // if(tone_num-69 < 0){
    //     
    // }else{
    //     freq  = powf(2,(tone_num-69)/12) * 440;
    // }
    freq  = powf(2,((float)tone_num+3.0)/12.0) * 6.875;

    if(freq < 31.0f){
        return false;
    }
    float pwm_period = PWM_TIMER_CLOCK / freq - 1;
    float pwm_ch_level = pwm_period * 0.01;
 
    pwm_set_wrap(slice_num, (int)pwm_period);
    pwm_set_chan_level(slice_num,ch_num, 100);
    pwm_set_enabled(slice_num, true);
    return true;
}
bool set_freq(uint32_t GPIO_num,float freq){
    uint32_t slice_num = pwm_gpio_to_slice_num(GPIO_num);
    uint32_t ch_num = pwm_gpio_to_channel(GPIO_num);

    if(freq < 31.0f){
        return false;
    }
    float pwm_period = PWM_TIMER_CLOCK / freq - 1;
    float pwm_ch_level = pwm_period * 0.01;
 
    pwm_set_wrap(slice_num, (int)pwm_period);
    pwm_set_chan_level(slice_num,ch_num, 100);
    pwm_set_enabled(slice_num, true);
    return true;
}
void tone_stop(uint32_t GPIO_num){
    uint32_t slice_num = pwm_gpio_to_slice_num(GPIO_num);
    uint32_t ch_num = pwm_gpio_to_channel(GPIO_num);
    pwm_set_enabled(slice_num, false);
}
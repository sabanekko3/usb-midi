#include "tones_control.h"

static tone_state_t tone_state_array[tone_pin_n];

void tones_init(void){
    for(int i=0; i<tone_pin_n; i++){
        tone_state_array[i].is_playing = false;
        tone_state_array[i].tone = 0;
        tone_init(tone_out_pin[i]);
    }
}

bool tones_delete(uint32_t tone){
    for(int i = 0; i < tone_pin_n; i++){
        if((tone_state_array[i].tone == tone) && tone_state_array[i].is_playing){
            tone_stop(tone_out_pin[i]);
            tone_state_array[i].is_playing = false;
            return true;
        }
    }
    return false;
}

bool tones_new(uint32_t tone,uint32_t velocity){
    // for(int i = 0; i < tone_pin_n; i++){
    //     if(tone_state_array[i].tone == tone){
    //         return false;
    //     }
    // }
    for(int i = 0; i < tone_pin_n; i++){
        if(!tone_state_array[i].is_playing){
            set_tone(tone_out_pin[i],tone);
            tone_state_array[i].tone = tone;
            tone_state_array[i].is_playing = true;
            return true;
        }
    }
    return false;
}

void tones_all_delete(void){
    for(uint8_t i = 0; i < tone_pin_n; i++){
        tone_delete(tone_out_pin[i]);
        tone_state_array[i].is_playing = false;
    }
    tones_init();
}
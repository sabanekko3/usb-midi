#include "midi_control.h"

static midi_message_t midi_decode(uint8_t *msg);

midi_message_t midi_buff[MIDI_BUFF_N];
bool midi_buff_is_free[MIDI_BUFF_N];
static uint32_t midi_buff_head = 0;
static uint32_t midi_buff_tail = 0;

void midi_inti(void){
    for(int i = 0; i < MIDI_BUFF_N; i++){
        midi_buff[i].event = 0;
        midi_buff[i].ch = 0;
        midi_buff[i].tone = 0;
        midi_buff[i].velocity = 0;

        midi_buff_is_free[i] = true;
    }
}

void midi_task(void)
{
    uint8_t msg[3] = {0};

    while (tud_midi_n_available(0, 0))
    {
        tud_midi_read(msg, 3);
        midi_buff[midi_buff_head] = midi_decode(msg);
        midi_buff_is_free[midi_buff_head] = false;
        midi_buff_head = (midi_buff_head + 1)&(MIDI_BUFF_N-1);
    }
}

uint32_t midi_message_available(void){
    uint32_t count = 0;
    for(int i = 0; i<MIDI_BUFF_N; i++){
        if(!midi_buff_is_free[i]){
            count ++;
        }
    }
    return count;
}
midi_message_t midi_get_message(void){
    midi_message_t rtn = midi_buff[midi_buff_tail];
    midi_buff_is_free[midi_buff_tail] = true;
    midi_buff_tail = (midi_buff_tail + 1)&(MIDI_BUFF_N-1);

    return rtn;
}

static midi_message_t midi_decode(uint8_t *msg){
    midi_message_t midi_msg;
    midi_msg.event = msg[0] >> 4;
    midi_msg.ch = msg[0] & 0xF;
    midi_msg.tone = msg[1];
    midi_msg.velocity = msg[2];
    return midi_msg;
}
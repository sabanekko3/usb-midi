#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "tones_control.h"
#include "midi_control.h"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9



int main(void)
{
    stdio_init_all();
    board_init();
    tusb_init();

    // I2C Initialisation. Using it at 400Khz.
    // i2c_init(I2C_PORT, 400*1000);
    
    // gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    // gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    // gpio_pull_up(I2C_SDA);
    // gpio_pull_up(I2C_SCL);

    tones_init();

    adc_init();
    adc_gpio_init(28);
    adc_select_input(2);    
    int adc_data = 0;
    while(1){
        // tud_task();
        // midi_task();
        // while(midi_message_available()){
        //     midi_message_t new_message = midi_get_message();
        //     switch (new_message.event){
        //     case NOTE_OFF:
        //         board_led_off();
        //         tones_delete(new_message.tone);
        //         //tones_all_delete();
        //         break;
        //     case NOTE_ON:
        //         board_led_on();
        //         tones_new(new_message.tone,new_message.velocity);
        //         break;
        //     default:
        //         //nop
        //         break;
        //     }
        // }
        int tmp = adc_data;
        adc_data = adc_read();
        if(adc_data != tmp){
            tones_delete(tmp >> 5);
            tones_new(adc_data >> 5,0);
        }

    }

    return 0;
}

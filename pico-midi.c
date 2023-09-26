#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"

#include "tones_control.h"
#include "midi_control.h"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

#define VOL_GPIO 28
#define VOL_ADC 2

#define STOP_SW 26
#define MODE_SW 27


int main(void)
{
    stdio_init_all();
    board_init();
    tusb_init();

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    gpio_init(STOP_SW);
    gpio_set_dir(STOP_SW, GPIO_IN);
    gpio_pull_up(STOP_SW);
    gpio_init(MODE_SW);
    gpio_set_dir(MODE_SW, GPIO_IN);
    gpio_pull_up(MODE_SW);

    adc_init();
    adc_gpio_init(VOL_GPIO);
    adc_select_input(VOL_ADC);    

    tones_init();

    int adc_data = 0;
    bool test_mode = false;
    int test_tone = 0;
    int test_tone_old = 0;

    while(1){
        tud_task();
        midi_task();
        

        if(!gpio_get(MODE_SW)){
            tones_all_delete();
            test_mode = !test_mode;
            while(!gpio_get(MODE_SW));
            sleep_ms(10);
        }

        if(test_mode){
            test_tone = adc_read()/4;
            set_freq(6,test_tone,100);
            sleep_ms(10);
        }else{
            float volume = adc_read() / 4096.0;
            while(midi_message_available()){
                midi_message_t new_message = midi_get_message();

                if(!gpio_get(STOP_SW)){
                    tones_all_delete();
                    continue;
                }
            
                switch (new_message.event){
                case NOTE_OFF:
                    board_led_off();
                    tones_delete(new_message.tone);
                    //tones_all_delete();
                    break;
                case NOTE_ON:
                    board_led_on();
                    tones_new(new_message.tone,(float)new_message.velocity*volume);
                    break;
                default:
                    //nop
                    break;
                }
            }
        }
    }

    return 0;
}

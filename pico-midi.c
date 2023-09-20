#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "pwm_tone.h"
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
    i2c_init(I2C_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    

    tone_init(28);

    while(1){
        tud_task();
        midi_task();
    }

    return 0;
}

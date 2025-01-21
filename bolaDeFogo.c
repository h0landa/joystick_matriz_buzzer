#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define EIXO_X_JOYSTICK 26
#define EIXO_Y_JOYSTICK 27
#define CANAL_ADC_0 0
#define CANAL_ADC_1 1
#define BOTAO_JOYSTICK 22

const float DIVIDER_PWM = 16.0;
const uint16_t PERIOD = 4096;

void setup_joystick() {
    adc_init();
    adc_gpio_init(EIXO_X_JOYSTICK);
    adc_gpio_init(EIXO_Y_JOYSTICK);

    gpio_init(BOTAO_JOYSTICK);
    gpio_set_dir(BOTAO_JOYSTICK, GPIO_IN);
    gpio_pull_up(BOTAO_JOYSTICK);
}

void setup() {
    stdio_init_all();
    setup_joystick();
}

void ler_eixos_botao(uint16_t *valor_eixo_x, uint16_t *valor_eixo_y){
    adc_select_input(CANAL_ADC_0);
    sleep_us(2);
    *valor_eixo_x = adc_read();

    adc_select_input(CANAL_ADC_1);
    sleep_us(2);
    *valor_eixo_y = adc_read();
}

int main() {
    uint16_t valor_eixo_x, valor_eixo_y, botao_joystick;
    setup();

    while(1) {
        joystick_read_axis(&valor_eixo_x, &valor_eixo_y);
    }
}
/*  PWM TAREFA INDIVIDUAL 06 DE FEVEREIRO 2025 EMBARCATECH

1) Considerando a GPIO 22, defina a sua frequência de PWM para,
aproximadamente, 50Hz – período de 20ms. (20% da nota)
2) Defina o ciclo ativo do módulo PWM para 2.400µs
(microssegundos) – Ciclo de Trabalho (Duty Cycle) de 0,12%. isto
ajustará a flange (braço) do servomotor para a posição de,
aproximadamente, 180 graus. Aguarde 05 segundos nesta
posição. (10% da nota)
3) Defina o ciclo ativo do módulo PWM para 1.470µs
(microssegundos) – Ciclo de Trabalho (Duty Cycle) de 0,0735%.
Isto ajustará a flange do servomotor para a posição de,
aproximadamente, 90 graus. Aguarde 05 segundos nesta
posição. (10% da nota)
4) Defina o ciclo ativo do módulo PWM para 500µs
(microssegundos) – Ciclo de Trabalho (Duty Cycle) de 0,025%.Isto ajustará a flange do servomotor para a posição de,
aproximadamente, 0 graus. Aguarde 05 segundos nesta
posição. (10% da nota)
5) Após a realização das proposições anteriores, crie uma rotina
para movimentação periódica do braço do servomotor entre os
ângulos de 0 e 180 graus. Obs.: a movimentação da flange deve
ser suave, recomenda-se o incremento de ciclo ativo de ±5µs,
com um atraso de ajuste de 10ms. (35% da nota)
6) Com o emprego da Ferramenta Educacional BitDogLab, faça
um experimento com o código deste exercício utilizando o LED
RGB – GPIO 12. O que o discente observou no comportamento
da iluminação do referido LED? (15% da nota)  */


#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

#define SERVO_PIN 22
#define RGB_LED_PIN 12
#define PWM_FREQ 50
#define CLOCK_DIV 64
#define WRAP_VALUE 62500

// Função para definir a posição do servo usando microssegundos
void set_servo_us(uint slice_num, uint chan, uint us) {
    uint16_t level = (us * (WRAP_VALUE / 20000));  // Converter microssegundos para nível PWM
    pwm_set_chan_level(slice_num, chan, level);
}

void smooth_servo_movement(uint slice_num, uint chan, uint start_us, uint end_us) {
    int step = (start_us < end_us) ? 5 : -5;
    
    for (uint pos = start_us; 
         (step > 0) ? pos <= end_us : pos >= end_us; 
         pos += step) {
        set_servo_us(slice_num, chan, pos);
        sleep_ms(10);
    }
}

int main() {
    stdio_init_all();
    
    // Inicializar PWM para servo
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    uint chan = pwm_gpio_to_channel(SERVO_PIN);
    
    // Configurar PWM
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, CLOCK_DIV);
    pwm_config_set_wrap(&config, WRAP_VALUE);
    pwm_init(slice_num, &config, true);
    
    // Inicialização LED RGB
    gpio_init(RGB_LED_PIN);
    gpio_set_dir(RGB_LED_PIN, GPIO_OUT);
    
    while (true) {
        // 180 graus - 2400µs
        set_servo_us(slice_num, chan, 2400);
        sleep_ms(5000);
        
        // 90 graus - 1470µs
        set_servo_us(slice_num, chan, 1470);
        sleep_ms(5000);
        
        // 0 graus - 500µs
        set_servo_us(slice_num, chan, 500);
        sleep_ms(5000);
        
        // Movimento suave de 0 a 180 graus e vice-versa
        smooth_servo_movement(slice_num, chan, 500, 2400);  // 0° a 180°
        sleep_ms(1000);
        smooth_servo_movement(slice_num, chan, 2400, 500);  // 180° a 0°
        sleep_ms(1000);
        
        // Alternar LED RGB
        gpio_put(RGB_LED_PIN, 1);
        sleep_ms(500);
        gpio_put(RGB_LED_PIN, 0);
        sleep_ms(500);
    }
}
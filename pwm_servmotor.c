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
#define SYSTEM_CLOCK 125000000
#define PWM_FREQ 50  // Frequência de 50Hz para ambos servo e LED
#define CLOCK_DIV 100
#define WRAP_VALUE (SYSTEM_CLOCK / (PWM_FREQ * CLOCK_DIV))

#define POS_180 2400
#define POS_90 1470
#define POS_0 500

// Função para definir o ciclo ativo do PWM do servo
void set_servo_us(uint slice_num, uint chan, uint us) {
    uint16_t level = (us * WRAP_VALUE) / 20000;
    pwm_set_chan_level(slice_num, chan, level);
}

// Função para definir o brilho do LED (0-100%)
void set_led_brightness(uint slice_num, uint chan, float brightness) {
    // Usando o mesmo WRAP_VALUE do servo para manter a mesma frequência
    uint16_t level = (uint16_t)(brightness * WRAP_VALUE / 100.0f);
    pwm_set_chan_level(slice_num, chan, level);
}

// Função para movimentação suave do servomotor com LED pulsante
void smooth_servo_movement(uint servo_slice, uint servo_chan, uint led_slice, uint led_chan, uint start_us, uint end_us) {
    int step = (start_us < end_us) ? 5 : -5;
    float brightness = 0;
    bool increasing = true;
    
    for (uint pos = start_us; 
         (step > 0) ? pos <= end_us : pos >= end_us; 
         pos += step) {
        // Atualiza posição do servo
        set_servo_us(servo_slice, servo_chan, pos);
        
        // Atualiza brilho do LED com efeito de pulsação
        if (increasing) {
            brightness += 2.0f;
            if (brightness >= 100) {
                increasing = false;
            }
        } else {
            brightness -= 2.0f;
            if (brightness <= 0) {
                increasing = true;
            }
        }
        
        set_led_brightness(led_slice, led_chan, brightness);
        sleep_ms(10);
    }
}

int main() {
    stdio_init_all();
    
    // Configurando o PWM do Servo
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint servo_slice = pwm_gpio_to_slice_num(SERVO_PIN);
    uint servo_chan = pwm_gpio_to_channel(SERVO_PIN);
    
    // Configurando o PWM do LED
    gpio_set_function(RGB_LED_PIN, GPIO_FUNC_PWM);
    uint led_slice = pwm_gpio_to_slice_num(RGB_LED_PIN);
    uint led_chan = pwm_gpio_to_channel(RGB_LED_PIN);
    
    // Configurando o PWM com os mesmos parâmetros para servo e LED
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, CLOCK_DIV);
    pwm_config_set_wrap(&config, WRAP_VALUE);
    
    // Inicializando os PWMs
    pwm_init(servo_slice, &config, true);
    pwm_init(led_slice, &config, true);
    
    while (true) {
        // 180 graus - LED brilho máximo
        set_servo_us(servo_slice, servo_chan, POS_180);
        set_led_brightness(led_slice, led_chan, 100);
        sleep_ms(5000);
        
        // 90 graus - LED brilho médio
        set_servo_us(servo_slice, servo_chan, POS_90);
        set_led_brightness(led_slice, led_chan, 50);
        sleep_ms(5000);
        
        // 0 graus - LED brilho mínimo
        set_servo_us(servo_slice, servo_chan, POS_0);
        set_led_brightness(led_slice, led_chan, 10);
        sleep_ms(5000);
        
        // Movimentos suaves com LED pulsante
        smooth_servo_movement(servo_slice, servo_chan, led_slice, led_chan, POS_0, POS_180);
        sleep_ms(1000);
        smooth_servo_movement(servo_slice, servo_chan, led_slice, led_chan, POS_180, POS_0);
        sleep_ms(1000);
    }
}
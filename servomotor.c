#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22  // Pino do servo no PWM
#define LED_R_PIN 12   // Pino do LED RGB - Canal Vermelho
#define LED_G_PIN 13   // Pino do LED RGB - Canal Verde
#define LED_B_PIN 14   // Pino do LED RGB - Canal Azul
#define PWM_FREQ 50    // Frequência de 50Hz
#define PWM_WRAP 20000 // Contagem total do PWM para 50Hz

static const int WAIT_MS = 5000; // Tempo de espera em milissegundos

// Função para configurar o PWM para o pino do servo
void setup_pwm(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(slice_num, PWM_WRAP);
    pwm_set_clkdiv(slice_num, 125.0f);
    pwm_set_enabled(slice_num, true);
}

// Função para configurar o PWM para o LED RGB
void setup_led_pwm() {
    gpio_set_function(LED_R_PIN, GPIO_FUNC_PWM);
    gpio_set_function(LED_G_PIN, GPIO_FUNC_PWM);
    gpio_set_function(LED_B_PIN, GPIO_FUNC_PWM);

    uint slice_r = pwm_gpio_to_slice_num(LED_R_PIN);
    uint slice_g = pwm_gpio_to_slice_num(LED_G_PIN);
    uint slice_b = pwm_gpio_to_slice_num(LED_B_PIN);

    pwm_set_wrap(slice_r, PWM_WRAP);
    pwm_set_wrap(slice_g, PWM_WRAP);
    pwm_set_wrap(slice_b, PWM_WRAP);

    pwm_set_clkdiv(slice_r, 125.0f);
    pwm_set_clkdiv(slice_g, 125.0f);
    pwm_set_clkdiv(slice_b, 125.0f);

    pwm_set_enabled(slice_r, true);
    pwm_set_enabled(slice_g, true);
    pwm_set_enabled(slice_b, true);
}

// Função para definir a intensidade do LED RGB (ajustando os duty cycles)
void set_led_intensity(uint r_intensity, uint g_intensity, uint b_intensity) {
    uint slice_r = pwm_gpio_to_slice_num(LED_R_PIN);
    uint slice_g = pwm_gpio_to_slice_num(LED_G_PIN);
    uint slice_b = pwm_gpio_to_slice_num(LED_B_PIN);

    pwm_set_gpio_level(LED_R_PIN, r_intensity);
    pwm_set_gpio_level(LED_G_PIN, g_intensity);
    pwm_set_gpio_level(LED_B_PIN, b_intensity);
}

// Função para movimentação suave do servo e controle da intensidade do LED
void smooth_movement(uint pin, uint start, uint end, int step, int delay_ms) {
    if (start > end) step = -step;

    for (uint pulse = start; (step > 0) ? (pulse <= end) : (pulse >= end); pulse += step) {
        // Define a posição do servo
        uint slice_num = pwm_gpio_to_slice_num(pin);
        pwm_set_gpio_level(pin, pulse);
        
        // Calcula a intensidade do LED de forma decrescente (começa forte e vai diminuindo)
        uint led_intensity = 65535 - (pulse / 10);  // Intensidade vai diminuindo conforme o servo se move
        if (led_intensity > 65535) led_intensity = 65535;  // Limite máximo da intensidade
        if (led_intensity < 0) led_intensity = 0;       // Limite mínimo da intensidade

        // Controlando a intensidade do LED RGB (canal vermelho)
        set_led_intensity(led_intensity, 0, 0);  // Ajuste para vermelho, pode mudar para outras cores se necessário
        
        sleep_ms(delay_ms);
    }
}

int main() {
    stdio_init_all();
    setup_pwm(SERVO_PIN);
    setup_led_pwm();  // Configuração do PWM para o LED RGB

    // Posições fixas com intensidade de LED ajustada
    pwm_set_gpio_level(SERVO_PIN, 2400); // 180°
    set_led_intensity(65535, 0, 0);  // Inicia com intensidade máxima no LED vermelho
    sleep_ms(WAIT_MS);

    pwm_set_gpio_level(SERVO_PIN, 1470); // 90°
    set_led_intensity(32767, 0, 0);  // Intensidade média do LED
    sleep_ms(WAIT_MS);

    pwm_set_gpio_level(SERVO_PIN, 500);  // 0°
    set_led_intensity(0, 0, 0);   // LED apagado
    sleep_ms(WAIT_MS);

    // Movimentação suave com LED ajustando a intensidade conforme o movimento
    while (1) {
        smooth_movement(SERVO_PIN, 500, 2400, 5, 10);  // Move de 0° para 180°
        smooth_movement(SERVO_PIN, 2400, 500, 5, 10);  // Move de 180° para 0°
    }

    return 0;
}

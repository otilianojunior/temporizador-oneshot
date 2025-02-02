#include "pico/stdlib.h"
#include <stdio.h>
#include <stdbool.h>
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define BUTTON_PIN 5
#define LED1_PIN 11
#define LED2_PIN 12
#define LED3_PIN 13

volatile bool button_pressed = false;
volatile bool timer_running = false;
int state = 0;     // 0: LED1, 1: LED2, 2: LED3
int countdown = 3; // Contagem regressiva de 3 segundos para cada LED

// Callback do timer: executado a cada 1 segundo durante a contagem
int64_t timer_callback(alarm_id_t id, void *user_data)
{
    if (countdown > 0)
    {
        // Exibe a contagem regressiva para o LED atual
        printf("| - - - - - - - - - - - - - - - - - |\n");
        printf("|     Desligando LED%d em %ds...      |\n", state + 1, countdown);
        countdown--;
        // Agenda a próxima chamada após 1 segundo (1.000.000 µs)
        return 1000 * 1000;
    }
    else
    {
        // Quando a contagem chega a zero, desliga o LED correspondente
        if (state == 0)
        {
            printf("| - - - - - - - - - - - - - - - - - |\n");
            printf("|                                   |\n");
            printf("|          [⚫] - LED 1 DESLIGADO   |\n"); // LED azul apagado
            printf("|          [🔴] - Vermelho          |\n"); // LED vermelho aceso
            printf("|          [🟢] - Verde             |\n"); // LED verde aceso
            printf("|                                   |\n");
            gpio_put(LED1_PIN, 0);
        }
        else if (state == 1)
        {
            printf("| - - - - - - - - - - - - - - - - - |\n");
            printf("|                                   |\n");
            printf("|         [⚫] - LED 1 DESLIGADO    |\n"); // LED azul apagado
            printf("|         [⚫] - LED 2 DESLIGADO    |\n"); // LED vermelho apagado
            printf("|         [🟢] - Verde              |\n"); // LED verde aceso
            printf("|                                   |\n");
            gpio_put(LED2_PIN, 0);
        }
        else if (state == 2)
        {
            printf("| - - - - - - - - - - - - - - - - - |\n");
            printf("|                                   |\n");
            printf("|         [⚫]  - LED 1 DESLIGADO   |\n"); // LED azul apagado
            printf("|         [⚫]  - LED 1 DESLIGADO   |\n"); // LED vermelho apagado
            printf("|         [⚫]  - LED 1 DESLIGADO   |\n"); // LED verde apagado
            printf("|                                   |\n");
            gpio_put(LED3_PIN, 0);
        }
        // Avança para o próximo LED
        state++;
        if (state < 3)
        {
            // Reinicia a contagem para o próximo LED e agenda o callback com 1 ms de atraso
            countdown = 3;
            return 1 * 1000; // 1 ms
        }
        else
        {
            // Fim da sequência: todos os LEDs foram processados
            printf("| - - - - - - - - - - - - - - - - - |\n");
            printf("|       Todos os LEDs apagados.     |\n");
            printf("| - - - - - - - - - - - - - - - - - |\n");
            state = 0;
            timer_running = false;
            return 0; // Cancela o callback recorrente
        }
    }
}

// Função de debounce para estabilizar a leitura do botão
bool debounce()
{
    static uint32_t last_time = 0;
    const uint32_t debounce_delay = 50; // 50 ms
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    if ((current_time - last_time) > debounce_delay)
    {
        last_time = current_time;
        return gpio_get(BUTTON_PIN) == 0;
    }
    return false;
}

// Rotina de interrupção do botão
void button_isr(uint gpio, uint32_t events)
{
    if (gpio == BUTTON_PIN && !timer_running && debounce())
    {
        button_pressed = true;
    }
}

int main()
{
    stdio_init_all();

    // Configuração do botão
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // Configuração dos LEDs
    gpio_init(LED1_PIN);
    gpio_init(LED2_PIN);
    gpio_init(LED3_PIN);
    gpio_set_dir(LED1_PIN, GPIO_OUT);
    gpio_set_dir(LED2_PIN, GPIO_OUT);
    gpio_set_dir(LED3_PIN, GPIO_OUT);

    // Garante que os LEDs estejam desligados inicialmente
    gpio_put(LED1_PIN, 0);
    gpio_put(LED2_PIN, 0);
    gpio_put(LED3_PIN, 0);

    // Configura a interrupção para o botão
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_isr);

    while (1)
    {
        if (button_pressed && !timer_running)
        {
            button_pressed = false;
            timer_running = true;
            state = 0;     // Inicia com o LED1
            countdown = 3; // Reseta o contador para 3 segundos

            // Liga todos os LEDs
            gpio_put(LED1_PIN, 1);
            gpio_put(LED2_PIN, 1);
            gpio_put(LED3_PIN, 1);
            printf("| - - - - - - - - - - - - - - - - - |\n");
            printf("|        Todos os LEDs ligados.     |\n");
            printf("| - - - - - - - - - - - - - - - - - |\n");
            printf("|                                   |\n");
            printf("|          [🔵] - Azul (LD1)        |\n"); // LED azul aceso
            printf("|          [🔴] - Vermelho (LD2)    |\n"); // LED vermelho aceso
            printf("|          [🟢] - Verde (LD3)       |\n"); // LED verde aceso
            printf("|                                   |\n");

            // Inicia a sequência de desligamento com um atraso mínimo de 1 ms
            add_alarm_in_ms(1, timer_callback, NULL, false);
        }
    }
    return 0;
}

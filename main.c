#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pio.h"
#include "stdio.h"
#include "ws2812.pio.h"  // Inclua o arquivo do programa PIO

// Definindo pinos
#define LED_VERMELHO_PIN 12  // LED vermelho
#define LED_AZUL_PIN 13      // LED azul
#define BUZZER_PIN_1 10      // Buzzer 1 no GPIO 10
#define BUZZER_PIN_2 21      // Buzzer 2 no GPIO 21
#define MIC_PIN 28           // Pino GPIO 28 (ADC)
#define BUTTON_A_PIN 5       // Pino do botão A (GPIO 5)
#define MATRIZ_LED_PIN 7     // Pino da matriz de LEDs (GPIO 7)

#define NUM_SAMPLES 10       // Número de amostras para média móvel
#define TIMEOUT_MS 5000      // Tempo para desligar a matriz de LEDs após inatividade (em ms)

// Variáveis globais para média móvel e controle de ruído
float samples[NUM_SAMPLES];
int sample_index = 0;
float average_voltage = 0.0f;
int last_noise_level = -1;   // Armazena o último nível de ruído detectado
uint32_t last_change_time = 0; // Armazena o tempo da última mudança de ruído

// Função para calcular a média móvel
float calculate_moving_average(uint16_t raw_value) {
    samples[sample_index] = raw_value * 3.3f / (1 << 12); // Converte para tensão
    sample_index = (sample_index + 1) % NUM_SAMPLES;

    float sum = 0.0f;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        sum += samples[i];
    }
    return sum / NUM_SAMPLES;
}

// Função para classificar o nível de ruído com base na tensão
int classify_noise_level(float voltage) {
    if (voltage < 1.62f || voltage > 1.66f) {
        return 1;  // Ruído alto (LED vermelho)
    } else {
        return 0;  // Ruído normal (LED azul)
    }
}

// Função para controlar os LEDs
void control_leds(int noise_level) {
    gpio_put(LED_VERMELHO_PIN, 0);  // Desliga o LED vermelho
    gpio_put(LED_AZUL_PIN, 0);      // Desliga o LED azul

    if (noise_level == 0) {
        gpio_put(LED_AZUL_PIN, 1);  // Ruído normal: LED azul aceso
    } else if (noise_level == 1) {
        gpio_put(LED_VERMELHO_PIN, 1);  // Ruído alto: LED vermelho aceso
    }
}

// Função para controlar os buzzers (usando ambos simultaneamente)
void control_buzzers(bool state) {
    gpio_put(BUZZER_PIN_1, state ? 1 : 0);  // Liga ou desliga o buzzer 1
    gpio_put(BUZZER_PIN_2, state ? 1 : 0);  // Liga ou desliga o buzzer 2
}

// Função para verificar se o botão A foi pressionado
bool is_button_a_pressed() {
    return gpio_get(BUTTON_A_PIN) == 0;  // Assumindo que o botão A tem pull-up e é pressionado para baixo
}

// Função para controlar a matriz de LEDs WS2812
void control_matrix(uint32_t color) {
    // Enviar cor para o WS2812 via PIO
    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);  // Carrega o programa PIO para WS2812
    ws2812_program_init(pio, sm, offset, MATRIZ_LED_PIN, 800000, false);  // Frequência 800kHz para WS2812

    // Criar um array de cores para a matriz
    uint32_t pixels[64];  // Para uma matriz 8x8
    for (int i = 0; i < 64; i++) {
        pixels[i] = color;  // Aplique a cor em toda a matriz
    }

    // Enviar a cor para a matriz
    for (int i = 0; i < 64; i++) {
        pio_sm_put_blocking(pio, sm, pixels[i]);
    }
}

// Função de configuração inicial
void setup() {
    stdio_init_all();

    // Inicializa os pinos para LEDs, buzzers, e botão
    gpio_init(LED_VERMELHO_PIN);
    gpio_set_dir(LED_VERMELHO_PIN, GPIO_OUT);

    gpio_init(LED_AZUL_PIN);
    gpio_set_dir(LED_AZUL_PIN, GPIO_OUT);

    gpio_init(BUZZER_PIN_1);
    gpio_set_dir(BUZZER_PIN_1, GPIO_OUT);

    gpio_init(BUZZER_PIN_2);
    gpio_set_dir(BUZZER_PIN_2, GPIO_OUT);

    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN); // Habilita pull-up no botão A

    gpio_init(MATRIZ_LED_PIN);  // Inicializa o pino da matriz de LEDs
    gpio_set_dir(MATRIZ_LED_PIN, GPIO_OUT);  // Define como saída

    // Inicializa o ADC para o microfone
    adc_init();
    adc_gpio_init(MIC_PIN);
    adc_select_input(2);  // Seleciona o canal de entrada ADC2 (pino 28)

    // Inicializa a média móvel
    for (int i = 0; i < NUM_SAMPLES; i++) {
        samples[i] = 0.0f;
    }

    // Inicializa os LEDs WS2812
    PIO pio = pio0;  // Pode ser pio1 também, dependendo da sua configuração
    uint sm = 0;      // State machine 0 (você pode usar outro se necessário)
    uint offset = pio_add_program(pio, &ws2812_program);  // Carrega o programa PIO
    ws2812_program_init(pio, sm, offset, MATRIZ_LED_PIN, 800000, false);  // Frequência 800kHz

    sleep_ms(1000);
}

// Função principal
void loop() {
    uint16_t raw_value = adc_read();
    average_voltage = calculate_moving_average(raw_value);
    int noise_level = classify_noise_level(average_voltage);

    control_leds(noise_level);

    // Se a tensão for maior que 1.66V ou menor que 1.62V, liga os buzzers
    if (average_voltage < 1.62f || average_voltage > 1.66f) {
        control_buzzers(true);  // Liga os buzzers
    } else {
        control_buzzers(false);  // Desliga os buzzers caso a tensão esteja no intervalo
    }

    // Se o botão A for pressionado, desliga os buzzers
    if (is_button_a_pressed()) {
        control_buzzers(false);  // Desliga os buzzers
    }

    // Controla a matriz de LEDs
    if (noise_level != last_noise_level) {
        last_change_time = to_ms_since_boot(get_absolute_time());  // Reseta o tempo de inatividade
        control_matrix(0xFF0000);  // Cor vermelha, ou defina qualquer outra
    }

    // Se o ruído não mudou dentro do tempo limite (TIMEOUT_MS), desliga a matriz de LEDs
    if (to_ms_since_boot(get_absolute_time()) - last_change_time > TIMEOUT_MS) {
        control_matrix(0x000000);  // Desliga a matriz de LEDs
    }

    last_noise_level = noise_level;  // Atualiza o último nível de ruído

    printf("Valor bruto: %u, Tensão média: %.2f V, Nível de Ruído: %d\n", raw_value, average_voltage, noise_level);

    sleep_ms(100);
}

// Função main
int main() {
    setup();
    while (1) {
        loop();
    }
}

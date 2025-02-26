# Projeto RP2040 com LEDs e Display SSD1306

Este projeto utiliza o microcontrolador RP2040 para controlar LEDs e um display SSD1306. O código permite alternar os LEDs usando botões ou comandos recebidos via USB e exibir mensagens no display.

## Funcionalidades

- Alternar LEDs (vermelho, verde e azul) usando botões ou comandos USB.
- Exibir mensagens no display SSD1306.
- Exibir números de 0 a 9 usando uma matriz de LEDs.

## Componentes Utilizados

- RP2040
- LEDs RGB
- Display SSD1306
- Botões
- Conexões I2C

## Estrutura do Código

O código está dividido em várias funções principais:

- **init_display()**: Inicializa o display SSD1306.
- **display_message()**: Exibe uma mensagem no display.
- **gpio_irq_handler()**: Manipulador de interrupções dos botões.
- **set_one_led()**: Define o estado de um LED.
- **show_number()**: Exibe um número na matriz de LEDs.
- **main()**: Função principal que inicializa os componentes e entra em um loop para ler comandos USB.

## Uso

1. Compile e carregue o código no RP2040.
2. Conecte os LEDs, botões e o display SSD1306 conforme indicado no código.
3. Use os botões para alternar os LEDs verde e azul.
4. Envie comandos via USB para alternar os LEDs ou exibir números na matriz de LEDs.

## Comandos USB

- "R": Alterna o LED vermelho.
- "G": Alterna o LED verde.
- "B": Alterna o LED azul.
- "0" a "9": Exibe o número correspondente na matriz de LEDs.
- Qualquer letra maiúscula digitada será exibida no display SSD1306.

## Observações

- **Falha ao usar letras minúsculas**: Os comandos para alternar os LEDs ("R", "G", "B") devem ser enviados em letras maiúsculas. Caso contrário, o comando será considerado inválido.

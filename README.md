Monitoramento de Ruído em Ambientes Domésticos
Descrição
Este projeto visa desenvolver um sistema embarcado para monitoramento de ruído em ambientes domésticos, com foco principal em quartos de bebês e idosos. O objetivo é garantir um ambiente tranquilo, ajudando a preservar a qualidade do sono ao monitorar e controlar os níveis de ruído. Quando os níveis de ruído ultrapassam um limite pré-definido, o sistema emite alertas sonoros e visuais para notificar os responsáveis sobre a necessidade de ajustar o ambiente.

Título do Projeto
Monitoramento de Ruído em Ambientes Domésticos

Objetivos
Monitorar os níveis de ruído em tempo real em quartos de bebês ou idosos.
Emitir alertas sonoros e visuais quando o nível de ruído atingir um limite prejudicial ao descanso.
Exibir o nível de ruído atual em um display LCD 128x64.
Usar LEDs para representar visualmente a intensidade do som.
Permitir ajustes no limite de ruído e ativação/desativação do sistema com botões de controle.
Descrição do Funcionamento
O sistema captura os níveis de som ambiente através de um microfone conectado a um ADC (Conversor Analógico-Digital). O valor capturado é classificado como baixo, moderado ou alto. O nível de ruído é exibido em tempo real no display 128x64 e na matriz de LEDs. Quando o nível de ruído atinge a categoria "Alto", o sistema emite um alerta sonoro e aciona a matriz de LEDs para alertar visualmente. Botões permitem ao usuário ajustar os limites de alerta ou desativar o sistema.

Justificativa
Em ambientes domésticos, especialmente quartos de bebês e idosos, o controle do nível de ruído é essencial para garantir uma boa qualidade de descanso. Este projeto visa melhorar a qualidade do sono e o bem-estar de indivíduos sensíveis ao ruído, utilizando um sistema simples e eficaz que monitora e alerta sobre níveis excessivos de som.

Originalidade
Embora existam sistemas de monitoramento de ruído, poucos se concentram especificamente em ambientes de descanso. Além disso, muitos sistemas existentes não integram alertas sonoros e visuais de forma acessível e personalizada. Este projeto se destaca por combinar várias tecnologias (microfone, display, LEDs e buzzer) e aplicá-las em um contexto voltado à segurança e bem-estar de bebês e idosos.

Especificação do Hardware
Diagrama de Bloco
Microfone: Captura os níveis de som ambiente e envia o sinal para o ADC.
ADC: Converte o sinal analógico do microfone para um valor digital.
Raspberry Pi Pico W: Processa o valor digital, classifica o ruído e controla os dispositivos de saída (display, LEDs, buzzer).
Display 128x64: Exibe informações sobre o nível de ruído.
Matriz de LEDs 5x5: Representa visualmente a intensidade do som ambiente.
Speaker: Emite um som de alerta quando o ruído atinge o nível alto.
Botões A e B: Permitem o controle e ajustes do sistema.
Pinagem
Microfone: GPIO 28 (entrada analógica)
Display 128x64: SDA (GPIO 14), SCL (GPIO 15)
Matriz de LEDs: GPIO 7 (controle PWM)
Speaker: GPIO 10 (controle digital)
Botões A e B: GPIO 5 e GPIO 6 (controle de configuração)
Diagrama Circuito Completo
O circuito inclui o Raspberry Pi Pico W conectado ao microfone (entrada analógica), display I2C, matriz de LEDs (controle PWM), buzzer (controle digital) e botões.

Especificação do Firmware
Blocos Funcionais
Aquisição de Dados: Leitura contínua do valor do microfone através do ADC.
Processamento do Ruído: O valor digital obtido é classificado em categorias (baixo, moderado, alto).
Controle de LEDs: A matriz de LEDs é acionada para representar visualmente o nível de ruído.
Alertas: O buzzer emite um som de alerta quando o ruído atinge o nível alto.
Interatividade: O usuário pode ajustar a sensibilidade do sistema e ativar/desativar o monitoramento com os botões.
Descrição das Funcionalidades
Captura de Som: O microfone captura o som ambiente, que é processado e convertido em um valor digital pelo ADC.
Classificação do Ruído: O valor digital é analisado para determinar se o ruído é baixo, moderado ou alto.
Alertas Visuais e Sonoros: Quando o ruído é classificado como alto, a matriz de LEDs exibe um padrão de alerta e o speaker emite um som.
Interatividade: Os botões permitem ao usuário ajustar os limites de alerta e ativar/desativar o monitoramento.
Variáveis
sound_level: Valor digital representando a intensidade do som.
noise_category: Categoria de ruído (baixo, moderado, alto).
alert_status: Determina se um alerta será emitido ou não.
Execução do Projeto
Metodologia
Pesquisa sobre sistemas de monitoramento de ruído e suas aplicações.
Escolha de componentes de hardware (Raspberry Pi Pico W, microfone, display, LEDs e buzzer).
Desenvolvimento do código e integração dos sistemas de captura, processamento e alertas.
Testes em diferentes ambientes para ajuste da sensibilidade.

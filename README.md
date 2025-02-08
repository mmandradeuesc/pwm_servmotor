# PWM_SERVMOTOR

## Tarefa 2 - Aula Síncrona 06/02

### Integrante
- Marcel Mascarenhas Andrade

### Pré-requisitos
Certifique-se de que você tem o ambiente configurado conforme abaixo:
- **Pico SDK** instalado e configurado.
- **VSCode** com todas as extensões necessárias configuradas.
- **CMake** e **Make** instalados.

### Instruções de Configuração
1. Clone o repositório e abra a pasta do projeto no VSCode.
   ```sh
   git clone https://github.com/mmandradeuesc/pwm_servmotor
   cd pwm_servmotor
   code .

### Manual do Programa
Objetivo: Definir a frequência de PWM para aproximadamente 50Hz (período de 20ms) na GPIO 22.
A função de configuração de PWM será ajustada para frequência de 50Hz.
o Ciclo Ativo será definido para 180 Graus

Objetivo: Ajustar a flange (braço) do servomotor para a posição de aproximadamente 180 graus.
O ciclo ativo do módulo PWM será ajustado para 2.400µs (microssegundos), o que corresponde a um Ciclo de Trabalho (Duty Cycle) de 0,12%.
Será maintido essa configuração por 5 segundos.
Ajuste do Ciclo será Ativo para 90 Graus

Objetivo: Ajustar a flange do servomotor para a posição de aproximadamente 90 graus.
O ciclo ativo do módulo PWM será ajustado para 1.470µs (microssegundos), o que corresponde a um Ciclo de Trabalho (Duty Cycle) de 0,0735%.
A configuração será mantida por 5 segundos.
Ajuste do Ciclo Ativado para 0 Graus

Objetivo: Ajustar a flange do servomotor para a posição de aproximadamente 0 graus.
O ciclo ativo do módulo PWM será ajustado para 500µs (microssegundos), o que corresponde a um Ciclo de Trabalho (Duty Cycle) de 0,025%.
Ação: Mantenha essa configuração por 5 segundos.
Rotina de Movimentação Periódica

Objetivo: Criar uma rotina para movimentação periódica do braço do servomotor entre os ângulos de 0 e 180 graus.
Implementada uma rotina que incrementa o ciclo ativo em ±5µs com um atraso de ajuste de 10ms para garantir uma movimentação suave da flange.
Experimento com LED RGB

Objetivo: Utilizar a Ferramenta Educacional BitDogLab para realizar um experimento com o código utilizando o LED RGB na GPIO 12.
Execute o código e observe o comportamento da iluminação do LED RGB.
Observação: Documente o comportamento observado na iluminação do LED durante o experimento.

### Documentação do Comportamento do LED RGB
Padrões de Iluminação Observados

Durante Posições Fixas (5 segundos cada):

- 180° (2400µs): LED permanece aceso continuamente
- 90° (1470µs): LED pisca em intervalos regulares
- 0° (500µs): LED permanece aceso continuamente


Durante Movimento Suave:

- Transição 0° → 180°: LED exibe padrão de pulsação gradual, aumentando intensidade
- Transição 180° → 0°: LED exibe padrão de pulsação gradual, diminuindo intensidade


Características Técnicas:

Frequência de piscada: 1Hz (500ms ligado, 500ms desligado)
Sincronização com PWM do servo: LED pisca em fase com mudanças de posição
Intensidade consistente durante estados estáticos
Variação de intensidade durante movimentos dinâmicos
 
- Link do vídeo demonstração do programa:
- https://drive.google.com/file/d/1x_K7VEitM5nYz3jrwK-gogZ9zSJDMMZA/view?usp=sharing

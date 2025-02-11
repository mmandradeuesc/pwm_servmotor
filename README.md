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

- 180° (2400µs): Posição 180 Graus

Servo: 
Duty Cycle: 12% (2400µs)
Posição: Rotação máxima (180°)

LED:
Brilho: 100% (máximo)
Estado: Luz constante e forte
Propósito: Indica posição máxima do servo

- 90° (1470µs): Posição 90º 
Servo:
Duty Cycle: 7.35% (1470µs)
Posição: Rotação média (90°)

LED:
Brilho: 50% (médio)
Estado: Luz constante e média
Propósito: Indica posição intermediária do servo

- 0° (500µs): Posição 0º

Servo:
Duty Cycle: 2.5% (500µs)
Posição: Rotação mínima (0°)

LED:
Brilho: 10% (mínimo)
Estado: Luz constante e fraca
Propósito: Indica posição mínima do servo


- Durante Movimento Suave:

Servo:
Variação: Incrementos de 5µs
Tempo entre incrementos: 10ms
Movimento: Contínuo entre 0° e 180°

LED:
Variação: Incrementos de 2% no brilho
Estado: Pulsação contínua (fade in/out)
Propósito: Indica movimento em progresso

### Características Técnicas:

- Estados Fixos

Brilho máximo → Servo em 180°
Brilho médio → Servo em 90°
Brilho mínimo → Servo em 0°

- Estados Dinâmicos

Pulsação do LED indica movimento do servo
Quanto mais rápida a pulsação, mais rápido o movimento

- Propósito do Sistema
O sistema fornece feedback visual do posicionamento do servo através do LED:

Estados fixos indicam posições específicas
Pulsação indica movimento em progresso
Intensidade do LED correlaciona com a posição angular do servo
 
- Link do vídeo demonstração do programa:
- https://drive.google.com/file/d/1AxvOeXxum08IZLNa79QtE43ockWTFbDh/view?usp=sharing

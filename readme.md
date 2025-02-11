# Controle de Servomotor por PWM com Raspberry Pi Pico W

## Descrição do Projeto

Este projeto implementa o controle de um servomotor utilizando o microcontrolador Raspberry Pi Pico W e o módulo PWM (Pulse Width Modulation). A simulação é realizada no simulador Wokwi e segue os requisitos definidos na atividade da Unidade 4, Capítulo 7 do curso.

## Requisitos

- Raspberry Pi Pico W
- Servomotor micro servo padrão (simulado no Wokwi)
- Ferramenta de desenvolvimento VS Code
- Kit de Desenvolvimento de Software Pico SDK
- Simulador Wokwi integrado ao VS Code
- Repositório no GitHub para versionamento
- Ferramenta Educacional BitDogLab para teste com LED RGB (GPIO 12)

## Configurações Implementadas

1. **Configuração do PWM**: A GPIO 22 foi configurada para operar a 50 Hz (período de 20ms).
2. **Posicionamento do Servo**:
   - 180°: Ciclo ativo de 2400µs (0,12% de duty cycle) e espera de 5 segundos.
   - 90°: Ciclo ativo de 1470µs (0,0735% de duty cycle) e espera de 5 segundos.
   - 0°: Ciclo ativo de 500µs (0,025% de duty cycle) e espera de 5 segundos.
3. **Movimentação Suave do Servo**: Criada uma rotina para deslocamento entre 0° e 180° com incrementos de ±5µs e atraso de 10ms para suavidade na movimentação.
4. **Teste com BitDogLab**: Análise do comportamento da iluminação do LED RGB na GPIO 12.

## Como Executar

1. Clone o repositório:
   ```sh
   git clone https://github.com/renanlima2023/servomotor
   cd servomotor
   ```
2. Configure o ambiente do Pico SDK seguindo a documentação oficial.
3. Compile e carregue o programa no Raspberry Pi Pico W.
4. Execute a simulação no Wokwi.
5. Utilize o BitDogLab para observar o comportamento do LED RGB.

## Resultados e Observações

Os testes realizados demonstram que o servomotor responde corretamente aos sinais PWM configurados, alterando suas posições de acordo com os tempos definidos. A movimentação suave entre os ângulos funciona conforme esperado, proporcionando transição natural entre as posições. No experimento com a BitDogLab, observou-se alteração na iluminação do LED RGB durante o funcionamento do servomotor.

## Video Demonstrativo

Para um melhor entendimento da implementação, assista ao video ensaio no link abaixo:

[Video de demonstração](https://www.youtube.com/watch?v=uydkDI5Abd8)

## Autor

Renan Lima - [GitHub](https://github.com/renanlima2023)

---

Este projeto faz parte das atividades da disciplina ministrada pelo Prof. Dr. Ricardo Menezes Prates.



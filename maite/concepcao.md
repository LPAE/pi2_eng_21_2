# Concepção

O projeto consiste na construção de uma residência automatizada, realizando o controle e monitoramento dos sistemas residenciais, apresentando os dados de maneira simples para o usuário final. Tendo como objetivo utilizar tecnologias de baixo custo, buscando a acessibilidade à maior parte da população.

### Requisitos:

1. Realizar o controle de acesso à residência, utilizando o sensor ultrasônico HC-SR04 e o sensor de presença PIR para identificar a presença de carros e pessoas, o buzzer será utilizado como campainha.

2. Realizar o controle de irrigação do jardim, utilizando o sensor YL-69 para monitorar o solo. Quando a umidade do solo estiver menor que 30% acionar a mini-bomba.

3. Realizar um sistema de prevenção a acidentes com gás de cozinha, utilizando o sensor de gás MQ-2. Quando o nível de gás ultrapassar o nível aceitável acionar o exaustor, desligando o mesmo somente quando o nível voltar ao normal.

5. Usar o sensor de nível d'água para medir o reservatório de água da minibomba. 

4. Apresentar os dados de temperatura e umidade externa e nível de água no LCD.
 
5. Os comandos devem ser realizados remotamente, via PC.

### Tecnologias do Projeto:

|  Componentes Eletrônicos                           | Quantidade |
| -------------------------------------------------- | ---------- |
| Placa MEGA 2560 R3 + Fonte + Cabo USB para Arduino |      1     |
| Sensor de Umidade e Temperatura DHT11 |      1     |
| Sensor de presença e movimento PIR |      1     |
| Sensor de gás MQ-2 inflamável e fumaça |      1     |
| Micro Servo SG92R 9g TowerPro |      1     |
| Módulo Relé 5 V e um Canal |      2     |
| Sensor ultrasônico HC-SR04 |      1     |
| Módulo Matriz de LED 8×8 com MAX7219 |      1     |
| Buzzer passivo |      1     |
| Display LCD 16×2 I2C Backlight Azul |      1     |
| Cooler |      1     |
| Módulo de fonte de alimentação HW-131 | 1 | 
| Higrômetro YL-69 | 1 |



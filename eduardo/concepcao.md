# Concepção do projeto

Acesso rápido:
  - [Introdução](./README.md)
  - [Design/Projeto](./design.md)
  - [Implementação](./implementacao.md)
  - [Operação](./operacao.md)


Este projeto pretende desenvolver um sistema de domótica completo, promovendo maior conforto e segurança para os residentes, visando o baixo custo.

#### Seguindo os objetivos definidos no projeto:

* Controle da temperatura nos cômodos, quando a temperatura subir além de 23° o ventilador será ligado e um aviso irá ser enviado para o display;

* Quando o sensor detectar um valor de gás acima de 25% acionará um exaustor para controlar o nivel de gás, a matriz de led irá acender e o buzzer emitirá um alarme sonoro para evitar um possível acidente;

* Ligar as luzes do cômodo assim que o residente entrar ou desligar as luzes quando não houver residentes no cômodo.

* Quando o sensor detectar presença a uma distância de 5cm do portão de entrada, o display LCD irá emitir um aviso de que possui visita e o buzzer emitirá um alerta sonoro;

* Abertura do portão com acionamento de uma tecla;

* Mostrar as informações mais relevantes do sistema.



Tecnologias para a realização do projeto:


Quantidade  | Tecnologias
:---------:   | ------
1           | Placa Arduino MEGA 2560 R3
1           | Sensor de Umidade e Temperatura DHT11
1           | Cooler 120mm
1           | Sensor de gás MQ-2 inflamável e fumaça
1           | Cooler 120mm
1           | Buzzer passivo
1           | Módulo Sensor de Umidade/Nível Água Chuva
1           |	Sensor de presença e movimento PIR
1           | Sensor ultrasônico HC-SR04
1           | Micro Servo SG92R 9g TowerPro
1           | Módulo Matriz de LED 8×8 com MAX7219
2           | Módulo Relé 5 V e um Canal
1           | Display LCD 16×2 I2C Backlight Azul



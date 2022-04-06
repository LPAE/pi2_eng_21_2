# Concepção do Projeto

Acesso rápido:
  
 - [Introdução](./introdução.md)
  - [Design/Projeto](./design.md)
  - [Implementação](./implementação.md)
  - [Operação](./operação.md)

  O intuito do projeto  de trata de desenvolver um sistema de automação residencial contruído e integrado à internet das coisas, dessa forma, garantindo um maior conforto,comodidade,segurança e custo benefício. Além disso, define os "princípios" de acordo com a necessidade do cliente, considerando modernidade, estrategia empresarial e os critérios de desenvolvimento de planos conceituais, técnicos e de negócios.
  
  ## Objetivação:
  
  •	Sistema de irrigação:
Será desenvolvido um sistema para o controle da umidade e temperatura externa, ou seja, na parte do jardim será possibilitado por meio do sensor umidade e do display LCD, liberar uma mensagem de aviso caso seja necessário regar as plantações nos períodos mais quentes e secos (<300).

•	Sistema entrada na garagem:
Será desenvolvido um sistema para a entrada na garagem, utilizando o servo juntamente do sensor presença e do sensor ultrassônico, o qual permite que quando a pessoa chegue na casa o portão abra automaticamente. 

•	Sistema de iluminação na garagem:
Além do fato acima, será projetada uma luz presença, caso por exemplo chegue de noite, a partir do momento que o carro entrou na garagem, haverá iluminação automática por meio da utilização do LED juntamente de um sensor presença (sem necessidade de sair do carro para liga-la).

•	Sistema para controle de vazamento de gás:
Será desenvolvido um sistema para controle de vazamentos de gás no ambiente da cozinha, sendo utilizado o sensor de gás juntamente do buzzer, na intenção de disparar um alarme sonoro na medida que o valor do gás for ≥ 400.

•	Sistema de alarme contra invasão:
Será desenvolvido um sistema de prevenção a invasão e roubo, caso algum movimento estranho desconhecido for detectado (exemplo: alguém pulando o muro), um alarme sonoro será disparado, por meio da utilização do buzzer juntamente do sensor presença.  
  
### Componentes eletrônicos disponíveis para o projeto:

| Componentes                          |Representação       |
| -------------------------------------|------------------- |
|  Placa MEGA 2560 R3+Fonte+Cabo USB          |![MEGA 2560](https://www.filipeflop.com/wp-content/uploads/2017/07/1AC04-1.jpg) |
|Sensor de Umidade e Temperatura DHT11        | ![DHT11](https://www.filipeflop.com/wp-content/uploads/2017/07/Dht11.jpg) |
|Sensor de presença e movimento PIR        | ![PIR](https://www.filipeflop.com/wp-content/uploads/2017/07/1220801-2.jpg) |
|Sensor de gás MQ-2 inflamável e fumaça     |![MQ2](https://www.filipeflop.com/wp-content/uploads/2017/07/sku_193001_2.png) |
|   Micro Servo SG92R 9g TowerPro           |![SERVO](https://cdn.awsli.com.br/600x450/535/535286/produto/121183340/f853b364ba.jpg) |
|Módulo Sensor de Umidade/Nível Água Chuva | ![NIVELAGUA](https://cdn.awsli.com.br/600x700/468/468162/produto/25255981/eb4cd1de03.jpg) |
|   Módulo Relé 5 V e um Canal                            |![rele](https://www.filipeflop.com/wp-content/uploads/2017/07/SKU099653h.jpg) |
|   Sensor ultrassônico HC-SR04                             | ![ultrassonico](https://cdn.awsli.com.br/600x700/78/78150/produto/2888532/62bc744cec.jpg) |
|   Módulo Matriz de LED 8×8 com MAX7219    | ![matrizled](https://www.usinainfo.com.br/1017274-thickbox_default/modulo-matriz-de-led-8x8-vermelho-max7219-jumpers.jpg) |
|   Buzzer passivo                                                     | ![buzzer](https://www.filipeflop.com/wp-content/uploads/2017/07/2-142.jpg) |
|   Display LCD 16×2 I2C Backlight Azul             | ![display](https://cdn.awsli.com.br/600x700/468/468162/produto/19414150/display-lcd-16x2-i2c-backlight-azul-7ff37942.jpg) |
|   LED Verde + Resistor             | ![display]( https://http2.mlstatic.com/D_NQ_NP_880713-MLB42892435467_072020-O.webp) |

## Referências
FILIPEFLOP. Loja virtual: componentes eletrônicos. Florianópolis-SC, [S.d]. Disponível em: https://www.filipeflop.com/. Acesso em: 10 nov. 2021.


# Concepção

Neste projeto, será utilizado o conceito da domótica com objetivo de modernizar e automatizar funções básicas dentro de uma casa a partir das necessidades do usuário exemplificando as possíveis tecnologias que podem ser implementadas além de manter o menor custo possível. Será utilizada uma maquete como referência, sendo as principais implentações do projeto:

- Sensoriamento de gás de cozinha, ativando o buzzer para sinalizar a detectação de gás e desabilitar o acionamento das luzes para evitar acidentes e ativando a matriz de led para iluminação.
- Controlar um portão com acionamento eletrônico de forma inteligente avisando o usuário quando existir a presença de visitas atravez do Buzzer.
- Efetuar o sensoriamento de temperatura e realizar o controle das janelas ou do arcondicionado para controlar temperatura.
- Controle do nível de água, informando quando deve ser realizado o reabastecimento de água da piscina ou regado as plantas do quintal.
- Sistema de seguraça a partir da detectação de movimento quando o usuário não estiver presente (o sistema é ativado por comando do usuário) Caso o usuário volte a residencia o sistema pode ser desativo pelo switch. Caso o sistema de segurança seja acionado o buzzer será ativado como forma de sinalizaçãoe para desativar o alarme é necessário apertar o botão novamente.

## Serão utilizados os seguintes componentes para realizar esse projeto:

**-Placa MEGA 2560 R3 + Fonte + Cabo USB para Arduino:**
Será utilizado para fazer a "conversão" entre sensores e dispositivos que realizam uma ação.

**-Sensor de Umidade e Temperatura DHT11:**
Será utilizado para determinar se as persianas estarão abertas ou não.

**-Sensor de presença e movimento PIR:**
Realizará o controle das luzes quando detectado o movimento no local, sem a necessidade de ir ao interruptor para controlar as luzes.

**-Sensor de gás MQ-2 inflamável e fumaça:**
Será colocado na cozinha. Quando ativado realizará o comando para o buzzer para sinalizar o proprietário, ativará a matriz de LED e desativará o controle das luzes com o interruptor impedindo qualquer tipo de acidente

**-Micro Servo SG92R 9g TowerPro:**
Trabalhará em conjunto com o sensor de umidade, realizando o controle das persianas

**-Módulo Sensor de Umidade/Nível Água Chuva:**
Será utilizado para controlar o nível de água da piscina e a disponibilidade de água para regar o jardim

**-Sensor ultrasônico HC-SR04:**
Será responsável por detectar presença nas entradas como portas e janelas e realizar o sensoriamento para abrir o portão

**-Display LCD 16×2 I2C Backlight Azul:**
Realizará a comunicação com o usuário para o controle do sistema de seguraça



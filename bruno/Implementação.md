 O código abaixo é uma junção de várias tarefas implementadas individualmente:

- A tarefa_garagem é responsável por fazer a manipulação do portão da garagem, através de um dado recebido da tarefa presença;

- Na tarefa presença há identificação de aproximação de um objeto através de um sensor ultrassônico;
- No caso da tarefa display, três situações possíveis com relação ao nível do reservatório de água da chuva são exibidas. Nível vazio, normal ou cheio dependendo do daddo recebido pela tarefa água;
- A tarefa água transforma os valores analógicos medidos pelo sensor nas três situações possíveis apresentadas na tarefa display e também aciona um LED quando nível vazio;
- Tarefa buzzer fica responsável por acionar o buzzer como um alarme dependendo do dado enviado pela tarefa gás;
- A tarefa gás mede possível vazamento de gás através de um sensor analógico que ao passar de um determinado valor emite sinal para tarefa buzzer;
- A tarefa_matriz foi implementada para mostrar a letra "D" quando ar condicionado está desligado e a letra "L" quando ar condicionado estiver ligado;
- O controle de acionamento do ar condicionado precisa diretamente da tarefa temp. Quando sensor de temperatura e umidade percebe uma temperatura acima de um valor pré-determinado em graus Célsius a tarefa temp emite um valor para tarefa presença;
- A tarefa presença ao receber um sinal da tarefa temp fica aguardando o sensor de presença para então emitir um sinal para acionamento do ar condicionado;
- A tarefa serial se faz necessária para comandos manuais de desligamento do alarme em caso de vazamento de gás através da letra "a", para fechamento e/ou abertura do portão da garagem através da letra "p" e também para desligar e/ou ligar o ar condicionado através da letra "q".


```C
// Inclui a biblioteca
#include <DHT.h>
#include <MatrizLed.h>
#include <Wire.h>
// Inclui a biblioteca do display
#include <LiquidCrystal_I2C.h>
// Inclui a biblioteca do servo
#include <Servo.h>
// Inclui a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>

// Define a entrada analógica 0 conectada ao sensor nivel dágua
#define PINO_SENSOR_AGUA A0
// Define o pino "51" onde o LED está conectado
#define LED_AGUA 51
// Pino digital onde está conectado o servo
#define SERVOPIN 3
//Define os pinos para o trigger e echo do sensor de proximidade
#define pino_trigger 52
#define pino_echo 53
//Define a entrada analógica 2 conectada ao sensor de gás
#define ENTRADA_GAS A2
//Define o pino "11" onde o buzzer está conectado
#define PINO_BUZZER 11
// CLK matriz de led
#define MCLK 5
// CS matriz de led
#define MCS 6
// DIN matriz de led
#define MDIN 7
// pino DHT11
#define DHT11PIN A4
// modelo DHT
#define DHTTYPE  DHT11
// pino PIR
#define pirCASA 50
// Define o endereço LCD para 0x27 para um display de 16 caracteres e 2 linhas
LiquidCrystal_I2C lcd(0x27, 20, 4);
// Nomeando o servo
Servo PORTAO;
// Inicializa o sensor de proximidade
Ultrasonic ultrasonic(pino_trigger, pino_echo);
// nomeando o DHT
DHT dht(DHT11PIN, DHTTYPE);
// nomeando a matriz
MatrizLed matriz;

// Função setup é executada apenas uma vez
void setup() {
  // inicia a comunicação serial a 9600 bits por segundo
  Serial.begin(9600);
  while (!Serial);
  // Configura o pino do LED como saída
  pinMode (LED_AGUA, OUTPUT);
  // inicializa o LCD
  lcd.init();
  //liga a luz de fundo
  lcd.backlight();
  //Porta onde o servo está conectado
  PORTAO.attach(SERVOPIN);
  /* Configuração dos pinos como entrada ou saída */
  pinMode(PINO_BUZZER, OUTPUT);

  /* Mantém buzzer desligado se acionamento for PNP
     Troque para HIGH para LOW caso NPN
  */
  digitalWrite(PINO_BUZZER, HIGH);
  // imprime uma mensagem inical
  // funcação F é uma indicação para manter a mensagem
  // na memória flash para economizar memória.
  Serial.println(F("Teste do DHT!"));

  pinMode (pirCASA, INPUT); // seta o pino do PIR com entrada
  // inicializa classe do sensor
  dht.begin();

  matriz.begin(MDIN, MCLK, MCS, 2);    // dataPin, clkPin, csPin, numero de matrizes de 8x8
  matriz.rotar(false);  // Caso ocorra falha
}

/* Essas variáveis são globais pois é necessário
   manter os valores independente do contexto de
   execução da função tarefa_1 */
const unsigned long periodo_tarefa_1 = 1000;
unsigned long tempo_tarefa_1 = millis();
const unsigned long periodo_tarefa_temp = 2000;
unsigned long tempo_tarefa_temp = millis();
const unsigned long periodo_tarefa_matriz = 3000;
unsigned long tempo_tarefa_matriz = millis();
int valorSensor; // Valor sensor reservatorio
int agua; // Nivel d'agua
// Armazena a posição do servo
int posp = 0;
bool abre_portao = false;
// Recebe a leitura feita no pino analógico do sensor de gás
int aSensor;
int estado_alarme = LOW;
bool ligar_alarme = false;
bool ligar_ar = false;

//Envia os valores para o PC
void tarefa_gas() {
  unsigned long tempo_atual = millis ();

  //Hora de enviar os dados caso tenha passado 1000 ms

  // Faz a leitura do sensor
  aSensor = analogRead(ENTRADA_GAS);

  // Envia para o computador (serial) os dados
  Serial.print("Leitura entrada analógica: ");
  Serial.println(aSensor);
  Serial.println();

  if (aSensor >= 400) {
    ligar_alarme = true;
  }

}
void tarefa_buzzer() {

  unsigned long tempo_atual = millis();

  /* Hora de executa essa tarefa */

  tempo_tarefa_1 = tempo_atual;

  if (ligar_alarme == true) {

    if (estado_alarme == HIGH) {
      estado_alarme = LOW;
      tone(PINO_BUZZER, 2000);
    }
    else {
      estado_alarme = HIGH;

      /* Depende do Buzzer:
         Se acionado com NPN, use apenas noTone(PINO_BUZZER);
         Se acionado com PNP, use abaixo para deixar o pino em nível alto.
          noTone(PINO_BUZZER);
          digitalWrite(PINO_BUZZER, HIGH);
      */
      noTone(PINO_BUZZER);
      digitalWrite(PINO_BUZZER, HIGH);
    }

  }
  else {
    noTone(PINO_BUZZER);
    digitalWrite(PINO_BUZZER, HIGH);
  }

}
/* Tarefa 1: envia o valor analógico para o PC */
void tarefa_agua() {
  unsigned long tempo_atual = millis();


  /* Hora de enviar os dados analógicos caso tenha passado 1000 ms */

  tempo_tarefa_1 = tempo_atual;

  valorSensor = analogRead(PINO_SENSOR_AGUA);

  Serial.print("Valor : ");
  Serial.println(valorSensor);

  //Acender o LED de acordo com o valor da entrada analógica
  if (valorSensor < 300) {
    digitalWrite(LED_AGUA, HIGH);
    agua = 0;

  }
  else {
    if ((valorSensor < 675) && (valorSensor > 300)) {

      digitalWrite(LED_AGUA, LOW);
      agua = 1;
    }
    else {
      digitalWrite(LED_AGUA, LOW);
      agua = 2;
    }
  }

}
void tarefa_display() {

  if (agua == 0) {
    // Posição do cursor
    lcd.setCursor(1, 0);
    // Imprime uma mensagem no LCD
    lcd.print(" Reservatorio            ");
    // Posição do cursor
    lcd.setCursor(1, 1);
    // Imprime uma mensagem no LCD
    lcd.print("    Vazio                ");

  }
  else if (agua == 1) {
    // Posição do cursor
    lcd.setCursor(1, 0);
    // Imprime uma mensagem no LCD
    lcd.print(" Reservatorio            ");
    // Posição do cursor
    lcd.setCursor(1, 1);
    // Imprime uma mensagem no LCD
    lcd.print(" Nivel Normal            ");
  }
  else if (agua == 2) {
    // Posição do cursor
    lcd.setCursor(1, 0);
    // Imprime uma mensagem no LCD
    lcd.print(" Reservatorio            ");
    // Posição do cursor
    lcd.setCursor(1, 1);
    // Imprime uma mensagem no LCD
    lcd.print(" Nivel Cheio             ");
  }

  else
    lcd.clear();


}

void tarefa_garagem() {
  PORTAO.write(posp);
  if (abre_portao == true) {
    if (posp < 90) {
      for (posp = 0; posp <= 90; posp += 1) {
        // Troca de posição
        PORTAO.write(posp);
        // Aguarda 10 ms
        delay(10);
      }
    }
  }
  else {
    if (posp > 0) {
      for (posp = 90; posp >= 0; posp -= 1) {
        // Troca de posição
        PORTAO.write(posp);
        // Aguarda 10 ms
        delay(10);
      }
    }
  }
}

void tarefa_serial() {

  /* Caso tenha recebido algum dado do PC */
  if (Serial.available()) {
    char dado_recebido = Serial.read();

    /* Depuração */
    Serial.print("Recebido:");
    Serial.println(dado_recebido);

    if (dado_recebido == 'a') { // desliga alarme
      if (ligar_alarme == true) {
        ligar_alarme = false;
      }
    }

    if (dado_recebido == 'p') { // abre ou fecha o portão
      if (abre_portao == true)
        abre_portao = false;
      else
        abre_portao = true;
    }

    if (dado_recebido == 'q') { // liga/desliga a mensagem de ar da matriz
      if (ligar_ar == true)
        ligar_ar = false;
      else
        ligar_ar = true;
    }
  }
}

void tarefa_presenca() {
  float cmMsec;
  cmMsec = ultrasonic.distanceRead(CM);

  // Se houver movimento
  if (cmMsec <= 8 ) {
    // Enviar para monitor serial
    Serial.println("portão abrindo");
    abre_portao = true;
  } else {
    // Se não houver movimento enviar para monitor serial
    Serial.println("-----");
  }

}
//Envia os valores interios para o PC
void tarefa_temp() {
  unsigned long tempo_atual = millis ();

  //Hora de enviar os dados caso tenha passado 2000 ms
  if (tempo_atual - tempo_tarefa_temp > periodo_tarefa_temp) {
    tempo_tarefa_temp = tempo_atual;
    // Lê a temperatura em Celsius
    float t = dht.readTemperature();


    // Verifica se alguma leitura falhou
    if (isnan(t)) {
      Serial.println(F("Falha ao ler o sensor DHT!"));
      return;
    }
    Serial.print("temperatura : ");
    Serial.println(t);

    // Envia para o computador (serial) os dados
    if ((digitalRead(pirCASA) == HIGH) && (t > 25))
      ligar_ar = true;
  }
}

void tarefa_matriz() {
  unsigned long tempo_atual = millis();

  /* Hora de executa essa tarefa */
  if (tempo_atual - tempo_tarefa_matriz > periodo_tarefa_matriz) {

    tempo_tarefa_matriz = tempo_atual;
    matriz.borrar();
    if (ligar_ar == true)
      matriz.escribirFrase("L");
    else
      matriz.escribirFrase("D");
  }
}



/* Função loop() é responsável por escalonar as tarefas.
   Essa função é executada eternamente enquanto o Arduino estiver  energizado */
void loop() {

  tarefa_garagem();
  tarefa_display();
  tarefa_buzzer();
  tarefa_matriz();
  tarefa_temp();
  tarefa_gas();
  tarefa_agua();
  tarefa_serial();
  tarefa_presenca();

}

```
Na imagem abaixo podemos observar a maquete já implementada com os componentes eletrônicos em funcionamento, na aba operação um vídeo explica o funcionamento do projeto.

<img src = "Maquete pronta.jpeg" alt = "Maquete pronta" width = "750" />

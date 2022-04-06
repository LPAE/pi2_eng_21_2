//################################################################################################################################//

// Projeto Integrador II do curso de Engenharia Eletrônica do IFSC

// Aluno: Fabio Schmitt Avelino


//################################################################################################################################//

//Inclusão das bibliotecas

#include "Wire.h"
#include "Ultrasonic.h"

#include <DHT.h>
#include <Servo.h>
#include <MatrizLed.h>
#include <LiquidCrystal_I2C.h>

//################################################################################################################################//

// Definição dos pinos que serão utilizados pelos sensores

#define PIR 52                                         // Pino ligado ao sensor PIR
#define RELE 12                                        // Pino ligado o módulo RELE
#define RELE2 7                                        // Pino ligado o módulo RELE
#define BUZZER 37                                      // Pino ligado o módulo BUZZER
#define SERVO 13                                       // Pino ligado ao SERVO
#define pinoEcho 5                                     // Pino de comunicaçao ligado ao Echo
#define pinoTrig 6                                     // Pino de comunicaçao ligado ao Trig


#define SENSOR_AGUA A5                                 // Pino ligado o sensor de água
#define GAS A6                                         // Pino ligado o sensor de gás
#define DHT11PIN A7                                    // Pino ligado o sensor de temperatura/umidade
#define DHTTYPE DHT11

//################################################################################################################################//

// Nomeando os componentes

Servo servo;
MatrizLed matriz;
DHT dht(DHT11PIN, DHTTYPE);
HC_SR04 ultrasonic(pinoEcho,pinoTrig);
LiquidCrystal_I2C lcd(0x27, 20, 4);

float distancia;
float temperatura;
float umidade;

int valorGAS;
int valorAGUA;
int valorPIR;
int abrirporta = 9;
int limiteGAS = 700;
int limiteAGUA = 315;
int limiteTEMPERATURA = 25;

//################################################################################################################################//

void setup()                                        // Função setup é executada apenas uma vez
{
  Serial.begin(9600);                               // Inicia a comunicação serial a 9600 bits por segundo
  
  dht.begin();

  lcd.init();                                       // Inicializa o LCD
  lcd.backlight();                                  // Liga a luz de fundo
  lcd.setCursor(1, 0);                              // Posição do cursor

  matriz.begin(10, 8, 9, 2);                        // dataPin, clkPin, csPin, numero de matrizes de 8x8
  matriz.rotar(false);                              // Caso ocorra falha


  servo.attach(SERVO);                              // Associa o pino escolhido ao servo motor
  servo.write(0);                                   // Inicia o servo na posição 0

  digitalWrite(BUZZER, HIGH);                       // Configura o buzzer para ficar desligado
  digitalWrite(RELE, LOW);                          // Configura o RELE para ficar desligado
  digitalWrite(RELE2, LOW);                         // Configura o RELE2 para ficar desligado


  pinMode(BUZZER, OUTPUT);                          // define o pin do buzzer com saída
  pinMode (RELE, OUTPUT);                           // define o pin do rele com saída
  pinMode (RELE2, OUTPUT);                          // define o pin do rele com saída
  
  pinMode (PIR, INPUT);                             // define pin do PIR como entrada
  pinMode(GAS, INPUT);                              // define pin do GAS como entrada
}

//################################################################################################################################//

void loop()                                         // Função loop é para executar repetidamente o código
{
  tarefa_temperatura();
  tarefa_GAS();
  tarefa_AGUA();
  tarefa_PIR();
  tarefa_ULTRASONIC();
}

//################################################################################################################################//

// VARIÁVEIS GLOBAIS

const unsigned long periodo_tarefa_temperatura = 1000;      // Tempo da tareda de temperatura = 1 segundo
unsigned long tempo_tarefa_temperatura = millis();

const unsigned long periodo_tarefa_GAS = 2000;              // Tempo da tareda do GAS = 2 segundos
unsigned long tempo_tarefa_GAS = millis();

const unsigned long periodo_tarefa_AGUA = 5000;             // Tempo da tareda da AGUA = 5 segundos
unsigned long tempo_tarefa_AGUA = millis();

const unsigned long periodo_tarefa_PIR = 1000;              // Tempo da tareda do PIR = 1 segundo
unsigned long tempo_tarefa_PIR = millis();

const unsigned long periodo_tarefa_ULTRASONIC = 500;        // Tempo da tareda do ULTRASONIC = 0,5 segundo
unsigned long tempo_tarefa_ULTRASONIC = millis();

//################################################################################################################################//

void tarefa_temperatura()
{
  unsigned long tempo_atual = millis ();

  //Hora de enviar os dados caso tenha passado 1000 ms
  if (tempo_atual - tempo_tarefa_temperatura > periodo_tarefa_temperatura)
  {
    tempo_tarefa_temperatura = tempo_atual;

    // Lê a umidade
    umidade = dht.readHumidity();
    // Lê a temperatura em Celsius
    temperatura = dht.readTemperature();
  
    if (temperatura>=limiteTEMPERATURA) 
    {
      digitalWrite(RELE, LOW);
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("VENTILADOR ON");
      lcd.setCursor(0,1);
      lcd.print("Temperatura=");
      lcd.print(temperatura);
    }
    else
    {
      digitalWrite(RELE, HIGH);
    }  
  }
}

//################################################################################################################################//

void tarefa_GAS()
{
  unsigned long tempo_atual = millis ();

  //Hora de enviar os dados caso tenha passado 2000 ms
  if (tempo_atual - tempo_tarefa_GAS > periodo_tarefa_GAS)
  {
    tempo_tarefa_GAS = tempo_atual;

    valorGAS = analogRead(GAS);

    if (valorGAS > limiteGAS)
    {
      digitalWrite(RELE2, LOW);
      tone(BUZZER, 2000);
      return;
    }
    else
    {
      digitalWrite(RELE2, HIGH);
      noTone(BUZZER);
      digitalWrite(BUZZER, HIGH);
    }
  }


}

//################################################################################################################################//

  void tarefa_AGUA()
  {
  unsigned long tempo_atual = millis ();

  //Hora de enviar os dados caso tenha passado 5000 ms
  if (tempo_atual - tempo_tarefa_AGUA > periodo_tarefa_AGUA)
  {
    tempo_tarefa_AGUA = tempo_atual;

    valorAGUA = analogRead(SENSOR_AGUA);

    if(valorAGUA>=limiteAGUA && umidade<=90)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("REGAR AS PLANTAS");
      lcd.setCursor(1,1);
      lcd.print("Umidade=");
      lcd.print(umidade);
      lcd.print("%");
      delay(2000);
    }
  }
  }

//################################################################################################################################//

void tarefa_PIR()
{
  unsigned long tempo_atual = millis ();

  //Hora de enviar os dados caso tenha passado 1000 ms
  if (tempo_atual - tempo_tarefa_PIR > periodo_tarefa_PIR)
  {
    tempo_tarefa_PIR = tempo_atual;

    if (digitalRead(PIR) == HIGH)
    {
      valorPIR = digitalRead(PIR);
      Serial.println("presença detectada");
      matriz.borrar();
      matriz.escribirCaracter('X' , 0);
      return;
    }
    else
    {
     Serial.println("Presença não detectada");
     matriz.borrar();
    }
  }
}

//################################################################################################################################//

void tarefa_ULTRASONIC()
{
  unsigned long tempo_atual = millis ();

  //Hora de enviar os dados caso tenha passado 500 ms
  if (tempo_atual - tempo_tarefa_ULTRASONIC > periodo_tarefa_ULTRASONIC)
  {
    tempo_tarefa_ULTRASONIC = tempo_atual;
    
    distancia = ultrasonic.distance();
     
    Serial.print("Distancia em cm: ");
    Serial.println(distancia);
    
    if (distancia<=abrirporta)
    {
     servo.write(-110);
    }
    else
    {
     servo.write(110);
    }
  }
}

//################################################################################################################################//
// FIM DO CÓDIGO
//################################################################################################################################//

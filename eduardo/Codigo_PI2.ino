// Projeto Integrador II do curso de engenharia eletrônica IFSC

// Aluno: Eduardo Tenfen dos Santos

// Professores: Luiz Alberto de Azevedo e Renan Augusto Starke

//===========================================================================//

//incluindo as bibliotecas

#include <Servo.h>
#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MatrizLed.h>

//===========================================================================//

//definindo os pinos

#define SERVO      13   //portão
#define RELE2      8    //ventilador
#define RELE1      23   //exaustor
#define BUZZER     31   //alarme/campainha
#define LED        10   //luz do escritório

#define MQ2DIG     22   //sensor de gás pino digital
#define PIR        9    //sensor de presença
#define MQ2        A6   //sensor de gás pino analógico
#define DHTPIN     11   //sensor de temperatura e umidade
#define ULT_TRIG   33   //sensor ultrassonico trig
#define ULT_ECHO   35   //sensor ultrassonico echo

#define DHTTYPE DHT11   // define modelo do sensor DHT como DHT 11

//===========================================================================//

DHT dht(DHTPIN, DHTTYPE);
Servo s;
MatrizLed matriz;
LiquidCrystal_I2C lcd(0x27, 20, 4);


bool portao = false;              //variavel para controlar se o portão abre ou fecha
const int limite_gas = 25;        //definine valor máximo de gás (nível de gás normal)
const int limite_distancia = 5;   //define o limite de distancia para avisar que tem vizitas
const float limite_temp = 23;     //define temperatura limite para acionar ventilador

//===========================================================================//

void comandos();
void tarefa_PIR (unsigned long tempo_atual);
void tarefa_DHT (unsigned long tempo_atual);
void tarefa_MQ2 (unsigned long tempo_atual);
void tarefa_HCSR04 (unsigned long tempo_atual);
void controle_portao (bool portao);

//===========================================================================//

void setup() {


  Serial.begin(9600);

  dht.begin();

  s.attach(SERVO);
  s.write(180);

  lcd.init();
  lcd.backlight();

  matriz.begin(50, 52, 51, 1);
  matriz.rotar(false); 

  pinMode(SERVO, OUTPUT);
  pinMode(RELE2, OUTPUT);
  pinMode(RELE1, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(ULT_TRIG, OUTPUT);
  
  pinMode(ULT_ECHO, INPUT);
  pinMode(MQ2DIG, INPUT);
  pinMode(DHTPIN, INPUT);
  pinMode(PIR, INPUT);

  digitalWrite(BUZZER, HIGH);
}

//===========================================================================//

void loop() {

  unsigned long meu_tempo_atual = millis();

  comandos();
  tarefa_PIR(meu_tempo_atual);
  tarefa_DHT(meu_tempo_atual);
  tarefa_MQ2(meu_tempo_atual);
  tarefa_HCSR04(meu_tempo_atual);
  
}

//===========================================================================//

//declarando variáveis globais

const unsigned long periodo_tarefa_DHT = 8000;      //tempo da tarefa de climatização = 8 segundos
unsigned long tempo_tarefa_DHT = millis();

const unsigned long periodo_tarefa_MQ2 = 5000;      //tempo da tarefa de alerta gás = 5 segundos
unsigned long tempo_tarefa_MQ2 = millis();

const unsigned long periodo_tarefa_PIR = 100;       //tempo da tarefa de iluminação = 0,1 segundo
unsigned long tempo_tarefa_PIR = millis();

const unsigned long periodo_desligar_luz = 600000;  //tempo da tarefa de desligar a luz = 10 minutos
unsigned long tempo_desligar_luz = millis();

const unsigned long periodo_tarefa_HCSR04 = 1000;   //tempo da tarefa de campainha = 1 segundo
unsigned long tempo_tarefa_HCSR04 = millis();

//===========================================================================//

void comandos() {
  if (Serial.available() != 0)
  {
    char tecla = Serial.read();
    switch (tecla)
    {
      case 'p':
        portao = !portao;
        controle_portao(portao);
        break;
      default:
        break;
    }
  }
}

//===========================================================================//

//tarefa de climatização
void tarefa_DHT(unsigned long tempo_atual)
{
  if (tempo_atual - tempo_tarefa_DHT > periodo_tarefa_DHT)
  {
    tempo_tarefa_DHT = tempo_atual;

    float t = dht.readTemperature();
    
    if (isnan(t))
    {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Ventilador");
        lcd.setCursor(1, 1);
        lcd.print("Falha na leitura do DHT");
      Serial.println("Falha na leitura do DHT");
    }
    else
    {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Temperatura");
      lcd.setCursor(1, 1);
      lcd.print(t);
      
      Serial.print(" Temperatura: ");
      Serial.print(t);
      Serial.println("ºC");
      
      if ((t > limite_temp)){
        digitalWrite(RELE2, HIGH); //liga ventilador
      }
      else {
        digitalWrite(RELE2, LOW);  //desliga ventilador
      }
    }

  }
}

//===========================================================================//

//tarefa de proteção contra acidentes com gás
void tarefa_MQ2(unsigned long tempo_atual)
{

  if (tempo_atual - tempo_tarefa_MQ2 > periodo_tarefa_MQ2)
  {
    tempo_tarefa_MQ2 = tempo_atual;


    int gas = analogRead(MQ2);

    gas = map(gas, 0, 1023, 0, 100);  //converte o valor do gás para porcentagem
     
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Nivel de gas");
    lcd.setCursor(1, 1);
    lcd.print(gas);
    
    Serial.print("Quantidade de gás: ");
    Serial.println(gas);
    
    if (gas > limite_gas)
    {
      digitalWrite(RELE1, HIGH);

      for (int repetir = 1; repetir <=5; repetir++)
      {

        for (int x = 0; x < 180; x++)
        {
          float seno;
          int frequencia;
              
          seno = (sin(x * 3.1416 / 180));
          frequencia = 1000 + (int(seno * 1000)); //Variando de 1000 a 2000 Hz
          tone(BUZZER, frequencia);
          delay(2);
        }
        noTone(BUZZER);
        digitalWrite(BUZZER, HIGH);
      }
        
      matriz.borrar();
      matriz.escribirFraseScroll("Alerta", 50);

      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Alerta! Nivel");
      lcd.setCursor(1, 1);
      lcd.print("de gas elevado");
      
      Serial.println("Alerta! Nível de gás elevado");
    }
    else
     digitalWrite(RELE1, LOW);
  }
}

//===========================================================================//

//tarefa de iluminação
void tarefa_PIR (unsigned long tempo_atual)
{
    if (tempo_atual - tempo_tarefa_PIR > periodo_tarefa_PIR)
    {
      tempo_tarefa_PIR = tempo_atual;

      if ((digitalRead (PIR)) == HIGH) //Se houver movimento faz
      {
        digitalWrite(LED, HIGH);  //liga a luz
        tempo_desligar_luz = tempo_atual;
      }
      else //Se não houver movimento
      {
        if (tempo_atual - tempo_desligar_luz > periodo_desligar_luz)
        {
          digitalWrite(LED, LOW);  //Desliga a luz
          tempo_desligar_luz = tempo_atual;
        }
      }
    }
}

//===========================================================================//

//tarefa de campainha
void tarefa_HCSR04 (unsigned long tempo_atual)
{
    if (tempo_atual - tempo_tarefa_HCSR04 > periodo_tarefa_HCSR04)
    {
       tempo_tarefa_HCSR04 = tempo_atual;
      
       digitalWrite(ULT_TRIG, LOW);
       delayMicroseconds(2);

       digitalWrite(ULT_TRIG, HIGH);
       delayMicroseconds(10);
       digitalWrite(ULT_TRIG, LOW);
       
       int duracao = pulseIn(ULT_ECHO, HIGH);
       
       int distancia = duracao * 0.034 / 2;
  
       if (distancia <= limite_distancia)
       {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Temos");
        lcd.setCursor(1, 1);
        lcd.print("Vizitas");

        Serial.println("Temos vizitas");

        for (int x = 0; x < 180; x++)
        {
          float seno;
          int frequencia;
          
          seno = (sin(x * 3.1416 / 180));
          frequencia = 1000 + (int(seno * 1000)); //Variando de 1000 a 2000 Hz
          tone(BUZZER, frequencia);
          delay(2);
        }
        noTone(BUZZER);
        digitalWrite(BUZZER, HIGH);
       }
    }
}

//===========================================================================//

//tarefa de abertura do portão
void controle_portao(bool c_portao)
{
  if (c_portao == true){
      s.write(90);

      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Portao");
      lcd.setCursor(1, 1);
      lcd.print("Aberto");
        
      Serial.println("Portão aberto");
  }
  else{
      s.write(180);
      
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Portao");
      lcd.setCursor(1, 1);
      lcd.print("Fechado");
      
      Serial.println("Portão fechado");
  }
}

//===========================================================================//

#include "DHT.h"
#include "LedControl.h"
#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA
#include "Ultrasonic.h"
#include <Servo.h>
 
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); //ENDEREÇO DO I2C E DEMAIS INFORMAÇÕES

//#define MINIBOMBA 52
//#define WATERPIN A1
#define DHTPIN A2 // Sinal
#define MQ2 A0 // PINO DO SENSOR MQ2
#define FAN 50 // RELÉ DO VENTILADOR
#define DISTT 24 // PINO TRIGGER
#define DISTE 22 // PINO ECHO
#define PIR 26 // PINO DO SENSOR DE PRESENÇA
#define BUZZER 12 // PINO DO BUZZER
#define TEMPO 500 // TEMPO DO SINAL DO BUZZER
#define PORTAO 13

#define DHTTYPE DHT11 // DHT 11

LedControl lc = LedControl(48,44,46,1);

DHT dht(DHTPIN, DHTTYPE);

Servo s; // Variável Servo
int pos=0; // Posição 


Ultrasonic ultrasonic(DISTT, DISTE);
float distcm=30.0;
bool pir=0;
bool buzzer=0;

byte LetraA[8] = {
  B00011000,
  B00100100,
  B01000010,
  B01000010,
  B01111110,
  B01000010,
  B01000010,
  B01000010
};

byte LetraB[8] = {
  B01111000,
  B01000100,
  B01000100,
  B01111000,
  B01000100,
  B01000100,
  B01000100,
  B01111000
};

byte LetraM[8] = {
  B01000010,
  B01100110,
  B01011010,
  B01011010,
  B01000010,
  B01000010,
  B01000010,
  B01000010
};

int mq2 = 300;

float h = 0;
float t = 0;
int frequencia=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Casa Automatizada!");
  dht.begin();
  lc.shutdown(0,false);
  lc.setIntensity(0,1);
  lc.clearDisplay(0);
  pinMode(MQ2, INPUT);
  pinMode(FAN, OUTPUT);
  s.attach(PORTAO);
  s.write(0); // Inicia motor posição zero
  pinMode(PIR, INPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, HIGH);
  //pinMode(MINIBOMBA, OUTPUT);
  lcd.begin (16,2); //SETA A QUANTIDADE DE COLUNAS(16) E O NÚMERO DE LINHAS(2) DO DISPLAY
  lcd.setBacklight(HIGH); //LIGA O BACKLIGHT (LUZ DE FUNDO)
}

void loop() {
  // put your main code here, to run repeatedly:
  bool pir = digitalRead(PIR);
  Serial.print("Presença na porta da frente: ");
  Serial.println(pir); 
  int mq2 = analogRead(MQ2);
  long microsec = ultrasonic.timing();
  float distcm = ultrasonic.convert(microsec, Ultrasonic::CM);
  GasDetector(mq2);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("dist: ");
  Serial.println(distcm); 
  mostrar_LCD (h, t);
  portao(pir, distcm);
  //Regar(h);
     
}

// Funções

void alarme_ativado() {  

     for (frequencia = 100; frequencia < 5000; frequencia += 1) 
      {
        tone(BUZZER, frequencia, TEMPO); 
      }

}

void fechaPortao(){
  for(pos = 90; pos > 0; pos--){ //fecha portao
    s.write(pos);
    delay(10);
}
}

void abrePortao(){
for(pos = 0; pos < 90; pos++){ //abre portao
    s.write(pos);
    delay(10);
}

while(1){

Serial.println("1. Aperte 1 para fechar o portão.");
  
if (Serial.available() > 0) { //Teste se porta serial esta recebendo dados
  char tecla;
  tecla = Serial.read(); // Lê o valor digitado pelo usuário.
  if (tecla == '1') 
  {
      fechaPortao();
      break; 
  }
}
}
}

void portao (bool pir, float distcm){
if(distcm <= 20.00){
  alarme_ativado(); // aciona a campainha
  noTone(BUZZER);
  digitalWrite(BUZZER, HIGH);
  
  while(1){

  Serial.println("0. Aperte 0 para não abrir o portão.");
  Serial.println("1. Aperte 1 para abrir o portão.");
  
  if (Serial.available() > 0) { //Teste se porta serial esta recebendo dados
    char tecla;
    tecla = Serial.read(); // Lê o valor digitado pelo usuário.
    if (tecla == '0') 
    {
      break; 
    }
    if (tecla == '1') 
    {
      abrePortao();
      break; 
    }
  }
  }
}

if(pir == HIGH){ //porta da frente
    alarme_ativado();   // aciona a campainha de novo
    noTone(BUZZER);
    digitalWrite(BUZZER, HIGH);
    }
}    

void display_A() {
  for(int i=0;i<8;i++) {
    lc.setRow(0,i,LetraA[i]);
  }
}

void display_B() {
  for(int i=0;i<8;i++) {
    lc.setRow(0,i,LetraB[i]);
  }
}

void display_M() {
  for(int i=0;i<8;i++) {
    lc.setRow(0,i,LetraM[i]);
  }
}

void GasDetector(int mq2){ // Função de detecção de gás
if(mq2 > 180 and mq2 <= 280){
  display_M();
}

if(mq2 <= 180){
  display_B();
}

if(mq2 > 280){
  display_A();

  while(mq2 > 280){
    digitalWrite(FAN, HIGH);
  }
  }
    digitalWrite(FAN, LOW);
}

void mostrar_LCD (float umidade, float temperatura){

  lcd.setCursor(0,0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("T = "); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.print(temperatura); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.print("C");
  lcd.setCursor(0,1); //SETA A POSIÇÃO DO CURSOR
  lcd.print("U = "); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.print(umidade); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.print("%");
  delay(10);
}

/*void Regar (float umidade){
  if (umidade >= 30.00){
    digitalWrite(MINIBOMBA, HIGH);
    delay(10);
  }
  else{
    digitalWrite(MINIBOMBA,LOW);
  }
}
*/

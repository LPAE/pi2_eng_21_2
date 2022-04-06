#include "DHT.h"
#include "Ultrasonic.h"

#define WATERPIN A13 // PINO SENSOR NÍVEL DA ÁGUA DA CHUVA

#define DISTT 47 // PINO TRIGGER
#define DISTE 49 // PINO ECHO

#define DHTPIN A12 // Sinal
#define DHTTYPE DHT11 // DHT 11
#define MQ2 A15 // PINO DO SENSOR MQ2

#define PIR 22 // PINO DO SENSOR DE PRESENÇA
#define BUZZER 12 // PINO DO BUZZER
#define TEMPO 10 // TEMPO DO SINAL DO BUZZER

Ultrasonic ultrasonic(DISTT, DISTE);

float distcm=0;
bool pir=0;
bool buzzer=0;

DHT dht(DHTPIN, DHTTYPE);

int frequencia=0;

void setup() 
{
  Serial.begin(9600);
  Serial.println("DHT11, Sensor de Água, HCSR04, MQ2, PIR  - Teste!");
  
  pinMode(WATERPIN, INPUT);
  pinMode(MQ2, INPUT);
 
  pinMode(PIR, INPUT);
  pinMode(BUZZER, OUTPUT);
  
  dht.begin();
}
 
void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // referente ao sensor de nível da água
  int a = analogRead(WATERPIN); 
  int mq2 = analogRead(MQ2); 
  
  bool pir = digitalRead(PIR);
  bool buzzer = digitalRead(BUZZER);
  long microsec = ultrasonic.timing();
  float distcm = ultrasonic.convert(microsec, Ultrasonic::CM);
 
  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.print(" \t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" °C");
  Serial.print(" \t");
  Serial.print("Nível da Água: ");
  Serial.print(a);
  Serial.print(" \t");
  Serial.print("Distancia em cm: ");
  Serial.print(distcm);
  Serial.print(" \t");
  Serial.print("Nível de Gás: ");
  Serial.print(mq2);
  Serial.print(" \t");
  Serial.print("Buzzer:  ");
  Serial.print(buzzer);
  Serial.print(" \t");
  Serial.print("Presença: ");
  Serial.println(pir);  

  alarme_ativado(); // aciona a campainha
  delay(2000)
  noTone(BUZZER);
  digitalWrite(BUZZER, HIGH);
    
}


void alarme_ativado() {  

     for (frequencia = 100; frequencia < 5000; frequencia += 1) 
      {
        tone(BUZZER, frequencia, TEMPO); 
      }

}

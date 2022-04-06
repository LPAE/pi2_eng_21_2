# Sensor de Gás

O sensor de gás detecta a presença de gás na cozinha, caso exista uma concentração maior que 300ppm de gás o sensor ativa o sistema de segurança onde ativa a matriz de led para funcionar como iluminação, abre a janela da cozinha, e ativa o buzer para indicar que existe vazamento de gás na cozinha, para desativar o sistema de segurança basta inserir "a" na entrada serial.
Para realizar essa funcionalidade foi utilizado o sensor de gás, servo motor, matriz de led e o buzzer.

<img src = "sensor gas fritzing.png" alt = "portao circuito" width = "1000" />

Código Utilizado:

```C
#define ENTRADA_GAS A2
#define buzzer 8
#define JANELAPIN 5

#include <LedControl.h>
#include <Servo.h>


LedControl lc=LedControl(10,12,11,1);

Servo JANELA;


int aSensor;
int posj = 0;
byte ALL[] = {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111}; //a matriz "ALL" tem os valores dos leds a serem ligados, no caso todos

void setup()
{
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);


  lc.shutdown(0,false);   //inicializa a matriz de led
  lc.setIntensity(0,8);   //defini a intensidade
  lc.clearDisplay(0);     //limpa os dados da matriz

  
  
  JANELA.attach(JANELAPIN);
}

void loop()
{
  tarefa_janela();
  tarefa_buzzer_gas();
  tarefa_matriz();
  tarefa_gas();
  tarefa_serial();
}

const unsigned long periodo_tarefa_2 = 1000;
unsigned long tempo_tarefa_2 = millis();

bool ligar_matriz = false;
bool msg_gas = false;
int estado_alarme = LOW;
bool ligar_alarme = false;
bool abre_janela = false;


void tarefa_gas() {
  unsigned long tempo_atual = millis ();
  
  if (tempo_atual - tempo_tarefa_2 > periodo_tarefa_2) {

    aSensor = analogRead(ENTRADA_GAS);

    Serial.print("Leitura entrada analógica: ");
    Serial.println(aSensor);
    Serial.println();

    if (aSensor >= 300) {
      ligar_alarme = true;
      ligar_matriz = true;
      msg_gas = true;
      abre_janela = true;

    }
  }
}

void tarefa_matriz() {
  lc.clearDisplay(0);
  if (ligar_matriz == true) {
    if (msg_gas == true) {
      lc.setRow(0,0,ALL[0]);
      lc.setRow(0,1,ALL[1]);
      lc.setRow(0,2,ALL[2]);
      lc.setRow(0,3,ALL[3]);
      lc.setRow(0,4,ALL[4]);
      lc.setRow(0,5,ALL[5]);
      lc.setRow(0,6,ALL[6]);
      lc.setRow(0,7,ALL[7]);
    }
  }
}

void tarefa_buzzer_gas() {

  unsigned long tempo_atual = millis();

  if (tempo_atual - tempo_tarefa_2 > periodo_tarefa_2) {

    tempo_tarefa_2 = tempo_atual;

    if (ligar_alarme == true) {

      if (estado_alarme == HIGH) {
        estado_alarme = LOW;
        tone(buzzer, 2000);
      }
      else {
        estado_alarme = HIGH;
        noTone(buzzer);
        digitalWrite(buzzer, HIGH);
      }

    }
    else {
      noTone(buzzer);
      digitalWrite(buzzer, HIGH);
    }
  }

}


void tarefa_serial() {


  if (Serial.available()) {
    char dado_recebido = Serial.read();

   

    if (dado_recebido == 'a') { 
      if (ligar_alarme == true)
        ligar_alarme = false;
      if (ligar_matriz == true)
        ligar_matriz = false;
      if (msg_gas == true)
        msg_gas = false;
    }

    if (dado_recebido == 'j') { 
      if (abre_janela == true)
        abre_janela = false;
      else
        abre_janela = true;
    }

  }
}

void tarefa_janela() {

  JANELA.write(posj);
  if (abre_janela == true) {
    if (posj < 110) {
      for (posj = 0; posj <= 110; posj += 1) {
        JANELA.write(posj);
        delay(10);
      }
    }
  }
  else {
    if (posj > 0) {
      for (posj = 110; posj >= 0; posj -= 1) {
        JANELA.write(posj);
        delay(10);
      }
    }
  }
}
```


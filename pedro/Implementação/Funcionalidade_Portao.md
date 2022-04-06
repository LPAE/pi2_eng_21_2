# Sensor de Visitas no Portão

O sensor de visitas detecta a presença de algum altomóvel a uma distância menor que 4cm acionando o buzzer para informar o usuário que existe uma visita, inserindo a letra "p" no no computador é possível controlar o servo motor para abrir ou fechar a garagem
Para montar essa funcionalidade foi utilizado o sensor ultrasonico, um servo motor e o buzzer como mostra a figura:

<img src = "sensor presenca fritzing.png" alt = "portao circuito" width = "1000" />

Código Utilizado:

```C
#include <Servo.h>
#include <Ultrasonic.h>

#define buzzer 8
#define SERVOPIN 6
#define pino_trigger 52
#define pino_echo 53

Servo PORTAO;
Ultrasonic ultrasonic(pino_trigger, pino_echo);
int posp = 0;
long distancia;

void setup()
{
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);

  PORTAO.attach(SERVOPIN);
  digitalWrite(buzzer, HIGH );
}

bool ligar_alarme = false;
bool abre_portao = false;
const unsigned long periodo_tarefa_1 = 1000;
unsigned long tempo_tarefa_1 = 0;
int estado_alarme = LOW;



void loop()
{
  tarefa_buzzer();
  tarefa_portao();
  tarefa_serial();
  tarefa_visita();
}


void tarefa_portao() {
  PORTAO.write(posp);
  if (abre_portao == true) {
    if (posp < 90) {
      for (posp = 0; posp <= 90; posp += 1) {
        PORTAO.write(posp);
        delay(10);
      }
    }
  }
  else {
    if (posp > 0) {
      for (posp = 90; posp >= 0; posp -= 1) {
        PORTAO.write(posp);
        delay(10);
      }
    }
  }
}

void tarefa_serial() {

  if (Serial.available()) {
    char dado_recebido = Serial.read();

    /* Depuração */
    Serial.print("Recebido:");
    Serial.println(dado_recebido);

    if (dado_recebido == 'p') {
      if (abre_portao == true)
        abre_portao = false;
      else {
        if (ligar_alarme == true)
          ligar_alarme = false;
        abre_portao = true;
      }
    }
  }
}

void tarefa_visita() {

  distancia = ultrasonic.Ranging(CM);


  if (distancia <= 4 ) {
    Serial.println("Presença detectada no portão");
    ligar_alarme = true;
  } else {
    Serial.println("-----");
    ligar_alarme = false;
  }
}

void tarefa_buzzer() {

  unsigned long tempo_atual = millis();

  if (tempo_atual - tempo_tarefa_1 > periodo_tarefa_1) {

    tempo_tarefa_1 = tempo_atual;

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
```

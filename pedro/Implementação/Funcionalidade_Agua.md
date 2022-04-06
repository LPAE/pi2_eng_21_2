# Sensor de Nível de Água

O sensor de nível de Água faz o sensoriamento da quantidade de água que está presenta na piscina, caso esse nível abaixe de 300 ele informa atravez do led verde que é necessário encher a pscina caso o nível de água suba para mais que 300 ele desliga o led.
Para implementar essa funcionalidade foi utilizada o sensor de nível de água, led verde

<img src = "sensor agua fritzing.png" alt = "portao circuito" width = "1000" />

Código Utilizado:

```C
#define PINO_SENSOR_AGUA A7
#define LED 51

#include <Servo.h>

void setup() {
  Serial.begin(9600);
  pinMode (LED, OUTPUT);

}
const unsigned long periodo_tarefa_agua = 1000;
unsigned long tempo_tarefa_agua = millis();


void loop() {
  tarefa_agua();
}

void tarefa_agua() {
  unsigned long tempo_atual_agua = millis();

  int valorSensor;

  if (tempo_atual_agua - tempo_tarefa_agua > periodo_tarefa_agua) {
    tempo_tarefa_agua = tempo_atual_agua;

    valorSensor = analogRead(PINO_SENSOR_AGUA);

    Serial.print("Valor : ");
    Serial.println(valorSensor);

    if (valorSensor > 300) {
      digitalWrite(LED, HIGH);

    }
    else {
      digitalWrite(LED, LOW);
    }
  }
}
```

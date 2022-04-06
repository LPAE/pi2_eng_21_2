# Sensor de temperatura

O sensor de temperatura realiza detecta se a temperatura é maior ou menor que 28°C, caso seja maior ele aciona o relé que ativa ar condicionado representado por um led branco caso a temperatura seja menor que 28°C ele desliga o relé.
Para implementar esa funcionalidade foi utilizado o sensor de temperatura, o módulo relé e um led

<img src = "sensor temp fritzing.png" alt = "portao circuito" width = "1000" />

Código Utilizado:

```C
#include <DHT.h>

#define DHT11PIN 2
#define DHTTYPE  DHT11
#define RELE 13

DHT dht(DHT11PIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("Teste do DHT!"));
  dht.begin();
  pinMode (RELE, OUTPUT);
}

void loop()
{
  tarefa_temp();
}
const unsigned long periodo_tarefa_temp = 2000;
unsigned long tempo_tarefa_temp = millis();

void tarefa_temp() {
  unsigned long tempo_atual_temp = millis ();

  if (tempo_atual_temp - tempo_tarefa_temp > periodo_tarefa_temp) {

    tempo_tarefa_temp = tempo_atual_temp;
    
    float t = dht.readTemperature();

    if (isnan(t)) {
      Serial.println(F("Falha ao ler o sensor DHT!"));
      return;
    }
    Serial.print("Valor : ");
    Serial.println(t);
        
    if (t > 28)
      digitalWrite(RELE, LOW);
    else
      digitalWrite(RELE, HIGH);
  }
}
```

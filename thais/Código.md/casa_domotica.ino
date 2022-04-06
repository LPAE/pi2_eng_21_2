#define ENTRADA_GAS A6
#define PINO_BUZZER 2
#define pirCASA 40 // Define o PIR com o valor "40" que é onde o pino digital está conectado
#define LUZ_CASA 50 // Define o pino do led de luz no valor "50"
#define pirMURO 7
// Pino digital onde está conectado o servo
#define PORTAOPIN 11
// Define o PIR com o valor "7" que é onde o pino digital está conectado
#define pirPORTAO 53
//Define os pinos para o trigger e echo do sensor de proximidade
#define pino_trigger 49
#define pino_echo 51

// Inclui a biblioteca
#include <Servo.h>
//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>

// Nomeando o servo
Servo PORTAO;
//Inicializa o sensor de proximidade
Ultrasonic ultrasonic(pino_trigger, pino_echo);

/* Essas variáveis são globais pois é necessário
   manter os valores independente do contexto de
   execução da função tarefa_1 */
const unsigned long periodo_tarefa_gas = 1000;
unsigned long tempo_tarefa_gas = millis();
const unsigned long periodo_tarefa_portao = 1000;
unsigned long tempo_tarefa_portao = 0;
const unsigned long periodo_tarefa_buzzer = 1000;
unsigned long tempo_tarefa_buzzer = 0;

int estado_alarme = LOW;
bool ligar_alarme = false;

bool abre_portao = false;

// Recebe a leitura feita no pino analógico do sensor de gás
int aSensor;

// Armazena a posição do servo do portão
int posp = 0;

// Função setup é executada apenas uma vez
void setup()
{
  pinMode (pirCASA, INPUT);
  pinMode (pirMURO, INPUT);

  // Configura o pino como entrada
  pinMode (pirPORTAO, INPUT);

  //Porta onde o servo está conectado
  PORTAO.attach(PORTAOPIN);

  PORTAO.write(posp);

  // Inicia a comunicação serial a 9600 bits por segundo
  Serial.begin(9600);
  while (!Serial);

  /* Configuração dos pinos como entrada ou saída */
  pinMode(PINO_BUZZER, OUTPUT);
  pinMode(LUZ_CASA, OUTPUT);

  /* Mantém buzzer desligado se acionamento for PNP
     Troque para HIGH para LOW caso NPN
  */
  digitalWrite(PINO_BUZZER, HIGH);
}

// Função loop é para executar repetidamente o código
void loop()
{
  tarefa_buzzer();
  tarefa_gas();
  tarefa_luz();
  tarefa_invasao();
  tarefa_serial();
  tarefa_portao();
  tarefa_garagem();
}





//Envia os valores interios para o PC
void tarefa_gas() {
  unsigned long tempo_atual = millis ();

  //Hora de enviar os dados caso tenha passado 1000 ms
  if (tempo_atual - tempo_tarefa_gas > periodo_tarefa_gas) {

    // Faz a leitura do sensor
    aSensor = analogRead(ENTRADA_GAS);

    // Envia para o computador (serial) os dados
    Serial.print("Leitura entrada analógica: ");
    Serial.println(aSensor);
    Serial.println();

    if (aSensor >= 400)
      ligar_alarme = true;


  }
}

void tarefa_buzzer() {

  unsigned long tempo_atual = millis();

  /* Hora de executa essa tarefa */
  if (tempo_atual - tempo_tarefa_buzzer > periodo_tarefa_buzzer) {

    tempo_tarefa_buzzer = tempo_atual;

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

}

void tarefa_luz()
{
  // Se houver movimento
  if (digitalRead(pirCASA) == HIGH) {
    // Enviar para monitor serial
    Serial.println("Luz acesa");
    digitalWrite(LUZ_CASA, HIGH); // acender luz
  } else {
    // Se não houver movimento enviar para monitor serial
    Serial.println("Luz apagada");
    digitalWrite(LUZ_CASA, LOW); //apagar luz
  }
}

void tarefa_invasao()
{
  // Se houver movimento
  if (digitalRead(pirMURO) == HIGH) {
    // Enviar para monitor serial
    Serial.println("Presença detectada");
    ligar_alarme = true;

  }
}

void tarefa_serial() {

  /* Caso tenha recebido algum dado do PC */
  if (Serial.available()) {
    char dado_recebido = Serial.read();

    /* Depuração */
    Serial.print("Recebido:");
    Serial.println(dado_recebido);

    if (dado_recebido == 'a')
      if (ligar_alarme == true)
        ligar_alarme = false;
      else
        ligar_alarme = true;

    if (dado_recebido == 'p') {// abre ou fecha o portão
      if (abre_portao == true)
        abre_portao = false;
      else
        abre_portao = true;
    }

  }
}

void tarefa_portao() {
  unsigned long tempo_atual = millis();

  if (tempo_atual - tempo_tarefa_portao > periodo_tarefa_portao) {
    tempo_tarefa_portao = tempo_atual;

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
}

void tarefa_garagem() {
  float cmMsec;
  cmMsec = ultrasonic.distanceRead(CM);

  // Se houver movimento próximo do portão
  if ((digitalRead(pirPORTAO) == HIGH) && cmMsec <= 5 ) {
    // Enviar para monitor serial
    Serial.println("Presença detectada no portão");
    if (abre_portao == false)
    abre_portao = true;
  }
}

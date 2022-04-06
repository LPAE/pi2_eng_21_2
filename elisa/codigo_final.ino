//Bibliotecas Utilizadas
#include <Servo.h>                                // Biblioteca do Motor Servo
#include <Wire.h>                                 // Parte complementar da biblioteca do Display 16x2 para comunicação I2C
#include <LiquidCrystal_I2C.h>                    // Biblioteca do Display 16x2 com comunicação I2C

// LEDS
#define LED1 13
#define LED2 12
#define LED3 6
#define LED4 10
#define LED5 9
#define LED6 8
#define LED7 7

// SENSOR FOTORESISTOR LDR
#define PINO_LDR A0

// SENSOR DE GÁS E FUMAÇA
#define ENTRADA_DIGITAL 53
#define ENTRADA_ANALOGICA A1

// BUZZER
#define PINO_BUZZER 5

// SENSOR DE PRESENÇA PIR
#define PINO_PIR 40

// SERVO
#define PINO_SERVO_PORTA 47
Servo motor1; 
#define PINO_SERVO_GARAGEM 46
Servo motor2; 

// SENSOR DE NÍVEL DE ÁGUA
#define PINO_AGUA A2

//Variáveis Sensor Fotoresistor LDR
  int aSensorLDR;
  int limite_de_luz = 600;                           // Configura a intensidade luminosa para ligar ou desligar os LEDs

//Variáveis Sensor de Gás e Fumaça
  bool dSensorGas;
  int aSensorGas;
  int limite_de_gas = 300;                          // Configura a concentração limite de gás normal (Valor Máximo)

//Variáveis Buzzer
  int estado_alarme = LOW;
  bool ligar_alarme = false;

//Variáveis Servo Motor
  int posicao_motor1 = 90;                            // Configura a posição inicial do Motor Servo para 0°
  int posicao_motor2 = 180; 

//Variáveis Sensor de Nìvel de Água
  int aSensorAgua;
  int normal_de_agua = 300;

//Variáveis LCD 16X2
  LiquidCrystal_I2C lcd(0x27, 16, 2);               // Configurando Display LCD 16x2 no endereço 0x27 para 16 colunas e 2 linhas

//Variáveis das Tarefas
  const unsigned long periodo_tarefa_2 = 1000;
  unsigned long tempo_tarefa_2 = millis();
  const unsigned long periodo_tarefa_3 = 10000;
  unsigned long tempo_tarefa_3 = millis();
  const unsigned long periodo_tarefa_4 = 1000;
  unsigned long tempo_tarefa_4 = millis();



void setup()
{

  Serial.begin(9600);

  //SETUP LEDS
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  pinMode (LED3, OUTPUT);
  pinMode (LED4, OUTPUT);
  pinMode (LED5, OUTPUT);
  pinMode (LED6, OUTPUT);
  pinMode (LED7, OUTPUT);

  // SETUP FOTORESISTOR LDR
  pinMode(PINO_LDR, INPUT);

  // SETUP GÁS E FUMAÇA
  pinMode(ENTRADA_DIGITAL, INPUT);

  //SETUP BUZZER
  pinMode(PINO_BUZZER, OUTPUT);
  /* Mantém buzzer desligado se acionamento for PNP
     Troque para HIGH para LOW caso NPN
  */
  digitalWrite(PINO_BUZZER, HIGH);

  //SETUP PIR
  pinMode(PINO_PIR, INPUT);

  //SETUP SERVO
  motor1.attach(PINO_SERVO_PORTA);                       // Associa o pino escolhido ao servo motor
  motor1.write(posicao_motor1);                     // Inicia o Motor Servo na posição 0°
  motor2.attach(PINO_SERVO_GARAGEM);                       // Associa o pino escolhido ao servo motor
  motor2.write(posicao_motor2);                     // Inicia o Motor Servo na posição 0°

  //SETUP AGUA
  pinMode(PINO_AGUA, INPUT);

  //SETUP LCD
  lcd.init();                                     // Inicia o LCD DISPLAY 16x2
  lcd.backlight();                                // Liga a iluminação do LCD Display 16x2

  //COMANDOS MONITOR SERIAL
  Serial.flush();
  Serial.println(" Pressione a tecla 'G' para fechar a garagem");

}

  void tarefa_1(unsigned long tempo_atual);
  void tarefa_2(unsigned long tempo_atual);
  void tarefa_3(unsigned long tempo_atual);
  void tarefa_4(unsigned long tempo_atual);
  void botoes();

void loop()
{

  unsigned long meu_tempo_atual = millis();

  tarefa_1(meu_tempo_atual);
  tarefa_2(meu_tempo_atual);
  tarefa_3(meu_tempo_atual);
  tarefa_4(meu_tempo_atual);
  botoes();

}

//Tarefa_1 = SENSOR FOTORESISTOR PARA LIGAR E DESLIGAR OS LEDS
void tarefa_1(unsigned long tempo_atual) {
  aSensorLDR = analogRead(PINO_LDR);

  if(aSensorLDR < limite_de_luz){
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, HIGH);
    digitalWrite(LED6, HIGH);
    digitalWrite(LED7, HIGH);
  }
  else{
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);
    digitalWrite(LED7, LOW);
  }
}

//Tarefa_2 = SENSOR DE GÁS E FUMAÇA FAZ A LEITURA
void tarefa_2(unsigned long tempo_atual) {

  //Hora de enviar os dados caso tenha passado 1000 ms
  if (tempo_atual - tempo_tarefa_2 > periodo_tarefa_2) {
    
    dSensorGas = digitalRead(ENTRADA_DIGITAL);
    aSensorGas = analogRead(ENTRADA_ANALOGICA);

    tempo_tarefa_2 = tempo_atual;
    lcd.setCursor(0,0);
    lcd.print("GAS: "); 
    lcd.println(aSensorGas);
    lcd.setCursor(0,0);
    delay(100);
    if(aSensorGas > limite_de_gas)
    {
      Serial.println("ALERTA!!!! VAZAMENTO DE GÁS DETECTADO!!!!");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("VAZAMENTO GAS");
      lcd.setCursor(4,1);
      lcd.print("DETECTADO");
      for (int repetir = 1; repetir <=20; repetir++)
      {
        for (int x = 180; x > 0; x--)
        {
          float sen;
          int f;
            
          sen = (sin(x * 3.1416 / 180));
            
          f = 500 + (int(sen * 1000));
          tone(PINO_BUZZER, f);                                              // Envia a frequência do som para o BUZZER
          delay(2);
          }
      noTone(PINO_BUZZER);                                                  // Desliga buzzer
      digitalWrite(PINO_BUZZER, HIGH);
      
      digitalWrite(LED1, LOW);                                        // Apaga todas as luzes como proteção a explosão
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      digitalWrite(LED5, LOW);
      digitalWrite(LED6, LOW);
      digitalWrite(LED7, LOW);

      motor1.write(0);                                                // Abre a porta para facilitar a saída do gás
        }
     lcd.clear();         

    }
  }
}

//Tarefa_3 = SENSOR DE PRESENÇA ABRE A GARAGEM
void tarefa_3(unsigned long tempo_atual){

  if (tempo_atual - tempo_tarefa_3 > periodo_tarefa_3) {
    
    tempo_tarefa_3 = tempo_atual;
    
    bool movimento = digitalRead(PINO_PIR);                                     // Lê o Sensor de movimento - PIR
    if (movimento == HIGH ){
      Serial.println("MOVIMENTO DETECTADO");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("VEICULO ENTRANDO");
      lcd.setCursor(5,1);
      lcd.print("CUIDADO");
      motor2.write(90);
      for (int repetir = 1; repetir <=3; repetir++)                       // tempo portao
        {
      
      }
      lcd.clear();                                                        // Limpa o Display do LCD
      motor2.write(-90);
      }
    else (movimento == LOW );{                                            // Função vazia pois não quero que faça nada quando não detecta movimento. Apenas quando houver movimento
      
    }
  }
}

//Tarefa_4 = SENSOR DE NÍVEL DE ÁGUA AVISA PELO LCD
void tarefa_4(unsigned long tempo_atual){
  if (tempo_atual - tempo_tarefa_4 > periodo_tarefa_4) {
    tempo_tarefa_4 = tempo_atual;

    aSensorAgua = analogRead(PINO_AGUA);



    
    if (aSensorAgua < normal_de_agua){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("FALTA DE ÁGUA");
      lcd.setCursor(4,1);
      lcd.print("DETECTADA");
      
    }
  }
}

void botoes(){
  if (Serial.available() > 0) {
    char letra;
    letra = Serial.read();
    if (letra == 'G'){
      motor2.write(180);
    }
  }
  Serial.flush();
}

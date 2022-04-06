# Alarme de Segurança

O alarme de segurança mostra no display que está aguardando para ser ativado, quando o usuário interage com o push button ele aciona em seguida o alarme escreve uma mensaguem no display avisando que o alarme será ativo após 9 segundos após isso o alarme está ativo, e mostra no display seu estado de funcionamento, quando é detectado qualquer tipo de movimento pelo sensor PIR o sistema ativa o Buzzer informando que um movimento foi detectado, o Alarme pode ser desativado quando o usuário interage com o push button em qualquer estado de funcionamento do alarme.
Para implementar a funcionalidade de alarme foi utilizado o sensor PIR o display LCD um Push button e o Buzzer como mostra o esquemático.

<img src = "alarme fritzing.png" alt = "portao circuito" width = "1000" />

Código Utilizado:

```C
#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define buzzer    8
#define pir       7

int screenOffMsg =  0;
int botao = 3;
int pressionado = 0;
int ligado = 0;
int valuePIR;
boolean enteredPassword;
boolean activated = false; 
boolean isActivated;
boolean activateAlarm = false;
boolean alarmActivated = false;

void setup() { 
  lcd.init();        
  lcd.backlight();  
  lcd.clear();      
  pinMode(buzzer, OUTPUT); 
  pinMode(pir, INPUT); 
  pinMode(botao, INPUT);
  digitalWrite(buzzer,HIGH);
}

unsigned long ultimociclo = millis();
unsigned long ultimociclo2 = millis();
unsigned long periodo = 1000;


void loop() {
  
  
  if (activateAlarm) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Alarm will be");
    lcd.setCursor(0,1);
    lcd.print("activated in");

    
    
    int countdown = 9; 
    while (countdown != 0) {
      unsigned long tempoagora = millis();
      if (tempoagora - ultimociclo > periodo){
        ultimociclo = tempoagora;

      lcd.setCursor(13,1);
      lcd.print(countdown);
      countdown--;
      }
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Alarm Activated!");
    activateAlarm = false;
    alarmActivated = true;
  }

  if (alarmActivated == true){
    valuePIR = digitalRead(pir);
      if ( valuePIR == HIGH) {
        digitalWrite(buzzer,LOW);  
        lcd.clear();
        enterPassword();
      }
    pressionado = digitalRead (botao);
      if ( pressionado == HIGH){
        lcd.setCursor(0,0);
        lcd.print("Deactivating...");

        int countdown2 = 2;
        while (countdown2 !=0){
          unsigned long tempoagora2 = millis();
          if (tempoagora2 - ultimociclo2 > periodo){
            ultimociclo2 = tempoagora2;

            activated = false;
            alarmActivated = false;
            digitalWrite(buzzer,HIGH);
            screenOffMsg = 0;
            countdown2--;
          }
        }
        
        }
    }

  if (!alarmActivated) {
    if (screenOffMsg == 0 ){
      lcd.setCursor(0,0);
      lcd.print("Activate Alarm  ");
      lcd.setCursor(0,1);
      lcd.print("     ");
    }
      pressionado = digitalRead(botao);
     if (pressionado == HIGH){        
      activateAlarm = true;            
    }
 }
}

void enterPassword() {
  activated = true;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" *** ALARM *** ");
  lcd.setCursor(0,1);
  lcd.print("Pass>");
      while(activated) {
        pressionado = digitalRead(botao);
      if (pressionado == HIGH){
        activated = false;
        alarmActivated = false;
        digitalWrite(buzzer,HIGH);
        screenOffMsg = 0;
      }
          
    }
}
```

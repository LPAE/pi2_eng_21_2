#define fan 22

void setup() {
  // put your setup code here, to run once:
  pinMode(fan, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(fan, LOW);  //Liga rele 1
  delay(5000);
  digitalWrite(fan, HIGH); //Desliga rele 1
  delay(5000);
}

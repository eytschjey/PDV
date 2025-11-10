const int LED = 21;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(LED,HIGH);
  delay(500);
  analogWrite(LED,LOW);
  delay(500);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(LED_BUILTIN,HIGH);
  delay(500);
  analogWrite(LED_BUILTIN,LOW);
  delay(500);
}

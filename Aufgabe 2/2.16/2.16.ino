int Taster = 36;
int LED = 21;
int val = 0;
long Timeout = 500;
long Timer = 0;
int state = LOW;
void setup() {
  // put your setup code here, to run once:
  pinMode(Taster,INPUT);
  pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(Taster);
  if (val == 1)
  {
    if (millis() >= Timeout + Timer)
    {
      Timer = millis();
      if (state == LOW) state = HIGH;
      else state = LOW;
      digitalWrite(LED,state);
    }
  }
  else
  {
    digitalWrite(LED,LOW);
    state = LOW;
  }
}

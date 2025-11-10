int Taster = 36;
int val = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Taster,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(Taster);
  if (val==0)
  {
    Serial.println("nicht gedrückt");
  }
  else
  {
    Serial.println("gedrückt");
  }
  delay(100);
}

const int LED1_1 = 21;
const int LED1_2 = 26;
const int LED2_1 = 32;
const int LED2_2 = 33;
const int LED3_1 = 4;
const int LED3_2 = 2;
const int Taster1 = 36;
const int Taster2 = 39;
const int Taster3 = 34;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED1_1,OUTPUT);
  pinMode(LED1_2,OUTPUT);
  pinMode(LED2_1,OUTPUT);
  pinMode(LED2_2,OUTPUT);
  pinMode(LED3_1,OUTPUT);
  pinMode(LED3_2,OUTPUT);
  pinMode(Taster1,INPUT);
  pinMode(Taster2,INPUT);
  pinMode(Taster3,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val1 = digitalRead(Taster1);
  int val2 = digitalRead(Taster2);
  int val3 = digitalRead(Taster3);
  if (val1 == 0 && val2 == 0 && val3 == 0)
  {
    digitalWrite(LED1_1,LOW);
    digitalWrite(LED1_2,LOW);
    digitalWrite(LED2_1,LOW);
    digitalWrite(LED2_2,LOW);
    digitalWrite(LED3_1,LOW);
    digitalWrite(LED3_2,LOW);
  }
  else if (val1 == 1 && val2 == 0 && val3 == 0)
  {
    digitalWrite(LED1_1,LOW);
    digitalWrite(LED1_2,HIGH);
    digitalWrite(LED2_1,LOW);
    digitalWrite(LED2_2,LOW);
    digitalWrite(LED3_1,LOW);
    digitalWrite(LED3_2,LOW);
  }
  else if (val1 == 0 && val2 == 1 && val3 == 0)
  {
    digitalWrite(LED1_1,LOW);
    digitalWrite(LED1_2,HIGH);
    digitalWrite(LED2_1,LOW);
    digitalWrite(LED2_2,LOW);
    digitalWrite(LED3_1,LOW);
    digitalWrite(LED3_2,LOW);
  }
  else if (val1 == 0 && val2 == 0 && val3 == 1)
  {
    digitalWrite(LED1_1,LOW);
    digitalWrite(LED1_2,HIGH);
    digitalWrite(LED2_1,LOW);
    digitalWrite(LED2_2,LOW);
    digitalWrite(LED3_1,LOW);
    digitalWrite(LED3_2,LOW);
  }
  else if (val1 == 1 && val2 == 1 && val3 == 0)
  {
    digitalWrite(LED1_1,LOW);
    digitalWrite(LED1_2,LOW);
    digitalWrite(LED2_1,LOW);
    digitalWrite(LED2_2,HIGH);
    digitalWrite(LED3_1,LOW);
    digitalWrite(LED3_2,LOW);
  }
  else if (val1 == 1 && val2 == 0 && val3 == 1)
  {
    digitalWrite(LED1_1,LOW);
    digitalWrite(LED1_2,LOW);
    digitalWrite(LED2_1,LOW);
    digitalWrite(LED2_2,HIGH);
    digitalWrite(LED3_1,LOW);
    digitalWrite(LED3_2,LOW);
  }
  else if (val1 == 0 && val2 == 1 && val3 == 1)
  {
    digitalWrite(LED1_1,LOW);
    digitalWrite(LED1_2,LOW);
    digitalWrite(LED2_1,LOW);
    digitalWrite(LED2_2,HIGH);
    digitalWrite(LED3_1,LOW);
    digitalWrite(LED3_2,LOW);
  }
  else if (val1 == 1 && val2 == 1 && val3 == 1)
  {
    digitalWrite(LED1_1,LOW);
    digitalWrite(LED1_2,LOW);
    digitalWrite(LED2_1,LOW);
    digitalWrite(LED2_2,LOW);
    digitalWrite(LED3_1,HIGH);
    digitalWrite(LED3_2,LOW);
  }
}

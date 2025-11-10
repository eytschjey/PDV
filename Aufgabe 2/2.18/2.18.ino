int LED1 = 21;
int LED2 = 26;
int Taster1 = 36;
int Taster2 = 39;
int Taster3 = 34;
void setup() {
  // put your setup code here, to run once:
  pinMode(Taster1,INPUT);
  pinMode(Taster2,INPUT);
  pinMode(Taster3,INPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  digitalWrite(LED2,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int in1 = digitalRead(Taster1);
  int in2 = digitalRead(Taster2);
  int in3 = digitalRead(Taster3);
  if (in1 == 1 && in2 == 0 && in3 == 0)
  {
    analogWrite(LED1,100);
  }
  else if (in1 == 1 && in2 == 1 && in3 == 0)
  {
    analogWrite(LED1,200);
  }
  else if (in1 == 1 && in2 == 1 && in3 == 1)
  {
    analogWrite(LED1,255);
  }
  else if (in1 == 0 && in2 == 1 && in3 == 1)
  {
    analogWrite(LED1, 150);
  }
  else if (in1 == 0 && in2 == 0 && in3 == 1)
  {
    analogWrite(LED1,25);
  }
  else if (in1 == 0 && in3 == 0 && in2 == 1)
  {
    analogWrite(LED1,50);
  }
  else if (in1 == 0 && in2 == 0 && in3 == 0)
  {
    analogWrite(LED1,0);
  }
}

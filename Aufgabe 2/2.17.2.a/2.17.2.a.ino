// Aufgabe 2.17.2.a
// Steuerung von 3 LED-Paaren über 3 Taster
//Hinweis: Die Vollständige Dokumentation finden sie in "Aufgabe 2 Team K.pdf"


// Initialisierung der GPIO Pins für LEDs und Taster
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
  // LEDs als Output und Taster als Input definieren
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
  // Auslesen der Tasterzustände
  int val1 = digitalRead(Taster1);
  int val2 = digitalRead(Taster2);
  int val3 = digitalRead(Taster3);


  // Hinweis LED Farbe: Wenn Pin1 low und Pin2 high -> grün, wenn Pin1 high und Pin2 low -> rot
  // wenn alle Taster nicht gedrückt sind, alle LEDs aus
  if (val1 == 0 && val2 == 0 && val3 == 0)
  {
    digitalWrite(LED1_1,LOW);
    digitalWrite(LED1_2,LOW);
    digitalWrite(LED2_1,LOW);
    digitalWrite(LED2_2,LOW);
    digitalWrite(LED3_1,LOW);
    digitalWrite(LED3_2,LOW);
  }
  // Wenn Taster 1 gedrückt ist, LED 1 an (grün)
  else if (val1 == 1 && val2 == 0 && val3 == 0)
  {
    digitalWrite(LED1_1,LOW);
    digitalWrite(LED1_2,HIGH);
    digitalWrite(LED2_1,LOW);
    digitalWrite(LED2_2,LOW);
    digitalWrite(LED3_1,LOW);
    digitalWrite(LED3_2,LOW);
  }
  // Wenn Taster 2 gedrückt ist, LED 1 an (grün)
  else if (val1 == 0 && val2 == 1 && val3 == 0)
  {
    digitalWrite(LED1_1,LOW);
    digitalWrite(LED1_2,HIGH);
    digitalWrite(LED2_1,LOW);
    digitalWrite(LED2_2,LOW);
    digitalWrite(LED3_1,LOW);
    digitalWrite(LED3_2,LOW);
  }
  // Wenn Taster 3 gedrückt ist, LED 1 an (grün)
  else if (val1 == 0 && val2 == 0 && val3 == 1)
  {
    digitalWrite(LED1_1,LOW);
    digitalWrite(LED1_2,HIGH);
    digitalWrite(LED2_1,LOW);
    digitalWrite(LED2_2,LOW);
    digitalWrite(LED3_1,LOW);
    digitalWrite(LED3_2,LOW);
  }
  // Wenn Taster 1 und 2 gedrückt sind, LED 2 an (grün)
  else if (val1 == 1 && val2 == 1 && val3 == 0)
  {
    digitalWrite(LED1_1,LOW);
    digitalWrite(LED1_2,LOW);
    digitalWrite(LED2_1,LOW);
    digitalWrite(LED2_2,HIGH);
    digitalWrite(LED3_1,LOW);
    digitalWrite(LED3_2,LOW);
  }
  // Wenn Taster 1 und 3 gedrückt sind, LED 2 an (grün)
  else if (val1 == 1 && val2 == 0 && val3 == 1)
  {
    digitalWrite(LED1_1,LOW);
    digitalWrite(LED1_2,LOW);
    digitalWrite(LED2_1,LOW);
    digitalWrite(LED2_2,HIGH);
    digitalWrite(LED3_1,LOW);
    digitalWrite(LED3_2,LOW);
  }
  // Wenn Taster 2 und 3 gedrückt sind, LED 2 an (grün)
  else if (val1 == 0 && val2 == 1 && val3 == 1)
  {
    digitalWrite(LED1_1,LOW);
    digitalWrite(LED1_2,LOW);
    digitalWrite(LED2_1,LOW);
    digitalWrite(LED2_2,HIGH);
    digitalWrite(LED3_1,LOW);
    digitalWrite(LED3_2,LOW);
  }
  // Wenn alle Taster gedrückt sind, LED 3 an (rot)
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

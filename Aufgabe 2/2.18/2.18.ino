// Aufgabe 2.18: LED Helligkeit je nach Tastenkombination steuern

/*
1. Entwickeln Sie ein Programm, das abhängig vom Binär-Wert der [Taster] die 
Helligkeit der LED ändert! 
2. Können Sie die Auflösung des PWM Ausgangs verändern?
Die Auflösung des PWM Ausgangs kann man durch die Funktion analogWriteRange() verändern.
Standardrange ist 255 (8Bit). Setzt man die Range auf 10Bit, kann man 1023 Stufen ansteuern.


*/


// Definieren der GPIO Pins für LEDs und Taster
int LED1 = 21;
int LED2 = 26;
int Taster1 = 36;
int Taster2 = 39;
int Taster3 = 34;


void setup() {
  // Initialisierung der Pins (Taster als Input, LEDs als Output)
  pinMode(Taster1,INPUT);
  pinMode(Taster2,INPUT);
  pinMode(Taster3,INPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  // Pin 2 der LED als Ground festlegen
  digitalWrite(LED2,LOW);
}

void loop() {
  // Auslesen der Tasterzustände
  int in1 = digitalRead(Taster1);
  int in2 = digitalRead(Taster2);
  int in3 = digitalRead(Taster3);

  // Steuerung der LED Helligkeit basierend auf Tasterzuständen
  // Falls Taster 1 gedrückt ist, Helligkeit auf 100 (von 255) setzen
  if (in1 == 1 && in2 == 0 && in3 == 0)
  {
    analogWrite(LED1,300);
  }
  // Falls Taster 1 und 2 gedrückt sind, Helligkeit auf 200 setzen
  else if (in1 == 1 && in2 == 1 && in3 == 0)
  {
    analogWrite(LED1,200);
  }
  // Falls alle Taster gedrückt sind, Helligkeit auf 255 setzen
  else if (in1 == 1 && in2 == 1 && in3 == 1)
  {
    analogWrite(LED1,255);
  }
  // Falls Taster 2 und 3 gedrückt sind, Helligkeit auf 150 setzen
  else if (in1 == 0 && in2 == 1 && in3 == 1)
  {
    analogWrite(LED1, 150);
  }
  // Falls nur Taster 3 gedrückt ist, Helligkeit auf 25 setzen
  else if (in1 == 0 && in2 == 0 && in3 == 1)
  {
    analogWrite(LED1,25);
  }
  // Falls nur Taster 2 gedrückt ist, Helligkeit auf 50 setzen
  else if (in1 == 0 && in3 == 0 && in2 == 1)
  {
    analogWrite(LED1,50);
  }
  // Falls kein Taster gedrückt ist, LED ausschalten
  else if (in1 == 0 && in2 == 0 && in3 == 0)
  {
    analogWrite(LED1,0);
  }
}

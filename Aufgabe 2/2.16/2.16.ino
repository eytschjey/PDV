/* Aufgabe 2.16 - ESP32 Switch Blink

Erstellen Sie ein Programm für das STTS-ESP32-System, das abhängig vom Zustand des 
Tasters die LED 1 mit einer Frequenz von 1 Hertz blinkt oder ganz ausschaltet! (siehe 
Datenblatt ESP32) 

Vermeiden Sie die Verwendung des „delay()“ Befehls! 
*/


// Definieren der GPIO Pins für Taster und LED
int Taster = 36;
int LED = 21;
int LED1 =26;
int val = 0;
long Timeout = 5000;
long Timer = 0;
int state = LOW;

void setup() {
  // Definieren des Tasters als Input und der LED als Output
  pinMode(Taster,INPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED,OUTPUT);
  digitalWrite(LED1,LOW);
}

void loop() {
  // Auslesen des Tasterzustands
  val = digitalRead(Taster);
  // Wenn Taster gedrückt
  if (val == 1)
  {
    // wenn die Zeit seit dem letzten Wechsel größer als das Timeout ist
    if (millis() >= Timeout + Timer)
    {
      // Timer zurücksetzen und LED Zustand wechseln
      Timer = millis();
      if (state == LOW) state = HIGH;
      else state = LOW;
      digitalWrite(LED,state);
    }
  }
  // Wenn Taster nicht gedrückt, LED ausschalten
  else
  {
    digitalWrite(LED,LOW);
    state = LOW;
    Timer = 0;
  }
}

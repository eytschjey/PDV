/* Aufgabe 2.15 - ESP32 Switch
Erstellen Sie ein Programm für das STTS-ESP32-System, das die Position eines Tasters über 
die serielle Verbindung ausgibt. 
*/

// Definieren des GPIO Pins für den Taster
int Taster = 36;
int val = 0;
void setup() {
  // Serial Monitor definieren
  Serial.begin(9600);
  // Taster als Input definieren
  pinMode(Taster,INPUT);
}

void loop() {
  // Auslesen des Tasterzustands
  val = digitalRead(Taster);
  // falls Taster nicht gedrückt
  if (val==0)
  {
    Serial.println("nicht gedrückt");
  }
  // falls Taster gedrückt
  else
  {
    Serial.println("gedrückt");
  }
  delay(100);
}

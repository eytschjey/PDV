/* Aufgabe 2.14
Erstellen Sie ein Programm für das STTS Arduino-System, das eine LED im Sekundentakt 
blinken lässt.  

Verwenden Sie in diesem einfachen Programm die Funktion „delay(msec)“!

Hinweis: Die Vollständige Dokumentation finden sie in "Aufgabe 2 Team K.pdf"
*/


//Verwendung der eingebauten LED
void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
}

// LED im Sekundentakt blinken lassen
void loop() {
  analogWrite(LED_BUILTIN,HIGH);
  delay(500);
  analogWrite(LED_BUILTIN,LOW);
  delay(500);
}

*/

// Verwendung einer externen LED
// Definieren der GPIO Pin für die LED
const int LED = 21;
// Definieren der LED als Output
void setup() {
  pinMode(LED,OUTPUT);
}

// LED im Sekundentakt blinken lassen
void loop() {
  analogWrite(LED,HIGH);
  delay(500);
  analogWrite(LED,LOW);
  delay(500);
}

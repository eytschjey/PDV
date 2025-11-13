// Aufgabe 2.13
/*
Schreiben Sie ein Programm, das den Text "Hello STTS Arduino World"
über die serielle Schnittstelle ausgibt.

Frage 3:Woran erkennen Sie, dass gerade ein neues Programm hochgeladen wird?
Am Blinken der internen LED während des Uploads.


Hinweis: Die Vollständige Dokumentation finden sie in "Aufgabe 2 Team K.pdf"
*/

// Initialisierung des seriellen Monitors
void setup() {
  Serial.begin(9600);
}

// Ausgabe von Hello World im Loop
void loop() {
  Serial.println("Hello STTS Arduino World");
}

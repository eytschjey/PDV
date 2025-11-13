/* 
Aufgabe 2.17.2b: Senden von MQTT Nachrichten bei Tastendruck

- Wenn sich der Zustand eines Schalters ändert, soll immer eine Nachricht 
geschickt werden.

- 2 Sekunden nach einer gesendeten Nachricht soll erneut eine neue Nachricht 
geschickt werden 

- Der Inhalt der Nachricht setzt sich abhängig von den Tastern T1, T2 und T3 
aus den folgenden Bestandteilen zusammen:  
1. Gruppennamen 
2. Anzahl der gedrückten Taster 
3. Liste der gedrückten Taster (z.B bei gedrücktem Schalter T1 und T3 
die Liste „[T1, T2]“ 

- Wenn das Senden der Nachricht fehlschlägt sollen alle LEDs der Boards mit 2 
Hz rot blinken!  

*/


#include <WiFi.h>
#include <PubSubClient.h>

// WLAN im SSTS Labor
const char *ssid ="ITBahn123";
const char *password ="ITBahn12345";

const char *broker ="141.72.191.235";
const char *topic ="hello";
const int port = 1883;

// leer lassen fuer kein username und kein password (STTS Labor)
const char *username ="";
const char *mqtt_password ="";

// Initialisierung der GPIO Pins für Taster und LEDs
const int Taster1 = 36;
const int Taster2 = 39;
const int Taster3 = 34;
const int LED1_1 = 21;
const int LED1_2 = 26;
const int LED2_1 = 32;
const int LED2_2 = 33;
const int LED3_1 = 4;
const int LED3_2 = 2;

// Initialisierung von Variablen
int state1 = 0;
int state2 = 0;
int state3 = 0;
int stateLED = 0;
int val1 = 0;
int val2 = 0;
int val3 = 0;
int used1 = 0;
int used2 = 0;
int used3 = 0;
int anzahl = 0;
int failed = 0;
long Timeout = 250;
long Timer = 0;
long Timeout1 = 2000;
long Timer1 = 0;
String Taster;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // WLAN Verbindung aufbauen
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  // MQTT Verbindung aufbauen
  client.setServer(broker, port);
  while (!client.connected())
  {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to broker \n",client_id.c_str());
    if (client.connect(client_id.c_str(),username,password))
    {
      Serial.println("broker connected");
    }
    else 
    {
      Serial.print("failed with state");
      Serial.print(client.state());
      delay(2000);
    }
  }

  // Taster als Input und LEDs als Output definieren
  pinMode(Taster1,INPUT);
  pinMode(Taster2,INPUT);
  pinMode(Taster3,INPUT);
  pinMode(LED1_1,OUTPUT);
  pinMode(LED1_2,OUTPUT);
  pinMode(LED2_1,OUTPUT);
  pinMode(LED2_2,OUTPUT);
  pinMode(LED3_1,OUTPUT);
  pinMode(LED3_2,OUTPUT);
  digitalWrite(LED1_2,LOW);
  digitalWrite(LED2_2,LOW);
  digitalWrite(LED3_2,LOW);
}

void loop() {
  client.loop();
  // string Taster zuruecksetzen
  for(int i = 0; i<3; i++)
  {
    Taster = " ";
  }

  // alter state in neue Variable speichern und neuen Tasterzustand auslesen
  state1 = val1;
  state2 = val2;
  state3 = val3;
  val1 = digitalRead(Taster1);
  val2 = digitalRead(Taster2);
  val3 = digitalRead(Taster3);
  // Anzahl der gedrueckten Taster bestimmen
  anzahl = val1 + val2 +val3;

  // fuer Taster 1: wenn neuer und alter state nicht ubereinstimmen, Nachricht senden
  if (state1 != val1)
  {
    if(client.publish(topic,"Gruppe K") != 1)
    {
      // Falls fehlgeschlagen, failed zaehler erhoehen
      failed++;
    }
    used1 = 1;
  }

// gleiches Vorgehen fuer Taster 2
  if (state2 != val2)
  {
    if(client.publish(topic,String(anzahl).c_str()) != 1)
    {
      failed++;
    }
    used2 = 1;
  }

  // Taster 3: Sende eine Nachricht mit der Liste der gedrueckten Taster bei Zustandsaenderung
  if (state3 != val3)
  {
    if(val1 == 1)
    {
      Taster += String(" T1 ");
      if(val2 == 1)
      {
        Taster += String(" T2 ");
        if(val2 == 1)
        {
          Taster += String(" T3 ");
        }
      } 
      else if(val3 == 1)
      {
        Taster += String(" T3 ");
      }
    }
    else if(val2 == 1)
    {
      Taster += String(" T2 ");
      if(val3 == 1)
      {
        Taster += String(" T3 ");
      }
    }
    else if(val3 == 1)
    {
      Taster += String(" T3 ");
    }
    if(client.publish(topic,Taster.c_str()) != 1)
    {
      failed++;
    }
    used3 = 1;
  }

  // Wenn eine Nachricht gesendet wurde (used), 2 Sekunden warten bevor neue Nachricht gesendet wird
  if(used1 == 1 || used2 == 1 || used3 == 1)
  {
    if (millis() >= Timeout1 + Timer1)
    {
      Timer1 = millis();
      if (used1 == 1)
      {
        if(client.publish(topic,"Gruppe K") != 1)
        {
          failed++;
        }
        used1 = 0;
      }
      if (used2 == 1)
      {
        if(client.publish(topic,String(anzahl).c_str()) !=1)
        {
          failed++;
        }
        used2 = 0;
      }
      if (used3 == 1)
      {
        if(client.publish(topic,Taster.c_str()) != 1)
        {
          failed++;
        }
        used3 = 0;
      }
    }
  }
  
  // failed zaehlt die fehlgeschlagenen Sendeversuche, wenn ungleich 0, alle LEDs mit 2Hz rot blinken lassen
  if (failed != 0)
  {
    while(1)
    {
      // Timeout und Timer fuer Blinkfrequenz (2Hz)
      if (millis() >= Timeout + Timer)
      {
        Timer = millis();
        if (stateLED == LOW) stateLED = HIGH;
        else stateLED = LOW;
        digitalWrite(LED1_1,stateLED);
        digitalWrite(LED2_1,stateLED);
        digitalWrite(LED3_1,stateLED);
      }
    }
  }
  
}

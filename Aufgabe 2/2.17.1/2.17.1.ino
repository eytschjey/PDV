// Aufgabe 2.17.1: MQTT Nachricht bei Tastendruck senden

// Hinweis: Die Vollständige Dokumentation finden sie in "Aufgabe 2 Team K.pdf"
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

// Initialisierung von Variablen
const int Taster1 = 36;
int time1 = 0;
int time2 = 0;
int buttonState = 0;
int lastButtonState = 0;
long pressTime = 0;
long releaseTime = 0;
long duration = 0;
long Timeout = 500;
long Timer = 0;

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
  // Taster 1 als Input
  pinMode(Taster1,INPUT);
}

void loop() {
  client.loop();
  // Messung des Tasterzustands an Pin 36
  buttonState = digitalRead(36);
  time1 = 0;

  // Messung von Druckdauer und Intervall


  // Sende MQTT Nachricht bei Tastendruck
  while (buttonState == 1)
  {
    // Kurz- und gedrückt unterscheiden
   
    if (millis() >= Timeout + Timer)
    {
      Timer = millis();
      client.publish(topic,"Hello STTS World von Gruppe K");
    }
    
    buttonState = digitalRead(36);
  }
}
